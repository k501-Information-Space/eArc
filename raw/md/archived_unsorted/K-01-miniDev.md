#!/usr/bin/env python3
"""
K501 Development Kernel (K-01) — minimal, fast, deterministic
- Designed to be called by loader.py (ML-01)
- Pipeline (fixed order):
  1) Canon Gate (blocker)
  2) Standards (File / MetaHeader / DDF)
  3) Analysis (Rules)
  4) Metrics (Performance / Trend / Long-term)
  5) Report (JSON + optional MD)
  6) Logs + Voice output

Exit codes:
  0 GREEN, 1 YELLOW, 2 RED, 3 CANON_FAIL, 4 DSL_FAIL
"""

from __future__ import annotations

import json
import os
import re
import fnmatch
import hashlib
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

# Optional YAML support (MetaHeader parsing)
try:
    from ruamel.yaml import YAML  # type: ignore
except Exception:  # pragma: no cover
    YAML = None


# =========================
# Exit codes / States
# =========================
EXIT_GREEN = 0
EXIT_YELLOW = 1
EXIT_RED = 2
EXIT_CANON_FAIL = 3
EXIT_DSL_FAIL = 4

STATE_GREEN = "GREEN"
STATE_YELLOW = "YELLOW"
STATE_RED = "RED"


# =========================
# Context (must match loader.py)
# =========================
@dataclass(frozen=True)
class KernelContext:
    config: Dict[str, Any]
    mode: str
    start_time_utc: str
    base_path: str
    dsl_path: str


# =========================
# Small utilities
# =========================
def utc_now_iso() -> str:
    return datetime.now(timezone.utc).replace(microsecond=0).isoformat()


def ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)


def read_text_safe(path: Path, limit_bytes: int = 2_000_000) -> str:
    # Avoid massive reads; sufficient for headers/DDF markers.
    with path.open("rb") as f:
        data = f.read(limit_bytes)
    return data.decode("utf-8", errors="replace")


def sha256_file(path: Path, chunk: int = 1024 * 1024) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        while True:
            b = f.read(chunk)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def write_json(path: Path, obj: Any) -> None:
    ensure_dir(path.parent)
    # deterministic: sort_keys + stable separators
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


def deep_get(d: Dict[str, Any], keys: List[str], default: Any = None) -> Any:
    cur: Any = d
    for k in keys:
        if not isinstance(cur, dict) or k not in cur:
            return default
        cur = cur[k]
    return cur


# =========================
# Canon Gate (P0)
# =========================
def canon_check(ctx: KernelContext, out: Dict[str, Any]) -> Tuple[bool, Dict[str, Any]]:
    cfg = ctx.config.get("canon", None)

    # Default policy for K501: canon required unless explicitly disabled
    required = True if cfg is None else bool(cfg.get("required", True))
    manifest_path = None
    status_required = "kanonisch"

    if cfg:
        status_required = cfg.get("status_required", status_required)
        manifest_path = deep_get(cfg, ["manifest", "file"], None)

    if not required:
        return True, {
            "required": False,
            "state": "SKIPPED",
            "manifest_ok": None,
            "files_ok": 0,
            "files_failed": 0,
        }

    if not manifest_path:
        # Default location
        manifest_path = "00_Grundsaetze/CANON_MANIFEST.json"

    manifest_file = Path(ctx.base_path) / manifest_path
    if not manifest_file.exists():
        return False, {
            "required": True,
            "state": "FAIL",
            "reason": "manifest_missing",
            "manifest": str(manifest_file),
        }

    try:
        manifest = json.loads(manifest_file.read_text(encoding="utf-8"))
    except Exception as e:
        return False, {
            "required": True,
            "state": "FAIL",
            "reason": "manifest_parse_error",
            "error": str(e),
            "manifest": str(manifest_file),
        }

    canon_meta = manifest.get("canon", {})
    canon_status = canon_meta.get("status", None)
    if canon_status != status_required:
        return False, {
            "required": True,
            "state": "FAIL",
            "reason": "status_mismatch",
            "status_found": canon_status,
            "status_required": status_required,
            "manifest": str(manifest_file),
        }

    files = manifest.get("files", [])
    ok = 0
    bad = 0
    failed: List[Dict[str, Any]] = []

    for item in files:
        p = item.get("path")
        expected = item.get("sha256")
        if not p or not expected:
            bad += 1
            failed.append({"path": p, "reason": "missing_path_or_hash"})
            continue

        abs_path = Path(ctx.base_path) / p
        if not abs_path.exists():
            bad += 1
            failed.append({"path": p, "reason": "missing_file"})
            continue

        actual = sha256_file(abs_path)
        if actual.lower() != str(expected).lower():
            bad += 1
            failed.append({"path": p, "reason": "hash_mismatch", "expected": expected, "actual": actual})
        else:
            ok += 1

    result = {
        "required": True,
        "state": "OK" if bad == 0 else "FAIL",
        "manifest": str(manifest_file),
        "canon_id": canon_meta.get("id"),
        "canon_version": canon_meta.get("version"),
        "status": canon_status,
        "files_ok": ok,
        "files_failed": bad,
        "failed": failed[:25],  # cap
    }

    return bad == 0, result


