#!/usr/bin/env python3
"""
Eternal Diamond Shell (DEV Kernel) — single file, stdlib-only

Core Intent:
- read-first
- append-only canonical artifacts
- append-only events
- deterministic-ish artifacts
- COMM default OFF (no network)
- mobile-friendly (Python stdlib; SQLite)

NOT:
- no self-encrypting payloads
- no dynamic/obfuscated encryption generation
Encryption: OS-level encryption or external audited crypto tool.

As I State Iinkognit0.
"""

from __future__ import annotations
import argparse
import datetime as _dt
import hashlib
import html
import json
import sqlite3
import zipfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple


# ============================
# Core config
# ============================

@dataclass(frozen=True)
class KernelConfig:
    root: Path = Path("earc")
    comm_default: str = "OFF"
    policy_write: str = "append_only"
    mode: str = "DEV"
    state: str = "FROZEN"


# ============================
# Utilities
# ============================

def utc_now() -> str:
    return _dt.datetime.utcnow().replace(microsecond=0).isoformat() + "Z"

def utc_tag() -> str:
    return _dt.datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")

def rfc2822_now_gmt() -> str:
    return _dt.datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")

def sha256_file(p: Path) -> str:
    h = hashlib.sha256()
    with p.open("rb") as f:
        for b in iter(lambda: f.read(8192), b""):
            h.update(b)
    return "sha256:" + h.hexdigest()

def ensure_dirs(cfg: KernelConfig) -> None:
    paths = [
        cfg.root / "diamond" / "superkorns",
        cfg.root / "vault" / "canon",
        cfg.root / "vault" / "frames",
        cfg.root / "vault" / "packs",
        cfg.root / "vault" / "superpacks",
        cfg.root / "vault" / "sources",
        cfg.root / "vault" / "logs",
        cfg.root / "index" / "migrations",
        cfg.root / "index" / "manifests",
        cfg.root / "index" / "freezes",
        cfg.root / "feeds" / "ephemeral",
        cfg.root / "exports",
    ]
    for p in paths:
        p.mkdir(parents=True, exist_ok=True)

def write_append_only(path: Path, content: str) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        raise FileExistsError(f"append-only violation: {path}")
    path.write_text(content, encoding="utf-8")
    return path

def write_ephemeral(path: Path, content: str) -> Path:
    """
    EPHEMERAL POINTER — NOT INDEXED, NOT CANONICAL
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    return path


# ============================
# SQLite
# ============================

def db_path(cfg: KernelConfig) -> Path:
    return cfg.root / "index" / "earc.sqlite"

SCHEMA_SQL = """
BEGIN;

CREATE TABLE IF NOT EXISTS artifacts (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  path TEXT NOT NULL,
  type TEXT NOT NULL,
  role TEXT,
  status TEXT NOT NULL,
  hash TEXT NOT NULL,
  created_utc TEXT NOT NULL,
  mtime_utc TEXT,
  size_bytes INTEGER,
  source TEXT,
  UNIQUE(path, hash)
);

CREATE TABLE IF NOT EXISTS events (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp_utc TEXT NOT NULL,
  event TEXT NOT NULL,
  details TEXT
);

