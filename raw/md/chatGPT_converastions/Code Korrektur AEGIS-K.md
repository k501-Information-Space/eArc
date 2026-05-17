# Code Korrektur AEGIS-K

## system · 1970-01-01T00:00:00 UTC



---

## user · 2026-01-09T22:11:37.784741 UTC

#!/usr/bin/env python3
"""
bundle_kernel.py — eArc Bundle Kernel (Seed + Diamond Shell + AEGIS-K) v0.1

Single-file, copy/paste-ready.
Local-first. Append-only logs. Canon read-only via AEGIS-K marker+lock.

USAGE (run from anywhere):
  python3 bundle_kernel.py init
  python3 bundle_kernel.py boot
  python3 bundle_kernel.py where
  python3 bundle_kernel.py validate
  python3 bundle_kernel.py log "hello_event"
  python3 bundle_kernel.py scan
  python3 bundle_kernel.py canon_quote
  python3 bundle_kernel.py status

NOTES:
- Root directory is derived from this file location:
    ROOT = bundle_kernel.py parent directory
- Creates:
    canon/ (AEGIS-K.marker + AEGIS-K.lock + feed_canon_quote.md)
    index/earc.sqlite  (events table)
    metrics/events.jsonl (append-only)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import os
import sqlite3
import sys


# =========================
# Time / Helpers
# =========================

def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> "NoReturn":
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    # root = directory where this bundle file resides
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


# =========================
# Seed (Bootstrap)
# =========================

CANON_QUOTE_DEFAULT = """Ewiges Zitat – Kanon der Erkenntnis

„Wir bauen nicht, um zu besitzen.
Wir ordnen, um zu verstehen.

Der Kern bleibt unangetastet.
Der Diamant bleibt geformt.

Alles, was wir erfahren haben,
legen wir nicht in den Kern,
sondern um ihn herum.

Als Archiv der Erkenntnis.

Nicht um zu steuern.
Nicht um zu lehren.

