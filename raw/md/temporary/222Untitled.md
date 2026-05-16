#!/usr/bin/env bash
set -euo pipefail

# =========================
# QuietHarbor v0.1 Installer
# (K501 Dev Kernel + Miniloader)
# =========================

PROJECT_DIR="${1:-quietharbor_v01}"
PYTHON_BIN="${PYTHON_BIN:-python3}"

echo "[QuietHarbor] creating project: ${PROJECT_DIR}"
mkdir -p "${PROJECT_DIR}"
cd "${PROJECT_DIR}"

echo "[QuietHarbor] creating venv"
"${PYTHON_BIN}" -m venv .venv
# shellcheck disable=SC1091
source .venv/bin/activate

echo "[QuietHarbor] upgrading pip"
python -m pip install --upgrade pip >/dev/null

echo "[QuietHarbor] installing minimal deps"
python -m pip install ruamel.yaml >/dev/null

echo "[QuietHarbor] creating directories"
mkdir -p out logs metrics import

echo "[QuietHarbor] writing loader.py"
cat > loader.py <<'PY'
#!/usr/bin/env python3
"""
K501 Miniloader (ML-01) — minimal, fast, reliable
- Finds DSL (YAML/JSON)
- Loads + basic sanity checks
- Hands over a KernelContext to the kernel entrypoint
- NO scanning, NO rules, NO metrics, NO canon checks (kernel does that)

Usage:
  python loader.py run k501.dsl.yaml
  python loader.py run k501.dsl.json
  python loader.py run .                 # resolves default DSL in current dir
"""

from __future__ import annotations

import json
import sys
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict

try:
    from ruamel.yaml import YAML  # type: ignore
except Exception:  # pragma: no cover
    YAML = None


DEFAULT_DSL_CANDIDATES = (
    "k501.dsl.yaml",
    "k501.dsl.yml",
    "k501.dsl.json",
    "k500.inline.yaml",
    "k500.inline.yml",
    "k500.inline.json",
)


@dataclass(frozen=True)
class KernelContext:
    config: Dict[str, Any]
    mode: str
    start_time_utc: str
    base_path: str
    dsl_path: str


def utc_now_iso() -> str:
    return datetime.now(timezone.utc).replace(microsecond=0).isoformat()


def die(msg: str, code: int = 4) -> None:
    print(f"[K501:MINILOADER] {msg}", file=sys.stderr)
    raise SystemExit(code)


def is_json_path(p: Path) -> bool:
    return p.suffix.lower() == ".json"


def is_yaml_path(p: Path) -> bool:
    return p.suffix.lower() in (".yaml", ".yml")


def load_json(p: Path) -> Dict[str, Any]:
    try:
        return json.loads(p.read_text(encoding="utf-8"))
    except FileNotFoundError:
        die(f"DSL not found: {p}", 4)
    except Exception as e:
        die(f"JSON parse error in {p}: {e}", 4)


def load_yaml(p: Path) -> Dict[str, Any]:
    if YAML is None:
        die("YAML support missing. Install ruamel.yaml to load .yaml/.yml DSL files.", 4)
    try:
        y = YAML(typ="safe")
        data = y.load(p.read_text(encoding="utf-8"))
        if data is None:
            return {}
        if not isinstance(data, dict):
            die(f"YAML root must be a mapping/object in {p}", 4)
        return data
    except FileNotFoundError:
        die(f"DSL not found: {p}", 4)
    except Exception as e:
        die(f"YAML parse error in {p}: {e}", 4)


def load_dsl(dsl_path: Path) -> Dict[str, Any]:
    if is_json_path(dsl_path):
        return load_json(dsl_path)
    if is_yaml_path(dsl_path):
        return load_yaml(dsl_path)
    die(f"Unsupported DSL file type: {dsl_path} (use .yaml/.yml/.json)", 4)