# =========================
# Target scanning (fast, deterministic)
# =========================
def normalize_patterns(patterns: List[str]) -> List[str]:
    return [p.replace("\\", "/") for p in patterns]


def match_any(path_posix: str, patterns: List[str]) -> bool:
    for pat in patterns:
        if fnmatch.fnmatch(path_posix, pat):
            return True
    return False


def scan_targets(cfg: Dict[str, Any], base_path: Path) -> List[Dict[str, Any]]:
    targets = cfg.get("targets", {}) if isinstance(cfg.get("targets", {}), dict) else {}
    root = targets.get("root", ".")
    root_path = (base_path / root).resolve()

    include = targets.get("include", ["**/*.md", "**/*.yaml", "**/*.yml", "**/*.json", "**/*.txt", "**/*.html"])
    exclude = targets.get("exclude", ["**/.git/**", "**/node_modules/**", "**/dist/**", "**/build/**", "**/out/**", "**/logs/**", "**/metrics/**"])

    include_pats = normalize_patterns([str(p) for p in include])
    exclude_pats = normalize_patterns([str(p) for p in exclude])

    out: List[Dict[str, Any]] = []
    # deterministic walk: sort dirs/files
    for dirpath, dirnames, filenames in os.walk(root_path):
        dirnames.sort()
        filenames.sort()

        for name in filenames:
            abs_path = Path(dirpath) / name
            rel = abs_path.relative_to(base_path).as_posix()

            # include/exclude matching
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


# =========================
# MetaHeader (YAML Frontmatter) + DDF
# =========================
_FRONT_RE = re.compile(r"^---\s*\n(.*?)\n---\s*\n", re.DOTALL)

def parse_metaheader(text: str) -> Dict[str, Any]:
    m = _FRONT_RE.match(text)
    if not m:
        return {"present": False}

    if YAML is None:
        # Minimal fallback: do not parse, only mark present
        return {"present": True, "parsed": False}

    y = YAML(typ="safe")
    try:
        data = y.load(m.group(1)) or {}
        if not isinstance(data, dict):
            return {"present": True, "parsed": True, "data": {}}
        return {"present": True, "parsed": True, "data": data}
    except Exception:
        return {"present": True, "parsed": False}

def parse_ddf_levels(text: str) -> Dict[str, Any]:
    # Supports HTML comment style markers: <!-- DDF:L0 -->
    levels = set(re.findall(r"DDF\s*:\s*(L[0-3])", text, flags=re.IGNORECASE))
    return {"enabled": bool(levels), "levels": sorted({lv.upper() for lv in levels})}