Sondern um zu zeigen,
dass es möglich ist,
rechtzeitig aufzuhören.“
"""


def ensure_dirs() -> None:
    p = P()
    p.root.mkdir(parents=True, exist_ok=True)
    p.canon.mkdir(parents=True, exist_ok=True)
    p.index.mkdir(parents=True, exist_ok=True)
    p.metrics.mkdir(parents=True, exist_ok=True)


def ensure_aegis_files() -> None:
    p = P()
    # Create marker/lock if missing (bootstrap action)
    if not p.marker.exists():
        p.marker.write_text("AEGIS-K: marker\n", encoding="utf-8")
    if not p.lock.exists():
        p.lock.write_text("AEGIS-K: lock\n", encoding="utf-8")

    # Canon feed quote (optional; write if missing)
    if not p.quote.exists():
        p.quote.write_text(CANON_QUOTE_DEFAULT, encoding="utf-8")


def ensure_sqlite() -> None:
    p = P()
    p.db.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS events(ts TEXT, msg TEXT)")
    con.commit()
    con.close()


def append_sqlite(msg: str) -> None:
    p = P()
    ensure_sqlite()
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("INSERT INTO events VALUES(?,?)", (utc_z(), msg))
    con.commit()
    con.close()


def append_jsonl(msg: str, extra: dict | None = None) -> None:
    p = P()
    p.metrics.mkdir(parents=True, exist_ok=True)
    payload = {"ts": utc_z(), "msg": msg}
    if extra:
        payload.update(extra)
    with p.events_jsonl.open("a", encoding="utf-8") as f:
        f.write(json.dumps(payload, ensure_ascii=False) + "\n")


def seed_init() -> int:
    ensure_dirs()
    ensure_aegis_files()
    ensure_sqlite()
    append_sqlite("seed_ok")
    append_jsonl("seed_ok", {"root": str(P().root)})
    print("SEED:OK")
    print("ROOT:", P().root)
    print("DB:", P().db)
    print("EVENTS:", P().events_jsonl)
    print("CANON:", P().canon)
    return 0


# =========================
# Diamond Shell (Triggers)
# =========================

def cmd_boot() -> int:
    print("BOOT:OK")
    print("ROOT:", P().root)
    return 0


def cmd_where() -> int:
    p = P()
    print("WHERE")
    print("ROOT:", p.root)
    print("CANON:", p.canon)
    print("INDEX:", p.index)
    print("METRICS:", p.metrics)
    print("DB:", p.db)
    print("EVENTS_JSONL:", p.events_jsonl)
    print("AEGIS_MARKER:", p.marker)
    print("AEGIS_LOCK:", p.lock)
    print("CANON_QUOTE:", p.quote)
    return 0


def cmd_validate() -> int:
    # hard gate: AEGIS-K must exist
    assert_aegis_k()

    p = P()
    if not p.canon.exists():
        print("VALIDATE:FAIL canon missing")
        return 1
    print("VALIDATE:OK")
    return 0


def cmd_log(args: list[str]) -> int:
    if not args:
        print("LOG:FAIL missing msg")
        return 1
    msg = " ".join(args).strip()
    append_sqlite(msg)
    append_jsonl(msg)
    print("LOG:OK", msg)
    return 0


def cmd_scan() -> int:
    p = P()
    print("SCAN")
    for key in ("canon", "index", "metrics"):
        d = getattr(p, key)
        if d.exists() and d.is_dir():
            print(f"- {key}/")
            for x in sorted(d.iterdir()):
                print("  ", x.name)
    return 0


def cmd_canon_quote() -> int:
    p = P()
    if not p.quote.exists():
        print("CANON_QUOTE: missing; run init")
        return 1
    print(p.quote.read_text(encoding="utf-8"))
    return 0


def cmd_status() -> int:
    p = P()
    ok_marker = p.marker.exists()
    ok_lock = p.lock.exists()
    ok_db = p.db.exists()
    ok_jsonl = p.events_jsonl.exists()

    print("STATUS")
    print("AEGIS-K.marker:", "OK" if ok_marker else "MISSING")
    print("AEGIS-K.lock:", "OK" if ok_lock else "MISSING")
    print("DB:", "OK" if ok_db else "MISSING")
    print("events.jsonl:", "OK" if ok_jsonl else "MISSING")
    print("ROOT:", p.root)
    return 0


def usage() -> int:
    print("bundle_kernel.py — eArc Bundle Kernel v0.1")
    print("Commands:")
    print("  init                 bootstrap folders + AEGIS-K + sqlite + jsonl log")
    print("  boot                 print ROOT")
    print("  where                print key paths")
    print("  validate             enforce AEGIS-K presence")
    print("  log <msg>            append event (sqlite + jsonl)")
    print("  scan                 list canon/index/metrics contents")
    print("  canon_quote          print canon feed quote")
    print("  status               quick health check")
    return 0


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        return usage()

    cmd = argv[1].lower()
    args = argv[2:]

    if cmd == "init":
        return seed_init()
    if cmd == "boot":
        return cmd_boot()
    if cmd == "where":
        return cmd_where()
    if cmd == "validate":
        return cmd_validate()
    if cmd == "log":
        return cmd_log(args)
    if cmd == "scan":
        return cmd_scan()
    if cmd == "canon_quote":
        return cmd_canon_quote()
    if cmd == "status":
        return cmd_status()

    print("Unknown command:", cmd)
    return 2


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))

---

## assistant · 2026-01-09T22:11:39.253884 UTC

Ich lese das als: **ein minimaler, single-file “Seed + Diamond Shell + AEGIS-K” Bootstrap**, der lokal-first ist, **append-only** loggt, und den **Kanon als read-only** behandeln will. Dafür ist es schon sehr nah dran – aber es gibt ein paar konkrete Stellen, die (a) aktuell **nicht ganz korrekt** sind und (b) eure AEGIS-K / “Canon never writes again” Idee noch **härter** machen.

## Sofort-Fixes (Korrektheit)

1) **`NoReturn` ist nicht importiert**  
`die()` annotiert `"NoReturn"`, aber `NoReturn` kommt nirgends her. Entweder:
- `from typing import NoReturn` und dann `-> NoReturn`, oder
- Annotation entfernen.

2) **Unbenutzte Imports**
`os` wird nicht genutzt (kann raus).

3) **Canon-Write-Guard ist definiert, aber nirgendwo aktiv**
`deny_write()` existiert, wird aber nicht aufgerufen. Momentan kann euer Code später *theoretisch* immer noch in `canon/` schreiben, wenn jemand aus Versehen `write_text` auf einen Canon-Pfad setzt.  
Wenn AEGIS-K “Canon is forever read-only” sein soll, sollte jede Canon-Schreibstelle **zentral** durch einen Guard gehen.

## AEGIS-K: Was aktuell “weich” ist (und wie du es hart bekommst)

### Problem A: `init` kann Canon “reparieren”
`ensure_aegis_files()` erstellt Marker/Lock, wenn sie fehlen. Das ist praktisch fürs Bootstrap – aber es bedeutet auch: **wenn jemand Canon beschädigt (Marker gelöscht), kann `init` ihn einfach neu erzeugen**.

**Harter Modus (empfohlen):**
- Wenn `canon/` schon existiert, aber Marker/Lock fehlen → **REFUSE** (kein self-heal).
- Nur beim allerersten Init (canon existiert nicht) darf erzeugt werden.

### Problem B: “Read-only” ist nur eine Konvention
AEGIS-K wird logisch geprüft (marker+lock), aber das OS darf trotzdem schreiben.

**Optionale Härtung (sehr wirksam, immer noch lokal-first):**
- Nach erfolgreichem `init` → setze Dateirechte von `canon/` und dessen Dateien auf read-only.
  - Linux/macOS: chmod 444 für Dateien, 555 für Ordner.
  - (Windows ist anders; dort kann man es zumindest “best effort” machen.)

### Problem C: Keine Integritätsprüfung des Kanons
Wenn jemand `feed_canon_quote.md` ändert, merkt dein Kernel nichts.

**Minimaler Integritätsanker:**
- Beim Init: schreibe zusätzlich `canon/AEGIS-K.sha256` mit Hashes (oder nur Hash des Quotes).
- Bei `validate`: prüfe Hash stimmt.

## Append-only Logs: kleine Verbesserungen

- **SQLite-Table ohne PK** ist ok für “append-only events”, aber ein `rowid` ist implizit. Wenn du später sauberer diffen willst: `id INTEGER PRIMARY KEY AUTOINCREMENT`.
- **WAL-Modus** macht SQLite robuster, besonders bei parallelen Writes:
  - `PRAGMA journal_mode=WAL;`
- **JSONL ist append-only**, aber paralleles Schreiben kann Zeilen mischen. Optional: `fcntl` lock (POSIX) oder “best effort” (für v0.1 ok).

## Mini-Patch (konkret, copy/paste)

Unten ein gezielter Patch, der nur das Nötigste macht:
- `NoReturn` fix
- `os` raus
- “Canon self-heal” nur beim ersten Init
- zentraler `safe_write_text` mit Canon-Guard
- optionaler chmod-freeze (best effort)

```python
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import sqlite3
import sys
from typing import NoReturn


def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> NoReturn:
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


def safe_write_text(path: Path, content: str) -> None:
    # single chokepoint for writes
    deny_write(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def freeze_canon_best_effort() -> None:
    """
    Best-effort OS-level hardening. Safe to fail silently.
    - files: 444
    - dirs : 555
    """
    p = P()
    try:
        if p.canon.exists():
            p.canon.chmod(0o555)
            for x in p.canon.iterdir():
                if x.is_file():
                    x.chmod(0o444)
    except Exception:
        # do not break kernel for permissions issues
        pass


# =========================
# Seed (Bootstrap)
# =========================

CANON_QUOTE_DEFAULT = """Ewiges Zitat – Kanon der Erkenntnis