def resolve_dsl_path(arg: str) -> Path:
    p = Path(arg).expanduser().resolve()

    if p.is_file():
        return p

    if p.is_dir():
        for name in DEFAULT_DSL_CANDIDATES:
            cand = p / name
            if cand.exists() and cand.is_file():
                return cand
        die(
            "No DSL found in directory. Tried: "
            + ", ".join(DEFAULT_DSL_CANDIDATES)
            + f" in {p}",
            4,
        )

    cwd = Path.cwd().resolve()
    cand = (cwd / arg).resolve()
    if cand.exists() and cand.is_file():
        return cand

    die(f"DSL path not found: {arg}", 4)


def basic_sanity(config: Dict[str, Any]) -> None:
    if not isinstance(config, dict):
        die("DSL must load to an object/mapping", 4)

    kernel = config.get("kernel", {})
    if kernel and not isinstance(kernel, dict):
        die("Field 'kernel' must be an object", 4)

    if not config:
        die("DSL is empty. Provide at least {kernel:{...}} or {targets:{...}}", 4)


def import_kernel_entry():
    try:
        import k501  # type: ignore

        if not hasattr(k501, "bootstrap_kernel"):
            die("Kernel module 'k501.py' must expose bootstrap_kernel(ctx).", 4)
        return k501.bootstrap_kernel
    except ModuleNotFoundError:
        die("Kernel module not found. Expected file: k501.py (importable as 'k501').", 4)
    except Exception as e:
        die(f"Kernel import error: {e}", 4)


def cmd_run(dsl_arg: str, mode: str = "dev") -> int:
    dsl_path = resolve_dsl_path(dsl_arg)
    config = load_dsl(dsl_path)
    basic_sanity(config)

    ctx = KernelContext(
        config=config,
        mode=mode,
        start_time_utc=utc_now_iso(),
        base_path=str(Path.cwd().resolve()),
        dsl_path=str(dsl_path),
    )

    bootstrap_kernel = import_kernel_entry()
    return int(bootstrap_kernel(ctx))


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        die("Usage: loader.py run <dsl-path|dir|.>", 4)

    cmd = argv[1].lower().strip()

    if cmd == "run":
        dsl_arg = argv[2] if len(argv) >= 3 else "."
        return cmd_run(dsl_arg, mode="dev")

    die(f"Unknown command: {cmd}. Supported: run", 4)


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
PY
chmod +x loader.py

echo "[QuietHarbor] writing k501.py"
cat > k501.py <<'PY'
#!/usr/bin/env python3
"""
K501 Development Kernel (K-01) — minimal, deterministic
Pipeline:
  1) Canon Gate (optional in fresh projects)
  2) Scan targets
  3) Standards (MetaHeader/DDF basic checks)
  4) Analysis (minimal rules)
  5) Metrics (Performance/Trend/Long-Term)
  6) Report + Logs + Voice

Exit codes:
  0 GREEN, 1 YELLOW, 2 RED, 3 CANON_FAIL, 4 DSL_FAIL
"""

from __future__ import annotations

import fnmatch
import hashlib
import json
import os
import re
import time
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

try:
    from ruamel.yaml import YAML  # type: ignore
except Exception:  # pragma: no cover
    YAML = None


EXIT_GREEN = 0
EXIT_YELLOW = 1
EXIT_RED = 2
EXIT_CANON_FAIL = 3
EXIT_DSL_FAIL = 4

STATE_GREEN = "GREEN"
STATE_YELLOW = "YELLOW"
STATE_RED = "RED"

_FRONT_RE = re.compile(r"^---\s*\n(.*?)\n---\s*\n", re.DOTALL)


@dataclass(frozen=True)
class KernelContext:
    config: Dict[str, Any]
    mode: str
    start_time_utc: str
    base_path: str
    dsl_path: str


def utc_now_iso() -> str:
    return datetime.now(timezone.utc).replace(microsecond=0).isoformat()


def ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)


def write_json(path: Path, obj: Any) -> None:
    ensure_dir(path.parent)
    path.write_text(
        json.dumps(obj, ensure_ascii=False, sort_keys=True, separators=(",", ":")) + "\n",
        encoding="utf-8",
    )