COMMIT;
"""

def db_connect(cfg: KernelConfig) -> sqlite3.Connection:
    con = sqlite3.connect(db_path(cfg))
    con.execute("PRAGMA foreign_keys = ON;")
    return con

def db_init_if_needed(cfg: KernelConfig) -> None:
    ensure_dirs(cfg)
    first = not db_path(cfg).exists()
    con = db_connect(cfg)
    cur = con.cursor()
    cur.executescript(SCHEMA_SQL)
    if first:
        cur.execute(
            "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
            (utc_now(), "index_init", "earc sqlite initialized")
        )
    con.commit()
    con.close()


# ============================
# Indexing
# ============================

def detect_type_from_path(rel_path: str) -> str:
    p = rel_path.replace("\\", "/").lstrip("./")
    if p.startswith("vault/frames/"):
        return "frame"
    if p.startswith("vault/packs/"):
        return "pack"
    if p.startswith("vault/superpacks/"):
        return "superpack"
    if p.startswith("diamond/superkorns/"):
        return "superkorn"
    if p.startswith("vault/canon/") or p.startswith("diamond/"):
        return "canon"
    return "other"

def scan_tree(base: Path) -> List[Path]:
    if not base.exists():
        return []
    return [p for p in base.rglob("*") if p.is_file()]

def index_paths(cfg: KernelConfig, paths: List[Path], source: str = "iarc") -> None:
    con = db_connect(cfg)
    cur = con.cursor()
    now = utc_now()

    for p in paths:
        try:
            rel = str(p.relative_to(cfg.root)).replace("\\", "/")
        except Exception:
            continue
        h = sha256_file(p)
        st = p.stat()
        cur.execute(
            """
            INSERT OR IGNORE INTO artifacts
            (path,type,role,status,hash,created_utc,mtime_utc,size_bytes,source)
            VALUES (?,?,?,?,?,?,?,?,?)
            """,
            (
                rel,
                detect_type_from_path(rel),
                None,
                "fixed",
                h,
                now,
                _dt.datetime.utcfromtimestamp(st.st_mtime).isoformat() + "Z",
                int(st.st_size),
                source,
            )
        )

    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (now, "vault_scan", "read-only scan completed")
    )
    con.commit()
    con.close()

def scan_and_index(cfg: KernelConfig) -> None:
    index_paths(cfg, scan_tree(cfg.root / "vault"))
    index_paths(cfg, scan_tree(cfg.root / "diamond"))


# ============================
# Orchestration: validate
# ============================

def validate(cfg: KernelConfig) -> dict:
    db_init_if_needed(cfg)

    report = {
        "generated_utc": utc_now(),
        "kernel": {"mode": cfg.mode, "state": cfg.state, "comm": cfg.comm_default},
        "ok": True,
        "checks": [],
        "warnings": [],
        "errors": [],
    }

    def ok(name, d=None): report["checks"].append({"name": name, "details": d})
    def warn(name, d=None): report["warnings"].append({"name": name, "details": d})
    def err(name, d=None):
        report["errors"].append({"name": name, "details": d})
        report["ok"] = False

    con = db_connect(cfg)
    cur = con.cursor()

    # SQLite integrity
    cur.execute("PRAGMA integrity_check;")
    if cur.fetchone()[0] != "ok":
        err("sqlite_integrity")
    else:
        ok("sqlite_integrity")

    # Ephemeral must not be indexed
    cur.execute("""
        SELECT path FROM artifacts
        WHERE path LIKE 'feeds/ephemeral/%'
           OR path LIKE 'index/manifests/ephemeral_%'
           OR path LIKE 'index/freezes/ephemeral_%'
    """)
    eph = [r[0] for r in cur.fetchall()]
    if eph:
        err("ephemeral_indexed", eph[:20])
    else:
        ok("ephemeral_not_indexed")

    # Drift heuristic (warning only)
    cur.execute("""
        SELECT path, COUNT(DISTINCT hash)
        FROM artifacts
        GROUP BY path
        HAVING COUNT(DISTINCT hash) > 1
    """)
    drift = cur.fetchall()
    if drift:
        warn("path_drift_detected", drift[:20])
    else:
        ok("no_path_drift")

    con.close()
    return report


# ============================
# CLI
# ============================

def main():
    cfg = KernelConfig()
    ap = argparse.ArgumentParser(prog="diamond_shell")
    sub = ap.add_subparsers(dest="cmd", required=True)

    sub.add_parser("scan")
    sub.add_parser("validate")

    args = ap.parse_args()

    if args.cmd == "scan":
        db_init_if_needed(cfg)
        scan_and_index(cfg)
    elif args.cmd == "validate":
        rep = validate(cfg)
        print(json.dumps(rep, indent=2, ensure_ascii=False))
        raise SystemExit(0 if rep["ok"] else 2)

if __name__ == "__main__":
    main()