„Wir bauen nicht, um zu besitzen.
Wir ordnen, um zu verstehen.

Der Kern bleibt unangetastet.
Der Diamant bleibt geformt.

Alles, was wir erfahren haben,
legen wir nicht in den Kern,
sondern um ihn herum.

Als Archiv der Erkenntnis.

Nicht um zu steuern.
Nicht um zu lehren.

Sondern um zu zeigen,
dass es möglich ist,
rechtzeitig aufzuhören.“
"""


def ensure_dirs() -> None:
    p = P()
    p.root.mkdir(parents=True, exist_ok=True)
    p.canon.mkdir(parents=True, exist_ok=True)
    p.index.mkdir(parents=True, exist_ok=True)
    p.metrics.mkdir(parents=True, exist_ok=True)


def ensure_aegis_files() -> None:
    p = P()

    # Hard rule: if canon exists but marker/lock missing -> refuse (no self-heal)
    canon_exists = p.canon.exists()
    marker_exists = p.marker.exists()
    lock_exists = p.lock.exists()

    if canon_exists and (not marker_exists or not lock_exists):
        die(1, "AEGIS-K: BROKEN CANON — REFUSE (marker/lock missing)")

    # First init only: create marker/lock/quote if missing
    if not marker_exists:
        p.marker.write_text("AEGIS-K: marker\n", encoding="utf-8")
    if not lock_exists:
        p.lock.write_text("AEGIS-K: lock\n", encoding="utf-8")
    if not p.quote.exists():
        p.quote.write_text(CANON_QUOTE_DEFAULT, encoding="utf-8")

    # optional hardening
    freeze_canon_best_effort()


def ensure_sqlite() -> None:
    p = P()
    p.db.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("PRAGMA journal_mode=WAL;")
    cur.execute("CREATE TABLE IF NOT EXISTS events(id INTEGER PRIMARY KEY AUTOINCREMENT, ts TEXT, msg TEXT)")
    con.commit()
    con.close()


def append_sqlite(msg: str) -> None:
    p = P()
    ensure_sqlite()
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("INSERT INTO events(ts, msg) VALUES(?,?)", (utc_z(), msg))
    con.commit()
    con.close()


def append_jsonl(msg: str, extra: dict | None = None) -> None:
    p = P()
    p.metrics.mkdir(parents=True, exist_ok=True)
    payload = {"ts": utc_z(), "msg": msg}
    if extra:
        payload.update(extra)
    with p.events_jsonl.open("a", encoding="utf-8") as f:
        f.write(json.dumps(payload, ensure_ascii=False) + "\n")
```

(Dein Rest kann bleiben wie er ist.)

## Kleine Design-Entscheidung, die ich sauber finde
Du hast `deny_write()` – das ist genau der richtige Instinkt. Der nächste Schritt ist: **jede Schreiboperation im Kernel muss durch genau eine Funktion gehen**. Das macht “Canon never writes” zu einer

---

## system · 2026-01-09T22:11:39.917367 UTC



---

## assistant · 2026-01-09T22:11:39.998976 UTC



---

## user · 2026-01-09T22:13:11.122699 UTC

#!/usr/bin/env python3
"""
bundle_kernel.py — eArc Bundle Kernel (Seed + Diamond Shell + AEGIS-K) v0.1

Single-file, copy/paste-ready.
Local-first. Append-only logs. Canon read-only via AEGIS-K marker+lock.

USAGE (run from anywhere):
  python3 bundle_kernel.py init
  python3 bundle_kernel.py boot
  python3 bundle_kernel.py where
  python3 bundle_kernel.py validate
  python3 bundle_kernel.py log "hello_event"
  python3 bundle_kernel.py scan
  python3 bundle_kernel.py canon_quote
  python3 bundle_kernel.py status

NOTES:
- Root directory is derived from this file location:
    ROOT = bundle_kernel.py parent directory