def append_jsonl(path: Path, obj: Any) -> None:
    ensure_dir(path.parent)
    with path.open("a", encoding="utf-8") as f:
        f.write(json.dumps(obj, ensure_ascii=False, sort_keys=True, separators=(",", ":")) + "\n")


def append_log(path: Path, line: str) -> None:
    ensure_dir(path.parent)
    with path.open("a", encoding="utf-8") as f:
        f.write(line.rstrip("\n") + "\n")


def sha256_file(path: Path, chunk: int = 1024 * 1024) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        while True:
            b = f.read(chunk)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def match_any(path_posix: str, patterns: List[str]) -> bool:
    for pat in patterns:
        if fnmatch.fnmatch(path_posix, pat):
            return True
    return False


def scan_targets(cfg: Dict[str, Any], base_path: Path) -> List[Dict[str, Any]]:
    targets = cfg.get("targets", {}) if isinstance(cfg.get("targets", {}), dict) else {}
    root = str(targets.get("root", "."))
    root_path = (base_path / root).resolve()

    include = targets.get("include", ["**/*.md", "**/*.yaml", "**/*.yml", "**/*.json", "**/*.txt", "**/*.html"])
    exclude = targets.get("exclude", ["**/.git/**", "**/node_modules/**", "**/out/**", "**/logs/**", "**/metrics/**", "**/.obsidian/**"])

    include_pats = [str(p).replace("\\", "/") for p in include]
    exclude_pats = [str(p).replace("\\", "/") for p in exclude]

    out: List[Dict[str, Any]] = []
    for dirpath, dirnames, filenames in os.walk(root_path):
        dirnames.sort()
        filenames.sort()
        for name in filenames:
            abs_path = Path(dirpath) / name
            rel = abs_path.relative_to(base_path).as_posix()
            if exclude_pats and match_any(rel, exclude_pats):
                continue
            if include_pats and not match_any(rel, include_pats):
                continue
            try:
                st = abs_path.stat()
            except Exception:
                continue
            out.append({
                "path": rel,
                "size": int(st.st_size),
                "mtime_utc": datetime.fromtimestamp(st.st_mtime, tz=timezone.utc).replace(microsecond=0).isoformat(),
                "ext": abs_path.suffix.lower(),
            })
    return out


def read_text_safe(path: Path, limit_bytes: int = 2_000_000) -> str:
    with path.open("rb") as f:
        data = f.read(limit_bytes)
    return data.decode("utf-8", errors="replace")


def parse_metaheader(text: str) -> Dict[str, Any]:
    m = _FRONT_RE.match(text)
    if not m:
        return {"present": False}

    if YAML is None:
        return {"present": True, "parsed": False}

    y = YAML(typ="safe")
    try:
        data = y.load(m.group(1)) or {}
        if not isinstance(data, dict):
            return {"present": True, "parsed": True, "data": {}}
        return {"present": True, "parsed": True, "data": data}
    except Exception:
        return {"present": True, "parsed": False}


def parse_ddf(text: str) -> Dict[str, Any]:
    levels = set(re.findall(r"DDF\s*:\s*(L[0-3])", text, flags=re.IGNORECASE))
    return {"enabled": bool(levels), "levels": sorted({lv.upper() for lv in levels})}


def enforce_standards(files: List[Dict[str, Any]], base_path: Path) -> Dict[str, Any]:
    meta_missing = 0
    id_missing = 0
    ddf_files = 0

    for f in files:
        ext = f.get("ext", "")
        if ext in {".md", ".txt", ".html"}:
            txt = read_text_safe(base_path / f["path"])
            meta = parse_metaheader(txt)
            ddf = parse_ddf(txt)

            if not meta.get("present"):
                meta_missing += 1
            else:
                data = meta.get("data", {}) if meta.get("parsed") else {}
                if isinstance(data, dict) and not data.get("id"):
                    id_missing += 1

            if ddf.get("enabled"):
                ddf_files += 1

    return {
        "files_checked": len(files),
        "meta_missing": meta_missing,
        "id_missing": id_missing,
        "ddf_files": ddf_files,
    }


