#!/usr/bin/env python3
import sqlite3, datetime, json
from pathlib import Path

ROOT = Path("earc")
DB = ROOT / "index" / "earc.sqlite"
FRAMES = ROOT / "vault" / "frames"
FRAMES.mkdir(parents=True, exist_ok=True)

def utc():
    return datetime.datetime.utcnow().replace(microsecond=0).isoformat() + "Z"

con = sqlite3.connect(DB)
cur = con.cursor()

# simple signals (baseline)
cur.execute("SELECT COUNT(*), MIN(created_utc), MAX(created_utc) FROM artifacts")
count, first, last = cur.fetchone()

# heuristic markers (no action)
level = "green"
if count > 1000:
    level = "yellow"
if count > 10000:
    level = "red"

frame = {
  "type": "pattern-marker",
  "level": level,
  "artifacts": count,
  "window": {"from": first, "to": last},
  "generated_utc": utc(),
  "policy": "mark_only"
}

fname = f"pattern_{frame['generated_utc'].replace(':','')}.json"
(FRAMES / fname).write_text(json.dumps(frame, indent=2), encoding="utf-8")

cur.execute("""
  INSERT INTO events (timestamp_utc,event,details)
  VALUES (?,?,?)
""", (frame["generated_utc"], "pattern_mark", f"level={level} count={count}"))

con.commit()
con.close()