- Creates:
    canon/ (AEGIS-K.marker + AEGIS-K.lock + feed_canon_quote.md)
    index/earc.sqlite  (events table)
    metrics/events.jsonl (append-only)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import os
import sqlite3
import sys


# =========================
# Time / Helpers
# =========================

def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> "NoReturn":
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    # root = directory where this bundle file resides
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


# =========================
# Seed (Bootstrap)
# =========================

CANON_QUOTE_DEFAULT = """Ewiges Zitat – Kanon der Erkenntnis

„Wir bauen nicht, um zu besitzen.
Wir ordnen, um zu verstehen.

Der Kern bleibt unangetastet.
Der Diamant bleibt geformt.

Alles, was wir erfahren haben,
legen wir nicht in den Kern,
sondern um ihn herum.

Als Archiv der Erkenntnis.

Nicht um zu steuern.
Nicht um zu lehren.

Sondern um zu zeigen,
dass es möglich ist,
rechtzeitig aufzuhören.“
"""


def ensure_dirs() -> None:
    p = P()
    p.root.mkdir(parents=True, exist_ok=True)
    p.canon.mkdir(parents=True, exist_ok=True)
    p.index.mkdir(parents=True, exist_ok=True)
    p.metrics.mkdir(parents=True, exist_ok=True)


def ensure_aegis_files() -> None:
    p = P()
    # Create marker/lock if missing (bootstrap action)
    if not p.marker.exists():
        p.marker.write_text("AEGIS-K: marker\n", encoding="utf-8")
    if not p.lock.exists():
        p.lock.write_text("AEGIS-K: lock\n", encoding="utf-8")

    # Canon feed quote (optional; write if missing)
    if not p.quote.exists():
        p.quote.write_text(CANON_QUOTE_DEFAULT, encoding="utf-8")


def ensure_sqlite() -> None:
    p = P()
    p.db.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS events(ts TEXT, msg TEXT)")
    con.commit()
    con.close()


def append_sqlite(msg: str) -> None:
    p = P()
    ensure_sqlite()
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("INSERT INTO events VALUES(?,?)", (utc_z(), msg))
    con.commit()
    con.close()


def append_jsonl(msg: str, extra: dict | None = None) -> None:
    p = P()
    p.metrics.mkdir(parents=True, exist_ok=True)
    payload = {"ts": utc_z(), "msg": msg}
    if extra:
        payload.update(extra)
    with p.events_jsonl.open("a", encoding="utf-8") as f:
        f.write(json.dumps(payload, ensure_ascii=False) + "\n")


def seed_init() -> int:
    ensure_dirs()
    ensure_aegis_files()
    ensure_sqlite()
    append_sqlite("seed_ok")
    append_jsonl("seed_ok", {"root": str(P().root)})
    print("SEED:OK")
    print("ROOT:", P().root)
    print("DB:", P().db)
    print("EVENTS:", P().events_jsonl)
    print("CANON:", P().canon)
    return 0


# =========================
# Diamond Shell (Triggers)
# =========================

def cmd_boot() -> int:
    print("BOOT:OK")
    print("ROOT:", P().root)
    return 0


def cmd_where() -> int:
    p = P()
    print("WHERE")
    print("ROOT:", p.root)
    print("CANON:", p.canon)
    print("INDEX:", p.index)
    print("METRICS:", p.metrics)
    print("DB:", p.db)
    print("EVENTS_JSONL:", p.events_jsonl)
    print("AEGIS_MARKER:", p.marker)
    print("AEGIS_LOCK:", p.lock)
    print("CANON_QUOTE:", p.quote)
    return 0


def cmd_validate() -> int:
    # hard gate: AEGIS-K must exist
    assert_aegis_k()

    p = P()
    if not p.canon.exists():
        print("VALIDATE:FAIL canon missing")
        return 1
    print("VALIDATE:OK")
    return 0


def cmd_log(args: list[str]) -> int:
    if not args:
        print("LOG:FAIL missing msg")
        return 1
    msg = " ".join(args).strip()
    append_sqlite(msg)
    append_jsonl(msg)
    print("LOG:OK", msg)
    return 0


def cmd_scan() -> int:
    p = P()
    print("SCAN")
    for key in ("canon", "index", "metrics"):
        d = getattr(p, key)
        if d.exists() and d.is_dir():
            print(f"- {key}/")
            for x in sorted(d.iterdir()):
                print("  ", x.name)
    return 0


def cmd_canon_quote() -> int:
    p = P()
    if not p.quote.exists():
        print("CANON_QUOTE: missing; run init")
        return 1
    print(p.quote.read_text(encoding="utf-8"))
    return 0


def cmd_status() -> int:
    p = P()
    ok_marker = p.marker.exists()
    ok_lock = p.lock.exists()
    ok_db = p.db.exists()
    ok_jsonl = p.events_jsonl.exists()

    print("STATUS")
    print("AEGIS-K.marker:", "OK" if ok_marker else "MISSING")
    print("AEGIS-K.lock:", "OK" if ok_lock else "MISSING")
    print("DB:", "OK" if ok_db else "MISSING")
    print("events.jsonl:", "OK" if ok_jsonl else "MISSING")
    print("ROOT:", p.root)
    return 0