def load_last_index(metrics_dir: Path) -> Optional[Dict[str, Any]]:
    p = metrics_dir / "last_index.json"
    if not p.exists():
        return None
    try:
        return json.loads(p.read_text(encoding="utf-8"))
    except Exception:
        return None


def save_last_index(metrics_dir: Path, files: List[Dict[str, Any]]) -> None:
    write_json(metrics_dir / "last_index.json", {
        "generated_utc": utc_now_iso(),
        "files": {f["path"]: {"size": f["size"], "mtime_utc": f["mtime_utc"]} for f in files}
    })


def apply_rules(files: List[Dict[str, Any]], standards: Dict[str, Any], metrics_dir: Path) -> Dict[str, Any]:
    warnings: List[Dict[str, Any]] = []
    errors: List[Dict[str, Any]] = []

    if standards["meta_missing"] > 0:
        warnings.append({"id": "STD_META", "msg": "MetaHeader missing in some text files", "count": standards["meta_missing"]})

    # strict by default for IDs (dev kernel)
    if standards["id_missing"] > 0:
        errors.append({"id": "STD_ID", "msg": "Required field 'id' missing in MetaHeader", "count": standards["id_missing"]})

    # append-only heuristic: file size must not shrink vs last run
    last = load_last_index(metrics_dir)
    if last and isinstance(last.get("files"), dict):
        prev = last["files"]
        shrunk = 0
        for f in files:
            p = f["path"]
            if p in prev:
                try:
                    if int(f["size"]) < int(prev[p]["size"]):
                        shrunk += 1
                except Exception:
                    pass
        if shrunk > 0:
            errors.append({"id": "R_APPEND_ONLY", "msg": "Append-only violated (file size decreased)", "count": shrunk})

    save_last_index(metrics_dir, files)

    return {
        "warnings": warnings,
        "errors": errors,
        "warnings_count": len(warnings),
        "errors_count": len(errors),
    }


def collect_metrics(metrics_dir: Path, perf: Dict[str, Any], trend_n: int = 5) -> Dict[str, Any]:
    ensure_dir(metrics_dir)
    append_jsonl(metrics_dir / "performance.log", perf)

    # naive tail trend (ok for early stage)
    deltas = {"delta_files": None, "delta_warnings": None, "delta_errors": None}
    try:
        lines = (metrics_dir / "performance.log").read_text(encoding="utf-8").splitlines()
        tail = []
        for ln in lines[-trend_n:]:
            try:
                tail.append(json.loads(ln))
            except Exception:
                pass
        if len(tail) >= 2:
            deltas["delta_files"] = int(tail[-1].get("files_scanned", 0)) - int(tail[-2].get("files_scanned", 0))
            deltas["delta_warnings"] = int(tail[-1].get("warnings", 0)) - int(tail[-2].get("warnings", 0))
            deltas["delta_errors"] = int(tail[-1].get("errors", 0)) - int(tail[-2].get("errors", 0))
    except Exception:
        pass

    lt_path = metrics_dir / "longterm.json"
    lt = {}
    if lt_path.exists():
        try:
            lt = json.loads(lt_path.read_text(encoding="utf-8"))
        except Exception:
            lt = {}
    if not lt:
        lt = {
            "first_run_utc": perf.get("timestamp_utc"),
            "total_runs": 0,
            "total_errors_seen": 0,
            "total_warnings_seen": 0,
        }
    lt["last_run_utc"] = perf.get("timestamp_utc")
    lt["total_runs"] = int(lt.get("total_runs", 0)) + 1
    lt["total_errors_seen"] = int(lt.get("total_errors_seen", 0)) + int(perf.get("errors", 0))
    lt["total_warnings_seen"] = int(lt.get("total_warnings_seen", 0)) + int(perf.get("warnings", 0))
    write_json(lt_path, lt)

    return {"performance": perf, "trend": deltas, "longterm": lt}


