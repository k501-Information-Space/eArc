#!/usr/bin/env python3
"""
Eternal Diamond Shell (DEV Kernel) — single file, stdlib-only

What it is:
- read-first
- append-only events
- deterministic-ish artifacts
- COMM default OFF (no network)
- mobile-friendly (Python stdlib; SQLite)

What it is NOT:
- no self-encrypting payloads
- no dynamic/obfuscated encryption generation
If you need encryption: use OS-level encryption (iOS Data Protection / encrypted container)
or an external audited crypto tool. This kernel stays clean + auditable.

As I State Iinkognit0.
"""

from __future__ import annotations
import argparse
import datetime as _dt
import hashlib
import html
import json
import os
import sqlite3
import zipfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

# ----------------------------
# Core config (calm, minimal)
# ----------------------------

@dataclass(frozen=True)
class KernelConfig:
    root: Path = Path("earc")
    comm_default: str = "OFF"          # explicit-only elsewhere
    policy_write: str = "append_only"  # no overwrite for artifacts
    mode: str = "DEV"
    state: str = "FROZEN"


# ----------------------------
# Utilities
# ----------------------------

def utc_now() -> str:
    return _dt.datetime.utcnow().replace(microsecond=0).isoformat() + "Z"

def rfc2822_now_gmt() -> str:
    return _dt.datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")

def sha256_file(p: Path) -> str:
    h = hashlib.sha256()
    with p.open("rb") as f:
        for b in iter(lambda: f.read(8192), b""):
            h.update(b)
    return "sha256:" + h.hexdigest()

def ensure_dirs(cfg: KernelConfig) -> None:
    (cfg.root / "diamond" / "superkorns").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "canon").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "frames").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "packs").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "superpacks").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "sources").mkdir(parents=True, exist_ok=True)
    (cfg.root / "vault" / "logs").mkdir(parents=True, exist_ok=True)
    (cfg.root / "index" / "migrations").mkdir(parents=True, exist_ok=True)
    (cfg.root / "feeds").mkdir(parents=True, exist_ok=True)
    (cfg.root / "exports").mkdir(parents=True, exist_ok=True)

def db_path(cfg: KernelConfig) -> Path:
    return cfg.root / "index" / "earc.sqlite"


# ----------------------------
# SQLite schema (index only)
# ----------------------------