def usage() -> int:
    print("bundle_kernel.py — eArc Bundle Kernel v0.1")
    print("Commands:")
    print("  init                 bootstrap folders + AEGIS-K + sqlite + jsonl log")
    print("  boot                 print ROOT")
    print("  where                print key paths")
    print("  validate             enforce AEGIS-K presence")
    print("  log <msg>            append event (sqlite + jsonl)")
    print("  scan                 list canon/index/metrics contents")
    print("  canon_quote          print canon feed quote")
    print("  status               quick health check")
    return 0


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        return usage()

    cmd = argv[1].lower()
    args = argv[2:]

    if cmd == "init":
        return seed_init()
    if cmd == "boot":
        return cmd_boot()
    if cmd == "where":
        return cmd_where()
    if cmd == "validate":
        return cmd_validate()
    if cmd == "log":
        return cmd_log(args)
    if cmd == "scan":
        return cmd_scan()
    if cmd == "canon_quote":
        return cmd_canon_quote()
    if cmd == "status":
        return cmd_status()

    print("Unknown command:", cmd)
    return 2


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))

---

## assistant · 2026-01-09T22:13:12.606866 UTC

Alles klar — ich behandle das als **Review + “härten ohne aufblasen”**. Du hast hier ein sauberes v0.1-Seed, aber aktuell sind drei Dinge “gegen den eigenen Text”:

1) **`die()` ist kaputt** (NoReturn fehlt)  
2) **AEGIS-K macht Canon nicht wirklich read-only** (nur Konvention)  
3) **`init` kann Canon jederzeit neu schreiben** (self-heal = weicher Kanon)

Unten bekommst du eine **komplette, drop-in Version** (immer noch single-file, copy/paste), die:

- `NoReturn` sauber importiert
- `os` entfernt
- einen **einzigen Schreib-Chokepoint** (`write_text_guarded`) nutzt
- Canon nur beim **First Init** schreibt (danach: wenn Marker/Lock fehlen → **REFUSE**)
- optional (best effort) Canon-Dateirechte auf read-only setzt
- SQLite etwas robuster macht (WAL + id PK), ohne Konzeptwechsel

---

