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
import os
import sys
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, Optional

# YAML is optional at runtime, but recommended for the DSL
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
    return {}  # unreachable


def resolve_dsl_path(arg: str) -> Path:
    """
    arg can be:
      - path to a DSL file
      - directory (we look for default candidates)
      - "." meaning current directory
    """
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

    # If arg is not existing path, try interpreting as filename in cwd
    cwd = Path.cwd().resolve()
    cand = (cwd / arg).resolve()
    if cand.exists() and cand.is_file():
        return cand

    die(f"DSL path not found: {arg}", 4)
    return Path()  # unreachable


def basic_sanity(config: Dict[str, Any]) -> None:
    """
    Keep this intentionally minimal (miniloader is 'dumb by design').
    Kernel does full validation + canon gate + standards.
    """
    if not isinstance(config, dict):
        die("DSL must load to an object/mapping", 4)

    # Very light expectations (optional in early stage)
    kernel = config.get("kernel", {})
    if kernel and not isinstance(kernel, dict):
        die("Field 'kernel' must be an object", 4)

    # allow missing fields; kernel will enforce if required
    # but ensure config isn't empty by accident (soft warning)
    if not config:
        die("DSL is empty. Provide at least {kernel:{...}} or {targets:{...}}", 4)


def import_kernel_entry():
    """
    Import the kernel entrypoint lazily so the miniloader stays minimal.
    Expected kernel module: k501.py with function: bootstrap_kernel(ctx: KernelContext) -> int
    """
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
    # kernel returns an exit code (0 green, 1 yellow, 2 red, 3 canon fail, 4 dsl fail)
    return int(bootstrap_kernel(ctx))


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        die("Usage: loader.py run <dsl-path|dir|.>", 4)

    cmd = argv[1].lower().strip()

    if cmd == "run":
        if len(argv) < 3:
            # default to current directory
            dsl_arg = "."
        else:
            dsl_arg = argv[2]
        return cmd_run(dsl_arg, mode="dev")

    die(f"Unknown command: {cmd}. Supported: run", 4)
    return 4


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))