# =========================
# Standards + Rules (minimal but real)
# =========================
def enforce_standards(files: List[Dict[str, Any]], base_path: Path) -> Dict[str, Any]:
    allowed_ext = {".md", ".txt", ".yaml", ".yml", ".json", ".html", ".css", ".ttf", ".otf", ".png", ".jpg", ".jpeg", ".svg"}

    meta_missing = 0
    id_missing = 0
    ddf_enabled = 0

    per_file: List[Dict[str, Any]] = []

    for f in files:
        p = base_path / f["path"]
        ext = f.get("ext", "")

        ok_type = ext in allowed_ext or ext == ""
        meta = {"present": False}
        ddf = {"enabled": False, "levels": []}

        if ext in {".md", ".txt", ".html"}:
            txt = read_text_safe(p)
            meta = parse_metaheader(txt)
            ddf = parse_ddf_levels(txt)

            if not meta.get("present"):
                meta_missing += 1
            else:
                data = meta.get("data", {}) if meta.get("parsed") else {}
                if isinstance(data, dict) and not data.get("id"):
                    id_missing += 1

            if ddf.get("enabled"):
                ddf_enabled += 1

        per_file.append({
            "path": f["path"],
            "ext": ext,
            "type_ok": ok_type,
            "meta_present": bool(meta.get("present")),
            "meta_parsed": bool(meta.get("parsed")),
            "ddf": ddf,
        })

    return {
        "files_checked": len(files),
        "type_violations": sum(1 for x in per_file if not x["type_ok"]),
        "meta_missing": meta_missing,
        "id_missing": id_missing,
        "ddf_files": ddf_enabled,
        "sample": per_file[:50],  # cap
    }


def load_last_index(metrics_dir: Path) -> Optional[Dict[str, Any]]:
    p = metrics_dir / "last_index.json"
    if not p.exists():
        return None
    try:
        return json.loads(p.read_text(encoding="utf-8"))
    except Exception:
        return None


def save_last_index(metrics_dir: Path, index: Dict[str, Any]) -> None:
    write_json(metrics_dir / "last_index.json", index)


def apply_rules(cfg: Dict[str, Any], files: List[Dict[str, Any]], standards: Dict[str, Any], metrics_dir: Path) -> Dict[str, Any]:
    rules = cfg.get("rules", [])
    if not isinstance(rules, list):
        rules = []

    warnings: List[Dict[str, Any]] = []
    errors: List[Dict[str, Any]] = []

    # Built-in minimal checks (even if rules list empty)
    # R: type violations => warn
    if standards.get("type_violations", 0) > 0:
        warnings.append({"id": "STD_TYPE", "msg": "File type violations detected", "count": standards["type_violations"]})

    # R: meta missing => warn (project can tighten later)
    if standards.get("meta_missing", 0) > 0:
        warnings.append({"id": "STD_META", "msg": "MetaHeader missing in some text files", "count": standards["meta_missing"]})

    # R: id missing => error by default (can be softened later)
    if standards.get("id_missing", 0) > 0:
        errors.append({"id": "STD_ID", "msg": "Required field 'id' missing in MetaHeader", "count": standards["id_missing"]})

    # Append-only (pragmatic): file size must not shrink vs last index
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

    # Optional user-defined rules (minimal dispatcher)
    for r in rules:
        if not isinstance(r, dict):
            continue
        rid = r.get("id", "RULE")
        level = (r.get("level") or "warn").lower()
        check = r.get("check")

        if check == "id_required":
            # Already handled above; include marker for traceability
            continue
        if check == "append_only":
            continue
        # Unknown checks are warned (dev transparency)
        warnings.append({"id": rid, "msg": f"Unknown rule check '{check}' (ignored in v0.1)"})

    # Update last index (for next run diffs)
    index = {"generated_utc": utc_now_iso(), "files": {f["path"]: {"size": f["size"], "mtime_utc": f["mtime_utc"]} for f in files}}
    save_last_index(metrics_dir, index)

    return {
        "warnings": warnings,
        "errors": errors,
        "warnings_count": len(warnings),
        "errors_count": len(errors),
    }


# =========================
# Metrics: Performance / Trend / Long-term
# =========================
def read_json(path: Path) -> Optional[Dict[str, Any]]:
    if not path.exists():
        return None
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception:
        return None