```python
#!/usr/bin/env python3
"""
bundle_kernel.py — eArc Bundle Kernel (Seed + Diamond Shell + AEGIS-K) v0.1.1

Single-file, copy/paste-ready.
Local-first. Append-only logs. Canon read-only via AEGIS-K marker+lock.

USAGE (run from anywhere):
  python3 bundle_kernel.py init
  python3 bundle_kernel.py boot
  python3 bundle_kernel.py where
  python3 bundle_kernel.py validate
  python3 bundle_kernel.py log "hello_event"
  python3 bundle_kernel.py scan
  python3 bundle_kernel.py canon_quote
  python3 bundle_kernel.py status

NOTES:
- Root directory is derived from this file location:
    ROOT = bundle_kernel.py parent directory
- Creates:
    canon/ (AEGIS-K.marker + AEGIS-K.lock + feed_canon_quote.md)
    index/earc.sqlite  (events table)
    metrics/events.jsonl (append-only)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import sqlite3
import sys
from typing import NoReturn


# =========================
# Time / Helpers
# =========================

def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> NoReturn:
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


def write_text_guarded(path: Path, content: str) -> None:
    """
    Single chokepoint for writes.
    All writes must go through here.
    """
    deny_write(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def freeze

---

## system · 2026-01-09T22:13:13.224386 UTC



---

## user · 2026-01-09T22:13:44.268106 UTC

#!/usr/bin/env python3
"""
bundle_kernel.py — eArc Bundle Kernel (Seed + Diamond Shell + AEGIS-K) v0.1

Single-file, copy/paste-ready.
Local-first. Append-only logs. Canon read-only via AEGIS-K marker+lock.

USAGE (run from anywhere):
  python3 bundle_kernel.py init
  python3 bundle_kernel.py boot
  python3 bundle_kernel.py where
  python3 bundle_kernel.py validate
  python3 bundle_kernel.py log "hello_event"
  python3 bundle_kernel.py scan
  python3 bundle_kernel.py canon_quote
  python3 bundle_kernel.py status

NOTES:
- Root directory is derived from this file location:
    ROOT = bundle_kernel.py parent directory
- Creates:
    canon/ (AEGIS-K.marker + AEGIS-K.lock + feed_canon_quote.md)
    index/earc.sqlite  (events table)
    metrics/events.jsonl (append-only)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import os
import sqlite3
import sys


# =========================
# Time / Helpers
# =========================

def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> "NoReturn":
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    # root = directory where this bundle file resides
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


# =========================
# Seed (Bootstrap)
# =========================

CANON_QUOTE_DEFAULT = """Ewiges Zitat – Kanon der Erkenntnis

„Wir bauen nicht, um zu besitzen.
Wir ordnen, um zu verstehen.

Der Kern bleibt unangetastet.
Der Diamant bleibt geformt.

Alles, was wir erfahren haben,
legen wir nicht in den Kern,
sondern um ihn herum.

Als Archiv der Erkenntnis.

Nicht um zu steuern.
Nicht um zu lehren.

Sondern um zu zeigen,
dass es möglich ist,
rechtzeitig aufzuhören.“
"""


def ensure_dirs() -> None:
    p = P()
    p.root.mkdir(parents=True, exist_ok=True)
    p.canon.mkdir(parents=True, exist_ok=True)
    p.index.mkdir(parents=True, exist_ok=True)
    p.metrics.mkdir(parents=True, exist_ok=True)


def ensure_aegis_files() -> None:
    p = P()
    # Create marker/lock if missing (bootstrap action)
    if not p.marker.exists():
        p.marker.write_text("AEGIS-K: marker\n", encoding="utf-8")
    if not p.lock.exists():
        p.lock.write_text("AEGIS-K: lock\n", encoding="utf-8")

    # Canon feed quote (optional; write if missing)
    if not p.quote.exists():
        p.quote.write_text(CANON_QUOTE_DEFAULT, encoding="utf-8")


def ensure_sqlite() -> None:
    p = P()
    p.db.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS events(ts TEXT, msg TEXT)")
    con.commit()
    con.close()


def append_sqlite(msg: str) -> None:
    p = P()
    ensure_sqlite()
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("INSERT INTO events VALUES(?,?)", (utc_z(), msg))
    con.commit()
    con.close()


def append_jsonl(msg: str, extra: dict | None = None) -> None:
    p = P()
    p.metrics.mkdir(parents=True, exist_ok=True)
    payload = {"ts": utc_z(), "msg": msg}
    if extra:
        payload.update(extra)
    with p.events_jsonl.open("a", encoding="utf-8") as f:
        f.write(json.dumps(payload, ensure_ascii=False) + "\n")


def seed_init() -> int:
    ensure_dirs()
    ensure_aegis_files()
    ensure_sqlite()
    append_sqlite("seed_ok")
    append_jsonl("seed_ok", {"root": str(P().root)})
    print("SEED:OK")
    print("ROOT:", P().root)
    print("DB:", P().db)
    print("EVENTS:", P().events_jsonl)
    print("CANON:", P().canon)
    return 0


# =========================
# Diamond Shell (Triggers)
# =========================

def cmd_boot() -> int:
    print("BOOT:OK")
    print("ROOT:", P().root)
    return 0


def cmd_where() -> int:
    p = P()
    print("WHERE")
    print("ROOT:", p.root)
    print("CANON:", p.canon)
    print("INDEX:", p.index)
    print("METRICS:", p.metrics)
    print("DB:", p.db)
    print("EVENTS_JSONL:", p.events_jsonl)
    print("AEGIS_MARKER:", p.marker)
    print("AEGIS_LOCK:", p.lock)
    print("CANON_QUOTE:", p.quote)
    return 0


def cmd_validate() -> int:
    # hard gate: AEGIS-K must exist
    assert_aegis_k()

    p = P()
    if not p.canon.exists():
        print("VALIDATE:FAIL canon missing")
        return 1
    print("VALIDATE:OK")
    return 0


def cmd_log(args: list[str]) -> int:
    if not args:
        print("LOG:FAIL missing msg")
        return 1
    msg = " ".join(args).strip()
    append_sqlite(msg)
    append_jsonl(msg)
    print("LOG:OK", msg)
    return 0


def cmd_scan() -> int:
    p = P()
    print("SCAN")
    for key in ("canon", "index", "metrics"):
        d = getattr(p, key)
        if d.exists() and d.is_dir():
            print(f"- {key}/")
            for x in sorted(d.iterdir()):
                print("  ", x.name)
    return 0


def cmd_canon_quote() -> int:
    p = P()
    if not p.quote.exists():
        print("CANON_QUOTE: missing; run init")
        return 1
    print(p.quote.read_text(encoding="utf-8"))
    return 0


def cmd_status() -> int:
    p = P()
    ok_marker = p.marker.exists()
    ok_lock = p.lock.exists()
    ok_db = p.db.exists()
    ok_jsonl = p.events_jsonl.exists()

    print("STATUS")
    print("AEGIS-K.marker:", "OK" if ok_marker else "MISSING")
    print("AEGIS-K.lock:", "OK" if ok_lock else "MISSING")
    print("DB:", "OK" if ok_db else "MISSING")
    print("events.jsonl:", "OK" if ok_jsonl else "MISSING")
    print("ROOT:", p.root)
    return 0


def usage() -> int:
    print("bundle_kernel.py — eArc Bundle Kernel v0.1")
    print("Commands:")
    print("  init                 bootstrap folders + AEGIS-K + sqlite + jsonl log")
    print("  boot                 print ROOT")
    print("  where                print key paths")
    print("  validate             enforce AEGIS-K presence")
    print("  log <msg>            append event (sqlite + jsonl)")
    print("  scan                 list canon/index/metrics contents")
    print("  canon_quote          print canon feed quote")
    print("  status               quick health check")
    return 0


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        return usage()

    cmd = argv[1].lower()
    args = argv[2:]

    if cmd == "init":
        return seed_init()
    if cmd == "boot":
        return cmd_boot()
    if cmd == "where":
        return cmd_where()
    if cmd == "validate":
        return cmd_validate()
    if cmd == "log":
        return cmd_log(args)
    if cmd == "scan":
        return cmd_scan()
    if cmd == "canon_quote":
        return cmd_canon_quote()
    if cmd == "status":
        return cmd_status()

    print("Unknown command:", cmd)
    return 2


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))

---

## assistant · 2026-01-09T22:13:45.721136 UTC

Du hast denselben Stand nochmal gepostet (v0.1). Ich mache dir daraus jetzt **eine saubere v0.1.1 “hardened” Full-Replacement-Datei**, ohne Zusatz-Features, nur die Härtung + Fixes:

- ✅ `NoReturn` korrekt (Import + Annotation)
- ✅ `os` entfernt (war unbenutzt)
- ✅ **ein** Write-Chokepoint (`write_text_guarded`) – Canon writes laufen nur in `init` und nur beim First Init
- ✅ **kein Canon self-heal**: wenn `canon/` existiert, aber marker/lock fehlen → **REFUSE**
- ✅ optionales “best effort” read-only chmod für Canon (bricht nicht, wenn’s nicht geht)
- ✅ SQLite minimal robuster (WAL + id PK), bleibt append-only

Hier ist die komplette Datei:

```python
#!/usr/bin/env python3
"""
bundle_kernel.py — eArc Bundle Kernel (Seed + Diamond Shell + AEGIS-K) v0.1.1

Single-file, copy/paste-ready.
Local-first. Append-only logs. Canon read-only via AEGIS-K marker+lock.

USAGE (run from anywhere):
  python3 bundle_kernel.py init
  python3 bundle_kernel.py boot
  python3 bundle_kernel.py where
  python3 bundle_kernel.py validate
  python3 bundle_kernel.py log "hello_event"
  python3 bundle_kernel.py scan
  python3 bundle_kernel.py canon_quote
  python3 bundle_kernel.py status

NOTES:
- Root directory is derived from this file location:
    ROOT = bundle_kernel.py parent directory
- Creates:
    canon/ (AEGIS-K.marker + AEGIS-K.lock + feed_canon_quote.md)
    index/earc.sqlite  (events table)
    metrics/events.jsonl (append-only)
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import datetime as dt
import json
import sqlite3
import sys
from typing import NoReturn


# =========================
# Time / Helpers
# =========================

def utc_z() -> str:
    return dt.datetime.now(dt.UTC).isoformat().replace("+00:00", "Z")


def die(code: int, msg: str) -> NoReturn:
    print(msg)
    raise SystemExit(code)


# =========================
# Paths
# =========================

@dataclass(frozen=True)
class Paths:
    root: Path
    canon: Path
    index: Path
    metrics: Path
    db: Path
    events_jsonl: Path
    marker: Path
    lock: Path
    quote: Path

    @staticmethod
    def from_root(root: Path) -> "Paths":
        canon = root / "canon"
        index = root / "index"
        metrics = root / "metrics"
        return Paths(
            root=root,
            canon=canon,
            index=index,
            metrics=metrics,
            db=index / "earc.sqlite",
            events_jsonl=metrics / "events.jsonl",
            marker=canon / "AEGIS-K.marker",
            lock=canon / "AEGIS-K.lock",
            quote=canon / "feed_canon_quote.md",
        )


def kernel_root() -> Path:
    # root = directory where this bundle file resides
    return Path(__file__).resolve().parent


def P() -> Paths:
    return Paths.from_root(kernel_root())


# =========================
# AEGIS-K (Canon Shell)
# =========================

def assert_aegis_k() -> None:
    p = P()
    if not (p.marker.exists() and p.lock.exists()):
        print("AEGIS-K: MISSING — REFUSE")
        raise SystemExit(1)


def is_in_canon(target: Path) -> bool:
    canon_root = P().canon.resolve()
    t = target.resolve()
    try:
        return t.is_relative_to(canon_root)  # py>=3.9
    except AttributeError:
        return str(t).startswith(str(canon_root))


def deny_write(target: Path) -> None:
    if is_in_canon(target):
        raise PermissionError("AEGIS-K: CANON IS READ-ONLY FOREVER")


def write_text_guarded(path: Path, content: str) -> None:
    """
    Single chokepoint for writes.
    Canon is denied here, always.
    """
    deny_write(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def freeze_canon_best_effort() -> None:
    """
    Best-effort OS-level hardening (POSIX).
    - canon dir: 555
    - canon files: 444
    Safe to fail silently.
    """
    p = P()
    try:
        if p.canon.exists():
            p.canon.chmod(0o555)
            for x in p.canon.iterdir():
                if x.is_file():
                    x.chmod(0o444)
    except Exception:
        # do not break kernel on permission environments
        pass


# =========================
# Seed (Bootstrap)
# =========================

CANON_QUOTE_DEFAULT = """Ewiges Zitat – Kanon der Erkenntnis