def calc_state(errors_count: int, warnings_count: int) -> str:
    if errors_count > 0:
        return STATE_RED
    if warnings_count > 0:
        return STATE_YELLOW
    return STATE_GREEN


def exit_code_for_state(state: str) -> int:
    if state == STATE_GREEN:
        return EXIT_GREEN
    if state == STATE_YELLOW:
        return EXIT_YELLOW
    return EXIT_RED


def trend_arrow(d: Optional[int]) -> str:
    if d is None:
        return "→"
    if d > 0:
        return "↑"
    if d < 0:
        return "↓"
    return "→"


def render_voice(summary: Dict[str, Any]) -> None:
    print("K501 · DEV RUN")
    print(f"Timestamp(UTC): {summary.get('timestamp_utc')}")
    print(f"State: {summary.get('state')}")
    print(f"Files: {summary.get('files_scanned')}")
    print(f"Warnings: {summary.get('warnings')}")
    print(f"Errors: {summary.get('errors')}")
    print(f"Trend: {summary.get('trend')}")
    print(f"Report: {summary.get('report_path')}")
    print("As I State Iinkognit0.")


def canon_check(cfg: Dict[str, Any], base: Path) -> Tuple[bool, Dict[str, Any]]:
    canon_cfg = cfg.get("canon", {})
    required = bool(canon_cfg.get("required", False))  # default off for fresh tests
    manifest_path = canon_cfg.get("manifest", "00_Grundsaetze/CANON_MANIFEST.json")

    if not required:
        return True, {"required": False, "state": "SKIPPED"}

    mf = (base / manifest_path).resolve()
    if not mf.exists():
        return False, {"required": True, "state": "FAIL", "reason": "manifest_missing", "manifest": str(mf)}

    try:
        manifest = json.loads(mf.read_text(encoding="utf-8"))
    except Exception as e:
        return False, {"required": True, "state": "FAIL", "reason": "manifest_parse_error", "error": str(e), "manifest": str(mf)}

    files = manifest.get("files", [])
    bad = []
    ok = 0
    for it in files:
        p = it.get("path")
        exp = it.get("sha256")
        if not p or not exp:
            bad.append({"path": p, "reason": "missing_path_or_hash"})
            continue
        fp = base / p
        if not fp.exists():
            bad.append({"path": p, "reason": "missing_file"})
            continue
        act = sha256_file(fp)
        if act.lower() != str(exp).lower():
            bad.append({"path": p, "reason": "hash_mismatch", "expected": exp, "actual": act})
        else:
            ok += 1

    return (len(bad) == 0), {
        "required": True,
        "state": "OK" if len(bad) == 0 else "FAIL",
        "files_ok": ok,
        "files_failed": len(bad),
        "failed": bad[:25],
        "manifest": str(mf),
    }