SCHEMA_SQL = """
BEGIN;

CREATE TABLE IF NOT EXISTS artifacts (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  path TEXT NOT NULL,
  type TEXT NOT NULL,          -- superkorn | frame | pack | superpack | canon | other
  role TEXT,                   -- ethos | invariant | context | voice | null
  status TEXT NOT NULL,        -- drafted | fixed | archived
  hash TEXT NOT NULL,
  created_utc TEXT NOT NULL,
  source TEXT,                 -- iarc | external | null
  UNIQUE(path, hash)
);

CREATE TABLE IF NOT EXISTS relations (
  from_id INTEGER,
  to_id INTEGER,
  relation TEXT,
  FOREIGN KEY(from_id) REFERENCES artifacts(id),
  FOREIGN KEY(to_id) REFERENCES artifacts(id)
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
    return sqlite3.connect(db_path(cfg))

def db_init(cfg: KernelConfig) -> None:
    ensure_dirs(cfg)
    con = db_connect(cfg)
    cur = con.cursor()
    cur.executescript(SCHEMA_SQL)
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (utc_now(), "index_init", "earc sqlite v1 initialized")
    )
    con.commit()
    con.close()


# ----------------------------
# Indexing (read vault -> artifacts)
# ----------------------------

def detect_type_from_path(rel_path: str) -> str:
    p = rel_path.replace("\\", "/")
    if p.startswith("vault/frames/"):
        return "frame"
    if p.startswith("vault/packs/"):
        return "pack"
    if p.startswith("vault/superpacks/"):
        return "superpack"
    if p.startswith("vault/canon/") or p.startswith("diamond/"):
        return "canon"
    if p.startswith("diamond/superkorns/"):
        return "superkorn"
    return "other"

def scan_tree(cfg: KernelConfig, base: Path) -> List[Path]:
    if not base.exists():
        return []
    return [p for p in base.rglob("*") if p.is_file()]

def index_paths(cfg: KernelConfig, paths: List[Path], source: str = "iarc") -> Tuple[int, int]:
    """
    Returns (inserted_count, skipped_count).
    """
    con = db_connect(cfg)
    cur = con.cursor()
    inserted = 0
    skipped = 0
    now = utc_now()

    for p in paths:
        rel = str(p.relative_to(cfg.root)).replace("\\", "/")
        h = sha256_file(p)
        typ = detect_type_from_path(rel)
        status = "fixed"  # conservative default
        try:
            cur.execute("""
                INSERT OR IGNORE INTO artifacts
                (path,type,role,status,hash,created_utc,source)
                VALUES (?,?,?,?,?,?,?)
            """, (rel, typ, None, status, h, now, source))
            if cur.rowcount == 1:
                inserted += 1
            else:
                skipped += 1
        except sqlite3.Error:
            skipped += 1

    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (now, "vault_scan", f"read-only scan completed inserted={inserted} skipped={skipped}")
    )
    con.commit()
    con.close()
    return inserted, skipped

def scan_and_index(cfg: KernelConfig) -> None:
    ensure_dirs(cfg)
    vault_files = scan_tree(cfg, cfg.root / "vault")
    diamond_files = scan_tree(cfg, cfg.root / "diamond")
    index_paths(cfg, vault_files, source="iarc")
    index_paths(cfg, diamond_files, source="iarc")


# ----------------------------
# Spirit analysis (mark only)
# ----------------------------

def spirit_mark_patterns(cfg: KernelConfig) -> Path:
    """
    Mark-only heuristic: green/yellow/red based on artifact count.
    Writes a new frame JSON (append-only).
    """
    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute("SELECT COUNT(*), MIN(created_utc), MAX(created_utc) FROM artifacts")
    count, first, last = cur.fetchone()
    con.close()

    level = "green"
    if count and count > 1000:
        level = "yellow"
    if count and count > 10000:
        level = "red"

    frame = {
        "type": "pattern-marker",
        "level": level,
        "artifacts": int(count or 0),
        "window": {"from": first, "to": last},
        "generated_utc": utc_now(),
        "policy": "mark_only",
        "comm": cfg.comm_default
    }

    frames_dir = cfg.root / "vault" / "frames"
    frames_dir.mkdir(parents=True, exist_ok=True)
    fname = f"pattern_{frame['generated_utc'].replace(':','')}.json"
    out = frames_dir / fname
    out.write_text(json.dumps(frame, indent=2), encoding="utf-8")

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (frame["generated_utc"], "pattern_mark", f"level={level} count={count}")
    )
    con.commit()
    con.close()

    # index new frame
    index_paths(cfg, [out], source="iarc")
    return out


# ----------------------------
# Packs / SuperPacks (summaries only)
# ----------------------------

def build_pack(cfg: KernelConfig, last_n: int = 20) -> Optional[Path]:
    frames_dir = cfg.root / "vault" / "frames"
    files = sorted(frames_dir.glob("pattern_*.json"))[-last_n:]
    if not files:
        return None

    items = []
    for f in files:
        try:
            items.append(json.loads(f.read_text(encoding="utf-8")))
        except Exception:
            continue

    now = utc_now()
    latest = items[-1] if items else {}
    pack = {
        "type": "pack",
        "pack_id": f"pack_{now}",
        "generated_utc": now,
        "source_frames": [f.name for f in files],
        "summary": {
            "count_frames": len(items),
            "latest_level": latest.get("level", "green"),
            "latest_artifacts": latest.get("artifacts", 0),
            "policy": "summary_only"
        },
        "notes": "Pack is a calm structural summary. No action implied."
    }

    packs_dir = cfg.root / "vault" / "packs"
    packs_dir.mkdir(parents=True, exist_ok=True)
    out = packs_dir / f"pack_{now.replace(':','')}.json"
    out.write_text(json.dumps(pack, indent=2), encoding="utf-8")

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (now, "pack_build", f"pack={out.name} frames={len(items)}")
    )
    con.commit()
    con.close()

    index_paths(cfg, [out], source="iarc")
    return out

def build_superpack(cfg: KernelConfig, last_n: int = 10) -> Optional[Path]:
    packs_dir = cfg.root / "vault" / "packs"
    files = sorted(packs_dir.glob("pack_*.json"))[-last_n:]
    if not files:
        return None

    items = []
    for f in files:
        try:
            items.append(json.loads(f.read_text(encoding="utf-8")))
        except Exception:
            continue

    now = utc_now()
    levels = [p.get("summary", {}).get("latest_level", "green") for p in items]
    level = "green"
    if "red" in levels:
        level = "red"
    elif "yellow" in levels:
        level = "yellow"

    superpack = {
        "type": "superpack",
        "superpack_id": f"superpack_{now}",
        "generated_utc": now,
        "source_packs": [f.name for f in files],
        "overview": {
            "count_packs": len(items),
            "dominant_level": level,
            "policy": "overview_only"
        },
        "notes": "SuperPack provides calm orientation. No directive, no escalation."
    }

    superpacks_dir = cfg.root / "vault" / "superpacks"
    superpacks_dir.mkdir(parents=True, exist_ok=True)
    out = superpacks_dir / f"superpack_{now.replace(':','')}.json"
    out.write_text(json.dumps(superpack, indent=2), encoding="utf-8")

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (now, "superpack_build", f"superpack={out.name} packs={len(items)}")
    )
    con.commit()
    con.close()

    index_paths(cfg, [out], source="iarc")
    return out


# ----------------------------
# TAT1 (artifact generation only — COMM OFF)
# ----------------------------

def tat1_generate(cfg: KernelConfig, site_link: str = "https://iinkognit0.de/earc-feed/") -> Tuple[Path, Path]:
    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute("SELECT COUNT(*) FROM artifacts")
    count = cur.fetchone()[0]
    con.close()

    now = utc_now()
    title = f"eArc · TAT1 · Status · {now}"
    desc = f"artifacts={count} · comm={cfg.comm_default} · policy=mark_only"

    feeds_dir = cfg.root / "feeds"
    feeds_dir.mkdir(parents=True, exist_ok=True)

    rss_path = feeds_dir / "tat1.rss"
    atom_path = feeds_dir / "tat1.atom"

    rss = f"""<?xml version="1.0" encoding="UTF-8"?>