„Wir bauen nicht, um zu besitzen.
Wir ordnen, um zu verstehen.

Der Kern bleibt unangetastet.
Der Diamant bleibt geformt.

Alles, was wir erfahren haben,
legen wir nicht in den Kern,
sondern um ihn herum.

Als Archiv der Erkenntnis.

Nicht um zu steuern.
Nicht um zu lehren.

Sondern um zu zeigen,
dass es möglich ist,
rechtzeitig aufzuhören.“
"""


def ensure_dirs() -> None:
    p = P()
    p.root.mkdir(parents=True, exist_ok=True)
    p.canon.mkdir(parents=True, exist_ok=True)
    p.index.mkdir(parents=True, exist_ok=True)
    p.metrics.mkdir(parents=True, exist_ok=True)


def ensure_aegis_files() -> None:
    """
    Canon bootstrap rule:
    - If canon exists but marker/lock missing => REFUSE (no self-heal).
    - Marker/lock/quote may only be created on first init (when canon is new).
    """
    p = P()

    canon_exists = p.canon.exists()
    marker_exists = p.marker.exists()
    lock_exists = p.lock.exists()

    # Canon exists but shell is broken => refuse
    if canon_exists and (not marker_exists or not lock_exists):
        die(1, "AEGIS-K: BROKEN CANON — REFUSE (marker/lock missing)")

    # First init only: create marker/lock/quote if missing
    if not marker_exists:
        p.marker.write_text("AEGIS-K: marker\n", encoding="utf-8")
    if not lock_exists:
        p.lock.write_text("AEGIS-K: lock\n", encoding="utf-8")
    if not p.quote.exists():
        p.quote.write_text(CANON_QUOTE_DEFAULT, encoding="utf-8")

    # Optional OS-level freeze (best effort)
    freeze_canon_best_effort()


def ensure_sqlite() -> None:
    p = P()
    p.db.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("PRAGMA journal_mode=WAL;")
    cur.execute(
        "CREATE TABLE IF NOT EXISTS events("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ts TEXT, "
        "msg TEXT)"
    )
    con.commit()
    con.close()


def append_sqlite(msg: str) -> None:
    p = P()
    ensure_sqlite()
    con = sqlite3.connect(p.db)
    cur = con.cursor()
    cur.execute("INSERT INTO events(ts, msg) VALUES(?,?)", (utc_z(), msg))
    con.commit()
    con.close()


def append_jsonl(msg: str, extra: dict | None = None) -> None:
    p = P()
    p.metrics.mkdir(parents=True, exist_ok=True)
    payload = {"ts": utc_z(), "msg": msg}
    if extra:
        payload.update(extra)
    with p.events_jsonl.open("a", encoding="utf-8") as f:
        f.write(json.dumps(payload, ensure_ascii=False) + "\n")


def seed_init() -> int:
    ensure_dirs()
    ensure_aegis_files()
    ensure_sqlite()
    append_sqlite("seed_ok")
    append_jsonl("seed_ok", {"root": str(P().root)})
    print("SEED:OK")
    print("ROOT:", P().root)
    print("DB:", P().db)
    print("EVENTS:", P().events_jsonl)
    print("CANON:", P().canon)
    return 0


# =========================
# Diamond Shell (Triggers)
# =========================

def cmd_boot() -> int:
    print("BOOT:OK")
    print("ROOT:", P().root)
    return 0


def cmd_where() -> int:
    p = P()
    print("WHERE")
    print("ROOT:", p.root)
    print("CANON:", p.canon)
    print("INDEX:", p.index)
    print("METRICS:", p.metrics)
    print("DB:", p.db)
    print("EVENTS_JSONL:", p.events_jsonl)
    print("AEGIS_MARKER:", p.marker)
    print("AEGIS_LOCK:", p.lock)
    print("CANON_QUOTE:", p.quote)
    return 0


def cmd_validate() -> int:
    # hard gate: AEGIS-K must exist
    assert_aegis_k()

    p = P()
    if not p.canon.exists():
        print("VALIDATE:FAIL canon missing")
        return 1
    print("VALIDATE:OK")
    return 0


def cmd_log(args: list[str]) -> int:
    if not args:
        print("LOG:FAIL missing msg")
        return 1
    msg = " ".join(args).strip()
    append_sqlite(msg)
    append_jsonl(msg)
    print("LOG:OK", msg)
    return 0


def cmd_scan() -> int:
    p = P()
    print("SCAN")
    for key in ("canon", "index", "metrics"):
        d = getattr(p, key)
        if d.exists() and d.is_dir():
            print(f"- {key}/")
            for x in sorted(d.iterdir()):
                print("  ", x.name)
    return 0


def cmd_canon_quote() -> int:
    p = P()
    if not p.quote.exists():
        print("CANON_QUOTE: missing; run init")
        return 1
    print(p.quote.read_text(encoding="utf-8"))
    return 0


def cmd_status() -> int:
    p = P()
    ok_marker = p.marker.exists()
    ok_lock = p.lock.exists()
    ok_db = p.db.exists()
    ok_jsonl = p.events_jsonl.exists()

    print("STATUS")
    print("AEGIS-K.marker:", "OK" if ok_marker else "MISSING")
    print("AEGIS-K.lock:", "OK" if ok_lock else "MISSING")
    print("DB:", "OK" if ok_db else "MISSING")
    print("events.jsonl:", "OK" if ok_jsonl else "MISSING")
    print("ROOT:", p.root)
    return 0


def usage() -> int:
    print("bundle_kernel.py — eArc Bundle Kernel v0.1.1")
    print("Commands:")
    print("  init                 bootstrap folders + AEGIS-K + sqlite + jsonl log")
    print("  boot                 print ROOT")
    print("  where                print key paths")
    print("  validate             enforce AEGIS-K

---

## system · 2026-01-09T22:13:46.290563 UTC



---