def bootstrap_kernel(ctx: KernelContext) -> int:
    base = Path(ctx.base_path).resolve()
    out_dir = base / "out"
    logs_dir = base / "logs"
    metrics_dir = base / "metrics"
    ensure_dir(out_dir); ensure_dir(logs_dir); ensure_dir(metrics_dir)

    run_log = logs_dir / "run.log"
    history_log = logs_dir / "history.log"

    append_log(history_log, json.dumps({
        "event": "kernel_run",
        "timestamp_utc": utc_now_iso(),
        "details": {"dsl_path": ctx.dsl_path, "mode": ctx.mode},
    }, ensure_ascii=False, sort_keys=True))

    # 1) Canon gate
    canon_ok, canon = canon_check(ctx.config, base)
    if not canon_ok:
        report = {
            "kernel": {"name": "K501", "mode": ctx.mode},
            "timestamp_utc": utc_now_iso(),
            "state": STATE_RED,
            "canon": canon,
            "analysis": {"warnings": [], "errors": [{"id": "CANON_FAIL", "msg": canon.get("reason", "canon_fail")}]},
        }
        rp = out_dir / "report.json"
        write_json(rp, report)
        append_log(run_log, f"{utc_now_iso()} CANON_FAIL {canon.get('reason','canon_fail')}")
        render_voice({
            "timestamp_utc": report["timestamp_utc"],
            "state": STATE_RED,
            "files_scanned": 0,
            "warnings": 0,
            "errors": 1,
            "trend": "→",
            "report_path": str(rp),
        })
        return EXIT_CANON_FAIL

    # 2) Scan targets
    t0 = time.time()
    files = scan_targets(ctx.config, base)

    # 3) Standards
    standards = enforce_standards(files, base)

    # 4) Analysis
    analysis = apply_rules(files, standards, metrics_dir)

    # 5) Metrics
    duration_ms = int((time.time() - t0) * 1000)
    perf = {
        "run_id": hashlib.sha256((ctx.start_time_utc + ctx.dsl_path).encode("utf-8")).hexdigest()[:12],
        "timestamp_utc": utc_now_iso(),
        "files_scanned": len(files),
        "warnings": int(analysis["warnings_count"]),
        "errors": int(analysis["errors_count"]),
        "ddf_files": int(standards["ddf_files"]),
        "duration_ms": duration_ms,
    }
    metrics = collect_metrics(metrics_dir, perf)

    # 6) Report
    state = calc_state(analysis["errors_count"], analysis["warnings_count"])
    report = {
        "kernel": {"name": "K501", "mode": ctx.mode, "dsl_path": ctx.dsl_path},
        "timestamp_utc": utc_now_iso(),
        "state": state,
        "canon": canon,
        "standards": standards,
        "analysis": analysis,
        "metrics": metrics,
        "artifacts": {"report_json": "out/report.json", "logs": "logs/", "metrics": "metrics/"},
    }
    rp = out_dir / "report.json"
    write_json(rp, report)
    append_log(run_log, f"{utc_now_iso()} RUN state={state} files={len(files)} warn={analysis['warnings_count']} err={analysis['errors_count']}")

    # 7) Voice
    render_voice({
        "timestamp_utc": report["timestamp_utc"],
        "state": state,
        "files_scanned": len(files),
        "warnings": analysis["warnings_count"],
        "errors": analysis["errors_count"],
        "trend": trend_arrow(metrics["trend"]["delta_warnings"]),
        "report_path": str(rp),
    })

    return exit_code_for_state(state)


if __name__ == "__main__":
    # direct run fallback (optional)
    raise SystemExit(bootstrap_kernel(KernelContext(
        config={"targets":{"root":"."}},
        mode="dev",
        start_time_utc=utc_now_iso(),
        base_path=str(Path.cwd().resolve()),
        dsl_path="(direct)",
    )))
PY
chmod +x k501.py

echo "[QuietHarbor] writing k501.dsl.yaml"
cat > k501.dsl.yaml <<'YAML'
kernel:
  name: QuietHarbor
  version: "0.1"
  mode_default: dev

# Canon is OFF by default for fresh test projects.
# Flip required: true once you have a CANON_MANIFEST.json in place.
canon:
  required: false
  manifest: "00_Grundsaetze/CANON_MANIFEST.json"

targets:
  root: "."
  include:
    - "**/*.md"
    - "**/*.txt"
    - "**/*.yaml"
    - "**/*.yml"
    - "**/*.json"
    - "**/*.html"
  exclude:
    - "**/.git/**"
    - "**/node_modules/**"
    - "**/.obsidian/**"
    - "**/out/**"
    - "**/logs/**"
    - "**/metrics/**"

# Communication policy: OFF by default (explicit activation only) — prepared for Neo.
comm:
  enabled: false
  transmit: false
  read: true
YAML

echo "[QuietHarbor] writing .gitignore"
cat > .gitignore <<'TXT'
.venv/
__pycache__/
out/
logs/
metrics/
TXT

echo ""
echo "[QuietHarbor] DONE."
echo "Run:"
echo "  source .venv/bin/activate"
echo "  python loader.py run k501.dsl.yaml"
echo ""
echo "Artifacts:"
echo "  out/report.json"
echo "  logs/run.log"
echo "  metrics/performance.log"