<rss version="2.0">
<channel>
<title>eArc · TAT1</title>
<link>{html.escape(site_link)}</link>
<description>Local artifact feed (no transmit)</description>
<item>
<title>{html.escape(title)}</title>
<guid isPermaLink="false">{html.escape(now)}</guid>
<pubDate>{html.escape(rfc2822_now_gmt())}</pubDate>
<description>{html.escape(desc)}</description>
</item>
</channel>
</rss>
"""
    rss_path.write_text(rss, encoding="utf-8")

    atom = f"""<?xml version="1.0" encoding="utf-8"?>
<feed xmlns="http://www.w3.org/2005/Atom">
<title>eArc · TAT1</title>
<id>urn:iarc:tat1</id>
<updated>{html.escape(now)}</updated>
<link href="{html.escape(site_link)}" />
<entry>
<title>{html.escape(title)}</title>
<id>urn:iarc:entry:{html.escape(now)}</id>
<updated>{html.escape(now)}</updated>
<summary>{html.escape(desc)}</summary>
</entry>
</feed>
"""
    atom_path.write_text(atom, encoding="utf-8")

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (now, "tat1_generate", f"feeds generated: {count} artifacts")
    )
    con.commit()
    con.close()

    # index feeds as artifacts? (optional) keep them outside vault: we still index them for integrity
    index_paths(cfg, [rss_path, atom_path], source="iarc")
    return rss_path, atom_path


# ----------------------------
# Manifest / Bundle / Freeze
# ----------------------------

def build_manifest(cfg: KernelConfig) -> Path:
    now = utc_now()
    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute("SELECT COUNT(*) FROM artifacts")
    artifacts = cur.fetchone()[0]
    cur.execute("SELECT COUNT(*) FROM events")
    events = cur.fetchone()[0]
    con.close()

    hashes: Dict[str, str] = {}
    for p in [cfg.root / "feeds" / "tat1.rss", cfg.root / "feeds" / "tat1.atom", cfg.root / "index" / "FREEZE.marker"]:
        if p.exists():
            hashes[str(p.relative_to(cfg.root)).replace("\\", "/")] = sha256_file(p)

    manifest = {
        "generated_utc": now,
        "root": "earc/",
        "kernel": {"mode": cfg.mode, "state": cfg.state, "comm": cfg.comm_default},
        "counts": {"artifacts": artifacts, "events": events},
        "hashes": hashes,
        "policy": {"read": "read_only", "write": cfg.policy_write, "comm": cfg.comm_default},
        "build": {"deterministic_intent": True}
    }

    out = cfg.root / "index" / "manifest.json"
    out.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    index_paths(cfg, [out], source="iarc")
    return out

def build_bundle(cfg: KernelConfig) -> Path:
    exports_dir = cfg.root / "exports"
    exports_dir.mkdir(parents=True, exist_ok=True)
    tag = _dt.datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")
    bundle = exports_dir / f"earc_bundle_{tag}.zip"

    include = [
        cfg.root / "diamond",
        cfg.root / "vault",
        cfg.root / "index" / "earc.sqlite",
        cfg.root / "index" / "manifest.json",
        cfg.root / "index" / "FREEZE.marker",
        cfg.root / "feeds" / "tat1.rss",
        cfg.root / "feeds" / "tat1.atom",
    ]

    with zipfile.ZipFile(bundle, "w", compression=zipfile.ZIP_DEFLATED) as z:
        for item in include:
            if item.is_dir():
                for f in item.rglob("*"):
                    if f.is_file():
                        z.write(f, f.relative_to(cfg.root))
            elif item.is_file():
                z.write(item, item.relative_to(cfg.root))

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (utc_now(), "bundle_build", f"bundle={bundle.name}")
    )
    con.commit()
    con.close()

    return bundle

def set_freeze_marker(cfg: KernelConfig) -> Path:
    p = cfg.root / "index" / "FREEZE.marker"
    content = "\n".join([
        "state: FROZEN",
        "scope: earc_bundle",
        "policy: read_only_core / append_only_events",
        f"comm: {cfg.comm_default}",
        f"generated_utc: {utc_now()}",
        ""
    ])
    p.write_text(content, encoding="utf-8")

    con = db_connect(cfg)
    cur = con.cursor()
    cur.execute(
        "INSERT INTO events (timestamp_utc,event,details) VALUES (?,?,?)",
        (utc_now(), "freeze", "build closed: FREEZE.marker set")
    )
    con.commit()
    con.close()

    index_paths(cfg, [p], source="iarc")
    return p


# ----------------------------
# Orchestration
# ----------------------------

def run_full_pipeline(cfg: KernelConfig) -> None:
    """
    Minimal, calm, deterministic intent:
    init -> scan/index -> mark -> pack -> superpack -> tat1 -> manifest -> freeze -> manifest -> bundle
    """
    db_init(cfg)
    scan_and_index(cfg)
    spirit_mark_patterns(cfg)
    build_pack(cfg)
    build_superpack(cfg)
    tat1_generate(cfg)
    build_manifest(cfg)
    set_freeze_marker(cfg)
    build_manifest(cfg)
    build_bundle(cfg)

def status(cfg: KernelConfig) -> str:
    p_db = db_path(cfg)
    ok_db = p_db.exists()
    out = {
        "kernel": {"mode": cfg.mode, "state": cfg.state, "comm": cfg.comm_default},
        "paths": {
            "root": str(cfg.root),
            "db": str(p_db),
            "feeds": str(cfg.root / "feeds"),
            "vault": str(cfg.root / "vault")
        },
        "ready": bool(ok_db),
        "counts": {}
    }
    if ok_db:
        con = db_connect(cfg)
        cur = con.cursor()
        cur.execute("SELECT COUNT(*) FROM artifacts")
        out["counts"]["artifacts"] = cur.fetchone()[0]
        cur.execute("SELECT COUNT(*) FROM events")
        out["counts"]["events"] = cur.fetchone()[0]
        con.close()
    return json.dumps(out, indent=2)


# ----------------------------
# CLI
# ----------------------------

def main():
    cfg = KernelConfig()

    ap = argparse.ArgumentParser(prog="diamond_shell", add_help=True)
    sub = ap.add_subparsers(dest="cmd", required=True)

    sub.add_parser("init", help="init dirs + sqlite schema")
    sub.add_parser("scan", help="scan vault+diamond and index into sqlite (read-only)")
    sub.add_parser("mark", help="Spirit mark-only frame (green/yellow/red)")
    sub.add_parser("pack", help="build pack summary from frames")
    sub.add_parser("superpack", help="build superpack overview from packs")
    sub.add_parser("tat1", help="generate local RSS/Atom artifacts (COMM OFF)")
    sub.add_parser("manifest", help="write index/manifest.json")
    sub.add_parser("freeze", help="set FREEZE.marker + event log (append-only)")
    sub.add_parser("bundle", help="zip bundle to exports/")
    sub.add_parser("run", help="run full minimal pipeline end-to-end")
    sub.add_parser("status", help="print status json")

    args = ap.parse_args()

    if args.cmd == "init":
        db_init(cfg)
    elif args.cmd == "scan":
        scan_and_index(cfg)
    elif args.cmd == "mark":
        spirit_mark_patterns(cfg)
    elif args.cmd == "pack":
        build_pack(cfg)
    elif args.cmd == "superpack":
        build_superpack(cfg)
    elif args.cmd == "tat1":
        tat1_generate(cfg)
    elif args.cmd == "manifest":
        build_manifest(cfg)
    elif args.cmd == "freeze":
        set_freeze_marker(cfg)
    elif args.cmd == "bundle":
        build_bundle(cfg)
    elif args.cmd == "run":
        run_full_pipeline(cfg)
    elif args.cmd == "status":
        print(status(cfg))

if __name__ == "__main__":
    main()