def collect_metrics(metrics_dir: Path, perf: Dict[str, Any], trend_n: int = 5) -> Dict[str, Any]:
    ensure_dir(metrics_dir)

    # Performance log (jsonl)
    perf_line = dict(perf)
    append_jsonl(metrics_dir / "performance.log", perf_line)

    # Trend: compare with last N-1 entries
    # (Cheap: read tail by scanning; acceptable for small logs. For huge logs, optimize later.)
    last_vals: List[Dict[str, Any]] = []
    perf_log = metrics_dir / "performance.log"
    try:
        lines = perf_log.read_text(encoding="utf-8").splitlines()
        for ln in lines[-trend_n:]:
            try:
                last_vals.append(json.loads(ln))
            except Exception:
                pass
    except Exception:
        pass

    def delta(key: str) -> Optional[int]:
        if len(last_vals) < 2:
            return None
        try:
            return int(last_vals[-1].get(key, 0)) - int(last_vals[-2].get(key, 0))
        except Exception:
            return None

    trend = {
        "window": min(trend_n, len(last_vals)),
        "delta_files": delta("files_scanned"),
        "delta_warnings": delta("warnings"),
        "delta_errors": delta("errors"),
    }

    # Long-term stats
    lt_path = metrics_dir / "longterm.json"
    lt = read_json(lt_path) or {
        "first_run_utc": perf.get("timestamp_utc"),
        "total_runs": 0,
        "total_errors_seen": 0,
        "total_warnings_seen": 0,
        "freezes_count": 0,
        "canon_changes_count": 0,
    }
    lt["last_run_utc"] = perf.get("timestamp_utc")
    lt["total_runs"] = int(lt.get("total_runs", 0)) + 1
    lt["total_errors_seen"] = int(lt.get("total_errors_seen", 0)) + int(perf.get("errors", 0))
    lt["total_warnings_seen"] = int(lt.get("total_warnings_seen", 0)) + int(perf.get("warnings", 0))
    write_json(lt_path, lt)

    return {"performance": perf, "trend": trend, "longterm": lt}


# =========================
# Report + Voice
# =========================
def calc_state(canon_ok: bool, errors_count: int, warnings_count: int) -> str:
    if not canon_ok or errors_count > 0:
        return STATE_RED
    if warnings_count > 0:
        return STATE_YELLOW
    return STATE_GREEN


def exit_code_for_state(state: str, canon_ok: bool) -> int:
    if not canon_ok:
        return EXIT_CANON_FAIL
    if state == STATE_GREEN:
        return EXIT_GREEN
    if state == STATE_YELLOW:
        return EXIT_YELLOW
    return EXIT_RED


def trend_arrow(delta: Optional[int]) -> str:
    if delta is None:
        return "→"
    if delta > 0:
        return "↑"
    if delta < 0:
        return "↓"
    return "→"


def render_voice(summary: Dict[str, Any]) -> None:
    # Calm, deterministic, minimal blocks
    print("K501 · DEV RUN")
    print(f"Timestamp(UTC): {summary.get('timestamp_utc')}")
    print(f"Mode: {summary.get('mode')}")
    print("")
    print(f"State: {summary.get('state')}")
    print(f"Canon: {summary.get('canon_state')}")
    print(f"Files: {summary.get('files_scanned')}")
    print(f"Warnings: {summary.get('warnings')}")
    print(f"Errors: {summary.get('errors')}")
    print(f"Trend: {summary.get('trend_arrow')}")
    print("")
    print(f"Report: {summary.get('report_path')}")
    print(f"Log: {summary.get('run_log_path')}")
    print(f"Metrics: {summary.get('metrics_dir')}")
    print("As I State Iinkognit0.")


