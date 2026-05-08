cd ~/Documents

cat > k1000_lite.py <<'PY'
#!/usr/bin/env python3
"""
k1000_lite.py — Kernel 1000-DEV (LITE)
Mobile-first (a-Shell / iOS), no unzip required, single-file.
- read-only scan of a vault folder
- deterministic index + manifest + report
- append-only metrics/events.jsonl
Outputs go to: ~/Documents/k1000_out/

Usage:
  python3 k1000_lite.py scan  "/path/to/Vault"
  python3 k1000_lite.py scan  "~/Documents/ObsidianVault"
  python3 k1000_lite.py where
"""

from __future__ import annotations
import argparse, json, hashlib, datetime, os
from pathlib import Path

ALLOWED_EXT = {".md",".txt",".json",".yaml",".yml",".html",".xml"}
REQUIRED_HEADER_KEYS = [
  "kernel_id","kernel_version","kernel_mode","kernel_state","build_id","build_hash",
  "canon_status","metrika","communication","artifact_type","artifact_status","source"
]

def utc_now() -> str:
  # timezone-aware, avoids DeprecationWarning
  return datetime.datetime.now(datetime.timezone.utc).replace(microsecond=0).isoformat().replace("+00:00","Z")

def sha256_bytes(b: bytes) -> str:
  return "sha256:" + hashlib.sha256(b).hexdigest()

def safe_expand(p: str) -> Path:
  return Path(os.path.expanduser(p)).resolve()

def read_text(path: Path) -> str:
  return path.read_text(encoding="utf-8", errors="replace")

def parse_frontmatter_min(text: str) -> dict:
  # minimal YAML frontmatter parser: expects starting '---' and next '---'
  if not text.lstrip().startswith("---"):
    return {}
  start = text.find("---")
  end = text.find("---", start+3)
  if end == -1:
    return {}
  block = text[start+3:end].strip()
  data = {}
  for line in block.splitlines():
    s = line.strip()
    if not s or s.startswith("#") or ":" not in line:
      continue
    k,v = line.split(":",1)
    k = k.strip()
    v = v.strip()
    if " #" in v:
      v = v.split(" #",1)[0].strip()
    # list shorthand
    if v.startswith("[") and v.endswith("]"):
      inner = v[1:-1].strip()
      data[k] = [x.strip() for x in inner.split(",") if x.strip()]
    else:
      data[k] = v.strip('"').strip("'")
  return data

def ensure_dir(p: Path) -> None:
  p.mkdir(parents=True, exist_ok=True)

def write_json(path: Path, obj) -> None:
  ensure_dir(path.parent)
  path.write_text(json.dumps(obj, indent=2, ensure_ascii=False), encoding="utf-8")

def append_jsonl(path: Path, obj) -> None:
  ensure_dir(path.parent)
  with path.open("a", encoding="utf-8") as f:
    f.write(json.dumps(obj, ensure_ascii=False) + "\n")

def scan_vault(root: Path) -> tuple[list[dict], list[str]]:
  records, warnings = [], []
  if not root.exists() or not root.is_dir():
    return [], [f"vault_not_found:{root}"]
  for p in sorted(root.rglob("*")):
    if p.is_dir():
      continue
    if p.suffix.lower() not in ALLOWED_EXT:
      continue
    try:
      b = p.read_bytes()
    except Exception as e:
      warnings.append(f"read_fail:{p}:{e}")
      continue

    rec = {
      "path": str(p.relative_to(root)),
      "bytes": len(b),
      "sha256": sha256_bytes(b),
      "type": p.suffix.lower().lstrip("."),
      "mtime_utc": datetime.datetime.fromtimestamp(p.stat().st_mtime, tz=datetime.timezone.utc).replace(microsecond=0).isoformat().replace("+00:00","Z")
    }

    if p.suffix.lower() == ".md":
      fm = parse_frontmatter_min(read_text(p))
      rec["frontmatter"] = fm
      missing = [k for k in REQUIRED_HEADER_KEYS if k not in fm]
      rec["header_ok"] = (len(missing)==0)
      if missing:
        rec["missing_header_keys"] = missing

    records.append(rec)
  return records, warnings

def cmd_where(out_root: Path) -> int:
  print("K1000_LITE")
  print("Documents:", str(Path("~/Documents").expanduser().resolve()))
  print("Out:", str(out_root))
  return 0

def cmd_scan(vault_path: str, out_root: Path) -> int:
  t = utc_now()
  vault = safe_expand(vault_path)

  files, warnings = scan_vault(vault)

  index = {
    "kernel": "k1000_dev_lite",
    "generated_utc": t,
    "vault_root": str(vault),
    "files_scanned": len(files),
    "warnings": warnings,
    "files": files
  }

  # deterministic manifest hash
  index_bytes = json.dumps(index, sort_keys=True, ensure_ascii=False).encode("utf-8")
  index_sha = sha256_bytes(index_bytes)

  manifest = {
    "kernel": "k1000_dev_lite",
    "generated_utc": t,
    "vault_root": str(vault),
    "index_sha256": index_sha,
    "policy": {
      "read": "read_only",
      "write": "append_only_outputs",
      "communication": "OFF"
    }
  }

  report = {
    "generated_utc": t,
    "ok": (len(files) > 0 and all(not w.startswith("vault_not_found") for w in warnings)),
    "files_scanned": len(files),
    "warnings_count": len(warnings),
    "header_ok": sum(1 for r in files if r.get("header_ok") is True),
    "header_bad": sum(1 for r in files if r.get("header_ok") is False),
    "index_sha256": index_sha
  }

  write_json(out_root / "index.json", index)
  write_json(out_root / "manifest.json", manifest)
  write_json(out_root / "report.json", report)

  append_jsonl(out_root / "metrics" / "events.jsonl", {
    "event": "kernel_scan",
    "timestamp_utc": t,
    "vault_root": str(vault),
    "files_scanned": len(files),
    "warnings": len(warnings),
    "index_sha256": index_sha
  })

  print("OK" if report["ok"] else "WARN")
  print("out:", str(out_root))
  print("files:", report["files_scanned"], "warnings:", report["warnings_count"])
  return 0

def main():
  out_root = Path("~/Documents/k1000_out").expanduser().resolve()

  ap = argparse.ArgumentParser()
  sub = ap.add_subparsers(dest="cmd", required=True)
  sub.add_parser("where")
  sp = sub.add_parser("scan")
  sp.add_argument("vault_path")
  args = ap.parse_args()

  if args.cmd == "where":
    raise SystemExit(cmd_where(out_root))
  if args.cmd == "scan":
    raise SystemExit(cmd_scan(args.vault_path, out_root))

if __name__ == "__main__":
  main()
PY

chmod +x k1000_lite.py
python3 k1000_lite.py where