# =========================
# Kernel entrypoint (called by loader)
# =========================
def bootstrap_kernel(ctx: KernelContext) -> int:
    base = Path(ctx.base_path).resolve()

    out_dir = Path(deep_get(ctx.config, ["run", "output_dir"], "out"))
    out_dir = (base / out_dir).resolve()

    logs_dir = base / "logs"
    metrics_dir = base / "metrics"
    ensure_dir(out_dir)
    ensure_dir(logs_dir)
    ensure_dir(metrics_dir)

    run_log = logs_dir / "run.log"
    history_log = logs_dir / "history.log"

    append_log(history_log, json.dumps({
        "event": "kernel_run",
        "timestamp_utc": utc_now_iso(),
        "context": "k501_dev",
        "details": {"dsl_path": ctx.dsl_path, "mode": ctx.mode},
    }, ensure_ascii=False, sort_keys=True))

    # 1) Canon gate
    canon_ok, canon_result = canon_check(ctx, {})
    if not canon_ok:
        # Write minimal report for traceability
        report = {
            "kernel": {"name": "K501", "mode": ctx.mode},
            "timestamp_utc": utc_now_iso(),
            "state": STATE_RED,
            "canon": canon_result,
            "analysis": {"warnings": [], "errors": [{"id": "CANON_FAIL", "msg": canon_result.get("reason", "canon_fail")}]},
        }
        report_path = out_dir / "report.json"
        write_json(report_path, report)
        append_log(run_log, f"{utc_now_iso()} CANON_FAIL {canon_result.get('reason')}")
        render_voice({
            "timestamp_utc": report["timestamp_utc"],
            "mode": ctx.mode,
            "state": STATE_RED,
            "canon_state": "FAIL",
            "files_scanned": 0,
            "warnings": 0,
            "errors": 1,
            "trend_arrow": "→",
            "report_path": str(report_path),
            "run_log_path": str(run_log),
            "metrics_dir": str(metrics_dir),
        })
        return EXIT_CANON_FAIL

    # 2) Scan targets
    files = scan_targets(ctx.config, base)

    # 3) Standards
    standards = enforce_standards(files, base)

    # 4) Analysis / Rules
    analysis = apply_rules(ctx.config, files, standards, metrics_dir)

    # 5) Metrics
    t0 = datetime.fromisoformat(ctx.start_time_utc.replace("Z", "+00:00")) if "T" in ctx.start_time_utc else datetime.now(timezone.utc)
    duration_ms = int((datetime.now(timezone.utc) - t0).total_seconds() * 1000)

    perf = {
        "run_id": hashlib.sha256((ctx.start_time_utc + ctx.dsl_path).encode("utf-8")).hexdigest()[:12],
        "timestamp_utc": utc_now_iso(),
        "files_scanned": len(files),
        "warnings": int(analysis.get("warnings_count", 0)),
        "errors": int(analysis.get("errors_count", 0)),
        "canon_state": "OK",
        "ddf_files": int(standards.get("ddf_files", 0)),
        "duration_ms": duration_ms,
    }
    metrics = collect_metrics(metrics_dir, perf, trend_n=5)

    # 6) Report
    state = calc_state(True, analysis["errors_count"], analysis["warnings_count"])
    report_obj = {
        "kernel": {
            "name": "K501",
            "mode": ctx.mode,
            "dsl_path": ctx.dsl_path,
            "base_path": str(base),
        },
        "timestamp_utc": utc_now_iso(),
        "state": state,
        "canon": canon_result,
        "standards": standards,
        "analysis": analysis,
        "metrics": metrics,
        "artifacts": {
            "report_json": "out/report.json",
            "run_log": "logs/run.log",
            "history_log": "logs/history.log",
            "metrics_dir": "metrics/",
        },
    }

    report_path = out_dir / "report.json"
    write_json(report_path, report_obj)

    # 7) Logs
    append_log(run_log, f"{utc_now_iso()} RUN state={state} files={len(files)} warn={analysis['warnings_count']} err={analysis['errors_count']}")

    # 8) Voice
    summary = {
        "timestamp_utc": report_obj["timestamp_utc"],
        "mode": ctx.mode,
        "state": state,
        "canon_state": canon_result.get("state", "OK"),
        "files_scanned": len(files),
        "warnings": analysis["warnings_count"],
        "errors": analysis["errors_count"],
        "trend_arrow": trend_arrow(metrics.get("trend", {}).get("delta_warnings")),
        "report_path": str(report_path),
        "run_log_path": str(run_log),
        "metrics_dir": str(metrics_dir),
    }
    render_voice(summary)

    return exit_code_for_state(state, True)