# SoftK501Dev Umsetzung

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## system · 2026-01-08T22:32:22.473086 UTC



---

## user · 2026-01-08T22:32:25.415195 UTC

Projekt: SoftK501Dev

Kontext:
Wir arbeiten an einem Entwicklungs-Kernel namens K501 im Soft-Modus.
Kein gehärteter Kern, keine Gates als Blocker, keine Telemetrie-Perfektion.

Ziel:
Ein lauffähiger, ruhiger Development-Kernel (SoftK501Dev), der:
- validieren kann (pragmatisch, warnend)
- Dateien scannt (sichtbar, einfach)
- Relationen / Graphen extrahiert
- maschinenlesbare Reports erzeugt
- ein simples HUD speist
- später problemlos gehärtet werden kann

Grundprinzipien:
- Work smart, not hard
- Read-only default
- Wirksame Aktionen nur mit Bestätigung
- Keine ausführliche Dokumentation
- Eine einzige maschinenlesbare Kernel-Spec (intern)
- Builder ist Werkzeug, nicht Gesetz
- Gates sind Hinweise (PASS / WARN / N/A), keine Blocker
- Sichtbarkeit vor Formalismus

Nicht tun:
- Keine Hardened-Kernel-Diskussion
- Keine Spec-vs-Real-Debatten
- Kein Tool-Debugging ohne Erkenntnisgewinn
- Keine Feature-Explosion

Erster Fokus:
1. Minimal funktionierender Scan (Dateien > 0 sichtbar)
2. Soft-Validate (Warnings erlaubt)
3. Extract (Links / Graph)
4. Klare, einfache Reports
5. HUD-Grundlogik

Modus:
Soft-K501 Development Mode aktiv.

Beginne mit:
„Analyse: Wie setzen wir SoftK501Dev jetzt minimal und stabil um?“

---

## assistant · 2026-01-08T22:32:33.260606 UTC

**Analyse: Wie setzen wir SoftK501Dev jetzt minimal und stabil um?**

Wir bauen SoftK501Dev als *ruhigen*, *read-only* Dev-Kernel mit einem klaren Pfad: **Scan → Soft-Validate → Extract → Reports → HUD**. Alles andere bleibt absichtlich draußen.

## 0) Minimaler Kern: 3 Dinge, die sofort stehen müssen
1) **Ein stabiles CLI**, das immer deterministisch läuft  
2) **Ein maschinenlesbarer Output**, der sich nicht dauernd ändert  
3) **Ein klarer Datenfluss**: Inputs (Workspace) → Pipeline → Report(s)

Das ergibt die erste stabile Form.

---

## 1) Ordner-/Dateistruktur (klein, aber später härtbar)
Vorschlag:

- `softk501/`
  - `k501.py` (oder `k501.ts`) – Einstieg/CLI
  - `core/`
    - `scan.py`
    - `validate.py`
    - `extract.py`
    - `report.py`
    - `hud.py`
  - `spec/`
    - `kernel_spec.json` *(intern, die einzige Spec)*
  - `out/` *(nur wenn explizit bestätigt / oder in tmp)*
  - `fixtures/` *(kleine Testdaten, optional)*

**Read-only default:** Der Kernel liest Workspace-Dateien, schreibt **nichts** ohne ausdrückliche Bestätigung (oder `--out` + `--yes`).

---

## 2) Ein einziger Pipeline-Run (MVP)
Ein Kommando, das alles anstößt:

- `k501 run <workspace> --out out/ --yes`
- Ohne `--out` oder ohne `--yes` → **kein Schreiben**, nur Console + Exitcode + optional stdout-json.

**Output-Philosophie:**  
- Console: kurz + sichtbar (Counts + wichtigste Warnungen)  
- Report: JSON (maschinenlesbar) + optional eine kleine Text-Zusammenfassung

---

## 3) Schritt 1: Minimal funktionierender Scan (Dateien > 0 sichtbar)
**Scan-Regeln (pragmatisch):**
- Ignoriere standardmäßig: `.git/`, `node_modules/`, `dist/`, `build/`, `out/`, `.obsidian/`
- Konfigurierbar via `kernel_spec.json` (aber default reicht)

**Scan-Output (minimal):**
- `files_total`
- `files_by_ext` (Top N)
- Liste der ersten N Pfade (zur Sichtbarkeit)
- `errors` (z. B. permission denied) als WARN, nicht Crash

---

## 4) Schritt 2: Soft-Validate (WARN erlaubt, Gates nicht blockierend)
Wir definieren Gates als **Hinweise**:

- `PASS` / `WARN` / `N/A`

**Beispiele für erste Gates (nur 3–5, sonst Explosion):**
- `G001 workspace_readable` (PASS/WARN)
- `G010 files_found` (PASS wenn >0, WARN wenn 0)
- `G020 suspicious_large_files` (WARN ab z. B. >10MB)
- `G030 unknown_extensions_ratio` (WARN wenn sehr hoch)

**Wichtig:** Kein “fail the build” in Soft-Modus. Exitcode kann trotzdem **0** bleiben, solange wir den Zustand sauber reporten.

---

## 5) Schritt 3: Extract (Links / Graph) – minimal
Ziel: *Relationen sichtbar machen, ohne Parser-Orgie.*

**Minimal-Extractor v1:**
- Markdown: `[[wikilink]]` und `[text](path)` und bare URLs
- Code: nur *einfache* Imports (z. B. `import x from '…'`, `require('…')`) optional später
- Filesystem-Kanten: Ordnerstruktur als “contains”-Kanten (optional, aber billig)

**Graph-Form (stabil, simpel):**
- Nodes: `id`, `type` (`file`, `url`, `symbol` optional), `path`/`value`
- Edges: `from`, `to`, `kind` (`md_link`, `wikilink`, `import`, `contains`), `confidence` (0–1 optional)

---

## 6) Schritt 4: Klare Reports (maschinenlesbar, ruhig)
Ein Report-File reicht für MVP:

`out/k501.report.json`

Empfohlene Top-Level-Struktur (sehr stabil halten):
```json
{
  "kernel": { "name": "SoftK501Dev", "version": "0.1.0", "mode": "soft-dev" },
  "run": { "id": "timestamp-or-hash", "workspace": "…", "started_at": "…", "ended_at": "…" },
  "scan": { "files_total": 123, "files_by_ext": { ".md": 50 }, "sample_paths": ["…"], "issues": [] },
  "validate": { "gates": [ { "id": "G010", "status": "PASS", "msg": "…" } ] },
  "extract": { "graph": { "nodes": [], "edges": [] }, "stats": { "edges_total": 42 } },
  "hud": { "headline": "PASS with WARN", "counts": { "warn": 3, "pass": 2 }, "focus": ["G020", "G030"] }
}
```

Das ist die Basis für spätere Härtung, weil alles schon *explizit* und *trennbar* ist.

---

## 7) Schritt 5: HUD-Grundlogik (einfach, nicht “UI bauen”)
HUD ist **nur ein dünner Feed**, z. B.:

- `out/k501.hud.json` (oder als Abschnitt im Report)
- enthält nur:
  - `status_summary` (“PASS”, “PASS_WITH_WARN”, “WARN_ONLY”)
  - `top_warnings` (max 5)
  - `counts` (files, nodes, edges, warns)
  - `next_action_hint` (Text, optional)

Keine Animation, kein Dashboard. Nur Speiseformat.

---

## 8) Bestätigungsprinzip (wirksame Aktionen)
Wir definieren “wirksam” als: **Schreiben / Löschen / Modifizieren / Network**.

SoftK501Dev macht im MVP:
- **Kein Network**
- **Kein Modify**
- **Schreiben nur mit** `--out` **und** `--yes`

Alles andere bleibt read-only.

---

## 9) Konkrete MVP-Reihenfolge (damit es nicht zerfasert)
1) **CLI + Scan** → Console zeigt `files_total > 0`
2) **Validate** → Gates als PASS/WARN/N/A im JSON
3) **Extract MD-Links** → Nodes/Edges wachsen sichtbar
4) **Report JSON stabilisieren** → Felder fixieren
5) **HUD JSON** → kleine “Now”-Zusammenfassung

---

## 10) “Minimal und stabil” heißt auch: harte Stop-Liste
Ab jetzt bewusst *nicht*:
- keine Plugin-Architektur
- keine komplexen Parser
- keine Auto-Fixes
- keine “Spec vs Real”-Debatten
- keine Gates als Blocker

---

## Nächster Schritt (sofort umsetzbar)
**Wir implementieren zuerst das Datenmodell + Scan + Report-Writer**, weil alles darauf aufbaut:

- `scan(workspace) -> ScanResult`
- `validate(scan) -> GateResults`
- `extract(scan) -> Graph`
- `report(scan, validate, extract) -> report.json (+ hud.json)`

Wenn du mir sagst, ob du **Python** (schnell, pragmatisch) oder **Node/TS** (Ökosystem-nah) willst, formuliere ich dir direkt die *minimalen* Modul-Signaturen + das CLI-Command-Set so, dass du innerhalb eines Runs schon `out/k501.report.json` hast.

---

## system · 2026-01-08T22:32:33.614250 UTC



---

## assistant · 2026-01-08T22:32:33.634280 UTC



---

## user · 2026-01-08T22:34:10.413607 UTC

Python

---

## system · 2026-01-08T22:34:21.846520 UTC



---

## assistant · 2026-01-08T22:34:26.745021 UTC

Gut — **Python** ist perfekt für “work smart, not hard”: schnell, wenig Overhead, gut für JSON-Reports.

## SoftK501Dev (Python) – Minimal stabile Umsetzung

### 1) Minimaler Projektbaum
```
softk501dev/
  k501.py
  core/
    __init__.py
    scan.py
    validate.py
    extract.py
    report.py
    hud.py
    util.py
  spec/
    kernel_spec.json
```

### 2) CLI-Design (ruhig, deterministisch)
- `python k501.py run <workspace> [--out out/] [--yes] [--stdout-json]`
- Default: **read-only**, **kein Schreiben**
- Schreiben nur, wenn **--out UND --yes**

Exitcodes (simpel):
- `0` immer bei normalem Run (auch mit WARN)
- `2` nur bei “harte” Runtime-Fehler (z. B. workspace nicht lesbar)

---

## 3) Direkt lauffähiger MVP-Code (Skeleton)

### `k501.py`
```python
#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from datetime import datetime, timezone

from core.scan import scan_workspace
from core.validate import soft_validate
from core.extract import extract_relations
from core.report import build_report, write_report_files
from core.hud import build_hud


KERNEL_NAME = "SoftK501Dev"
KERNEL_VERSION = "0.1.0"
KERNEL_MODE = "soft-dev"


def _utc_now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(prog="k501", add_help=True)
    sub = p.add_subparsers(dest="cmd", required=True)

    run = sub.add_parser("run", help="Scan → Soft-Validate → Extract → Report → HUD")
    run.add_argument("workspace", type=str, help="Workspace path")
    run.add_argument("--out", type=str, default=None, help="Output directory (requires --yes)")
    run.add_argument("--yes", action="store_true", help="Confirm writing outputs")
    run.add_argument("--stdout-json", action="store_true", help="Print report JSON to stdout")
    run.add_argument("--max-sample", type=int, default=30, help="Sample paths to include")
    run.add_argument("--max-warn", type=int, default=50, help="Max warnings to include in report")

    return p.parse_args()


def main() -> int:
    args = parse_args()
    if args.cmd != "run":
        return 2

    workspace = Path(args.workspace).expanduser().resolve()
    started_at = _utc_now_iso()

    try:
        scan = scan_workspace(workspace, max_sample=args.max_sample)
        gates = soft_validate(scan)
        graph = extract_relations(workspace, scan)
        hud = build_hud(scan, gates, graph, max_items=5)

        ended_at = _utc_now_iso()
        report = build_report(
            kernel_name=KERNEL_NAME,
            kernel_version=KERNEL_VERSION,
            mode=KERNEL_MODE,
            workspace=workspace,
            started_at=started_at,
            ended_at=ended_at,
            scan=scan,
            gates=gates,
            graph=graph,
            hud=hud,
            max_warn=args.max_warn,
        )

        # Console: ruhig + sichtbar
        print(f"{KERNEL_NAME} {KERNEL_VERSION} [{KERNEL_MODE}]")
        print(f"Workspace: {workspace}")
        print(f"Files: {report['scan']['files_total']} | Nodes: {report['extract']['graph']['stats']['nodes_total']} | "
              f"Edges: {report['extract']['graph']['stats']['edges_total']}")
        warn_count = sum(1 for g in report["validate"]["gates"] if g["status"] == "WARN")
        print(f"Gates: {len(report['validate']['gates'])} | WARN: {warn_count}")
        if hud.get("top_warnings"):
            print("Top warnings:")
            for w in hud["top_warnings"]:
                print(f"  - {w}")

        if args.stdout_json:
            print(json.dumps(report, ensure_ascii=False, indent=2))

        # Write only with confirmation
        if args.out and args.yes:
            out_dir = Path(args.out).expanduser().resolve()
            write_report_files(out_dir, report)
            print(f"Wrote: {out_dir / 'k501.report.json'}")
            print(f"Wrote: {out_dir / 'k501.hud.json'}")
        elif args.out and not args.yes:
            print("NOTE: --out provided but --yes missing. Read-only mode: nothing written.")

        return 0

    except Exception as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
```

### `core/scan.py`
```python
from __future__ import annotations

from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, List, Tuple


DEFAULT_IGNORE_DIRS = {
    ".git", "node_modules", "dist", "build", "out", ".obsidian", ".venv", "__pycache__"
}


@dataclass
class ScanIssue:
    level: str          # "WARN" only for MVP
    msg: str
    path: str | None = None


@dataclass
class ScanResult:
    workspace: str
    files_total: int
    files_by_ext: Dict[str, int]
    sample_paths: List[str]
    issues: List[ScanIssue]

    def to_dict(self) -> dict:
        d = asdict(self)
        d["issues"] = [asdict(i) for i in self.issues]
        return d


def _ext_of(p: Path) -> str:
    return p.suffix.lower() if p.suffix else "<none>"


def scan_workspace(workspace: Path, max_sample: int = 30) -> ScanResult:
    if not workspace.exists():
        raise RuntimeError("workspace does not exist")
    if not workspace.is_dir():
        raise RuntimeError("workspace is not a directory")

    files_by_ext: Dict[str, int] = {}
    sample: List[str] = []
    issues: List[ScanIssue] = []
    total = 0

    # Deterministic traversal: sorted
    for p in sorted(workspace.rglob("*")):
        try:
            if p.is_dir():
                if p.name in DEFAULT_IGNORE_DIRS:
                    # Skip subtree by ignoring contents via pattern: handled by continuing
                    # (rglob cannot prune easily; keep minimal for MVP)
                    continue
                continue

            # Skip ignored dirs by checking parts
            if any(part in DEFAULT_IGNORE_DIRS for part in p.parts):
                continue

            total += 1
            ext = _ext_of(p)
            files_by_ext[ext] = files_by_ext.get(ext, 0) + 1

            if len(sample) < max_sample:
                sample.append(str(p.relative_to(workspace)))

        except Exception as e:
            issues.append(ScanIssue(level="WARN", msg=f"scan issue: {e}", path=str(p)))

    return ScanResult(
        workspace=str(workspace),
        files_total=total,
        files_by_ext=dict(sorted(files_by_ext.items(), key=lambda kv: (-kv[1], kv[0]))),
        sample_paths=sample,
        issues=issues,
    )
```

### `core/validate.py`
```python
from __future__ import annotations

from dataclasses import dataclass, asdict
from typing import List

from core.scan import ScanResult


@dataclass
class GateResult:
    id: str
    status: str   # "PASS" | "WARN" | "N/A"
    msg: str

    def to_dict(self) -> dict:
        return asdict(self)


def soft_validate(scan: ScanResult) -> List[GateResult]:
    gates: List[GateResult] = []

    # G001 workspace readable: if we got ScanResult, it's readable enough
    gates.append(GateResult("G001", "PASS", "workspace readable"))

    # G010 files found
    if scan.files_total > 0:
        gates.append(GateResult("G010", "PASS", f"files found: {scan.files_total}"))
    else:
        gates.append(GateResult("G010", "WARN", "no files found"))

    # G020 scan issues
    if scan.issues:
        gates.append(GateResult("G020", "WARN", f"scan issues: {len(scan.issues)}"))
    else:
        gates.append(GateResult("G020", "PASS", "no scan issues"))

    # G030 unknown extension ratio (very rough, but useful)
    none = scan.files_by_ext.get("<none>", 0)
    if scan.files_total > 0 and (none / scan.files_total) > 0.5:
        gates.append(GateResult("G030", "WARN", "high ratio of files without extension"))
    else:
        gates.append(GateResult("G030", "PASS", "extension distribution ok"))

    return gates
```

### `core/extract.py` (MVP: nur Markdown-Links)
```python
from __future__ import annotations

import re
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, List, Set

from core.scan import ScanResult


WIKILINK_RE = re.compile(r"\[\[([^\]]+)\]\]")
MDLINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")
URL_RE = re.compile(r"(https?://[^\s)]+)")


@dataclass
class Graph:
    nodes: List[dict]
    edges: List[dict]
    stats: dict

    def to_dict(self) -> dict:
        return {"nodes": self.nodes, "edges": self.edges, "stats": self.stats}


def extract_relations(workspace: Path, scan: ScanResult) -> Graph:
    nodes: Dict[str, dict] = {}
    edges: List[dict] = []

    def node_file(rel: str) -> str:
        nid = f"file:{rel}"
        if nid not in nodes:
            nodes[nid] = {"id": nid, "type": "file", "path": rel}
        return nid

    def node_url(url: str) -> str:
        nid = f"url:{url}"
        if nid not in nodes:
            nodes[nid] = {"id": nid, "type": "url", "value": url}
        return nid

    # Only parse .md files for MVP
    md_files = [p for p in scan.sample_paths]  # sample-only for MVP stability/speed
    # If you want full set later: scan again and parse all .md (keep MVP calm)

    for rel in md_files:
        if not rel.lower().endswith(".md"):
            continue

        src_id = node_file(rel)
        abs_path = workspace / rel
        try:
            text = abs_path.read_text(encoding="utf-8", errors="ignore")
        except Exception:
            continue

        # [[wikilink]]
        for m in WIKILINK_RE.findall(text):
            target = m.strip()
            # keep as symbolic file-ish node for now
            tid = f"wikilink:{target}"
            if tid not in nodes:
                nodes[tid] = {"id": tid, "type": "wikilink", "value": target}
            edges.append({"from": src_id, "to": tid, "kind": "wikilink", "confidence": 0.9})

        # [text](path)
        for _, link in MDLINK_RE.findall(text):
            link = link.strip()
            if link.startswith("http://") or link.startswith("https://"):
                tid = node_url(link)
                edges.append({"from": src_id, "to": tid, "kind": "md_link_url", "confidence": 0.9})
            else:
                # treat as path-ish
                tid = f"ref:{link}"
                if tid not in nodes:
                    nodes[tid] = {"id": tid, "type": "ref", "value": link}
                edges.append({"from": src_id, "to": tid, "kind": "md_link_ref", "confidence": 0.7})

        # bare URLs
        for url in URL_RE.findall(text):
            tid = node_url(url)
            edges.append({"from": src_id, "to": tid, "kind": "url", "confidence": 0.6})

    graph = Graph(
        nodes=list(nodes.values()),
        edges=edges,
        stats={
            "nodes_total": len(nodes),
            "edges_total": len(edges),
        },
    )
    return graph
```

### `core/hud.py`
```python
from __future__ import annotations

from typing import List

from core.scan import ScanResult
from core.validate import GateResult
from core.extract import Graph


def build_hud(scan: ScanResult, gates: List[GateResult], graph: Graph, max_items: int = 5) -> dict:
    warn_gates = [g for g in gates if g.status == "WARN"]
    status_summary = "PASS_WITH_WARN" if warn_gates else "PASS"

    top_warnings = [f"{g.id}: {g.msg}" for g in warn_gates[:max_items]]

    focus = [g.id for g in warn_gates[:max_items]]
    next_hint = "Address WARN gates if they matter; otherwise continue." if warn_gates else "Proceed."

    return {
        "status_summary": status_summary,
        "counts": {
            "files": scan.files_total,
            "warn_gates": len(warn_gates),
            "nodes": graph.stats.get("nodes_total", 0),
            "edges": graph.stats.get("edges_total", 0),
        },
        "top_warnings": top_warnings,
        "focus": focus,
        "next_action_hint": next_hint,
    }
```

### `core/report.py`
```python
from __future__ import annotations

import json
from pathlib import Path
from typing import List

from core.scan import ScanResult
from core.validate import GateResult
from core.extract import Graph


def build_report(
    kernel_name: str,
    kernel_version: str,
    mode: str,
    workspace: Path,
    started_at: str,
    ended_at: str,
    scan: ScanResult,
    gates: List[GateResult],
    graph: Graph,
    hud: dict,
    max_warn: int = 50,
) -> dict:
    # cap scan issues in report for calmness
    scan_dict = scan.to_dict()
    scan_dict["issues"] = scan_dict["issues"][:max_warn]

    return {
        "kernel": {"name": kernel_name, "version": kernel_version, "mode": mode},
        "run": {
            "workspace": str(workspace),
            "started_at": started_at,
            "ended_at": ended_at,
        },
        "scan": scan_dict,
        "validate": {"gates": [g.to_dict() for g in gates]},
        "extract": {"graph": {"nodes": graph.nodes, "edges": graph.edges, "stats": graph.stats}},
        "hud": hud,
    }


def write_report_files(out_dir: Path, report: dict) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)
    report_path = out_dir / "k501.report.json"
    hud_path = out_dir / "k501.hud.json"

    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8")
    hud_path.write_text(json.dumps(report.get("hud", {}), ensure_ascii=False, indent=2), encoding="utf-8")
```

---

## 4) Sofort testen
Im Projektordner:
```bash
python k501.py run . --stdout-json
python k501.py run . --out out --yes
```

Erwartung (MVP):
- Console zeigt `Files: >0`
- `out/k501.report.json` + `out/k501.hud.json` existieren
- Gates zeigen PASS/WARN, nie “blockierend”

---

## 5) Nächster kleiner Schritt (ohne Feature-Explosion)
Wenn das steht, ist der beste ruhige Upgrade:
- **Scan nicht nur sample_paths**, sondern alle `.md` (mit Limit/Chunking), aber weiterhin deterministisch.
- Optional: `--max-parse-files N` für Ruhe.

Wenn du willst, kann ich dir als nächstes **eine ultrakurze `kernel_spec.json` (intern)** geben (Ignore-Dirs, Parse-Exts, Limits), ohne “Dokuwand”.

---

## user · 2026-01-08T22:42:27.523552 UTC

Upgrade 

---

## system · 2026-01-08T22:42:32.976564 UTC



---

## assistant · 2026-01-08T22:42:37.784136 UTC



---

## assistant · 2026-01-08T22:42:37.828636 UTC

Alles klar: **Upgrade** heißt jetzt *mehr Nutzen bei gleicher Ruhe* — ohne Feature-Explosion.

## Ziel des Upgrades (v0.1.1)
1) **Scan wird sauber prunable** (ignorierte Ordner werden wirklich nicht traversiert)  
2) **Extract parsed alle `.md`**, nicht nur `sample_paths` — aber **mit Limit** (Ruhe)  
3) **Interne Spec** (`spec/kernel_spec.json`) steuert Ignore/Parsing/Limits  
4) Report bleibt **stabil** (gleiches Schema), nur bessere Daten

---

## Upgrade-Schritt A: `kernel_spec.json` (intern, klein)
`spec/kernel_spec.json`
```json
{
  "ignore_dirs": [".git", "node_modules", "dist", "build", "out", ".obsidian", ".venv", "__pycache__"],
  "scan": { "max_sample": 30 },
  "extract": {
    "parse_exts": [".md"],
    "max_parse_files": 1000,
    "max_file_bytes": 1048576
  }
}
```

---

## Upgrade-Schritt B: Spec laden (ohne Doku, ohne Drama)
### `core/util.py`
```python
from __future__ import annotations
import json
from pathlib import Path

def load_spec(spec_path: Path) -> dict:
    if not spec_path.exists():
        return {}
    try:
        return json.loads(spec_path.read_text(encoding="utf-8"))
    except Exception:
        return {}
```

### `k501.py` (minimal ergänzen)
- Spec laden: `spec/kernel_spec.json`
- Spec-Werte für `max_sample`, `ignore_dirs`, `extract`-Limits verwenden

Patch-Idee (konkret, kurz):
```python
from core.util import load_spec

spec = load_spec(Path(__file__).parent / "spec" / "kernel_spec.json")
ignore_dirs = set(spec.get("ignore_dirs", []))
max_sample = spec.get("scan", {}).get("max_sample", args.max_sample)

scan = scan_workspace(workspace, ignore_dirs=ignore_dirs, max_sample=max_sample)

extract_cfg = spec.get("extract", {})
graph = extract_relations(workspace, scan, extract_cfg=extract_cfg)
```

---

## Upgrade-Schritt C: Scan prunable (kein rglob mehr)
`rglob("*")` kann nicht sauber “prunen”. Wir gehen auf `os.walk()` (deterministisch + prune).

### `core/scan.py` (ersetzen/upgrade)
```python
from __future__ import annotations

import os
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, List, Set


@dataclass
class ScanIssue:
    level: str
    msg: str
    path: str | None = None


@dataclass
class ScanResult:
    workspace: str
    files_total: int
    files_by_ext: Dict[str, int]
    sample_paths: List[str]
    issues: List[ScanIssue]

    def to_dict(self) -> dict:
        d = asdict(self)
        d["issues"] = [asdict(i) for i in self.issues]
        return d


def _ext_of(p: str) -> str:
    suf = Path(p).suffix.lower()
    return suf if suf else "<none>"


def scan_workspace(workspace: Path, ignore_dirs: Set[str], max_sample: int = 30) -> ScanResult:
    if not workspace.exists():
        raise RuntimeError("workspace does not exist")
    if not workspace.is_dir():
        raise RuntimeError("workspace is not a directory")

    files_by_ext: Dict[str, int] = {}
    sample: List[str] = []
    issues: List[ScanIssue] = []
    total = 0

    # Deterministic walk: sort dirs/files
    for root, dirs, files in os.walk(workspace):
        # prune ignored directories in-place
        dirs[:] = sorted([d for d in dirs if d not in ignore_dirs])

        files_sorted = sorted(files)
        for fn in files_sorted:
            abs_path = Path(root) / fn
            try:
                rel = abs_path.relative_to(workspace).as_posix()
                total += 1

                ext = _ext_of(fn)
                files_by_ext[ext] = files_by_ext.get(ext, 0) + 1

                if len(sample) < max_sample:
                    sample.append(rel)

            except Exception as e:
                issues.append(ScanIssue(level="WARN", msg=f"scan issue: {e}", path=str(abs_path)))

    files_by_ext = dict(sorted(files_by_ext.items(), key=lambda kv: (-kv[1], kv[0])))

    return ScanResult(
        workspace=str(workspace),
        files_total=total,
        files_by_ext=files_by_ext,
        sample_paths=sample,
        issues=issues,
    )
```

---

## Upgrade-Schritt D: Extract alle `.md` (ruhig, limitiert)
Wir parsen **alle `.md` im Workspace**, aber:
- `max_parse_files` (z. B. 1000)
- `max_file_bytes` (z. B. 1 MB)
- deterministic ordering

### `core/extract.py` (upgrade Signatur + Implementation)
```python
from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List

from core.scan import ScanResult


WIKILINK_RE = re.compile(r"\[\[([^\]]+)\]\]")
MDLINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")
URL_RE = re.compile(r"(https?://[^\s)]+)")


@dataclass
class Graph:
    nodes: List[dict]
    edges: List[dict]
    stats: dict


def extract_relations(workspace: Path, scan: ScanResult, extract_cfg: dict | None = None) -> Graph:
    extract_cfg = extract_cfg or {}
    parse_exts = set([e.lower() for e in extract_cfg.get("parse_exts", [".md"])])
    max_parse_files = int(extract_cfg.get("max_parse_files", 1000))
    max_file_bytes = int(extract_cfg.get("max_file_bytes", 1_048_576))

    nodes: Dict[str, dict] = {}
    edges: List[dict] = []

    def node_file(rel: str) -> str:
        nid = f"file:{rel}"
        if nid not in nodes:
            nodes[nid] = {"id": nid, "type": "file", "path": rel}
        return nid

    def node_url(url: str) -> str:
        nid = f"url:{url}"
        if nid not in nodes:
            nodes[nid] = {"id": nid, "type": "url", "value": url}
        return nid

    # Deterministic: build full list of candidate files by ext from filesystem
    # (ScanResult currently doesn't carry all file paths; we just walk once here.)
    candidates: List[Path] = []
    for p in sorted(workspace.rglob("*")):
        if p.is_file() and p.suffix.lower() in parse_exts:
            candidates.append(p)
            if len(candidates) >= max_parse_files:
                break

    parsed_files = 0
    skipped_large = 0

    for abs_path in candidates:
        try:
            if abs_path.stat().st_size > max_file_bytes:
                skipped_large += 1
                continue
            rel = abs_path.relative_to(workspace).as_posix()
            src_id = node_file(rel)

            text = abs_path.read_text(encoding="utf-8", errors="ignore")

            for m in WIKILINK_RE.findall(text):
                target = m.strip()
                tid = f"wikilink:{target}"
                if tid not in nodes:
                    nodes[tid] = {"id": tid, "type": "wikilink", "value": target}
                edges.append({"from": src_id, "to": tid, "kind": "wikilink", "confidence": 0.9})

            for _, link in MDLINK_RE.findall(text):
                link = link.strip()
                if link.startswith("http://") or link.startswith("https://"):
                    tid = node_url(link)
                    edges.append({"from": src_id, "to": tid, "kind": "md_link_url", "confidence": 0.9})
                else:
                    tid = f"ref:{link}"
                    if tid not in nodes:
                        nodes[tid] = {"id": tid, "type": "ref", "value": link}
                    edges.append({"from": src_id, "to": tid, "kind": "md_link_ref", "confidence": 0.7})

            for url in URL_RE.findall(text):
                tid = node_url(url)
                edges.append({"from": src_id, "to": tid, "kind": "url", "confidence": 0.6})

            parsed_files += 1

        except Exception:
            # Soft mode: ignore parsing failures silently for now
            continue

    stats = {
        "nodes_total": len(nodes),
        "edges_total": len(edges),
        "parsed_files": parsed_files,
        "skipped_large_files": skipped_large,
        "max_parse_files": max_parse_files,
        "max_file_bytes": max_file_bytes,
    }

    return Graph(nodes=list(nodes.values()), edges=edges, stats=stats)
```

> Hinweis: Hier nutze ich für Extract wieder `rglob`. Wenn du willst, können wir das später ebenfalls auf `os.walk` umstellen (prune + speed). Für v0.1.1 ist das okay, weil Extract eh limitiert ist.

---

## Upgrade-Schritt E: Report stabil halten (nur Stats erweitern)
Dein `report.py` bleibt praktisch gleich. Du bekommst automatisch in:
`report["extract"]["graph"]["stats"]`
mehr Felder (`parsed_files`, `skipped_large_files`, …). HUD kann die verwenden.

Optional: HUD nutzt `parsed_files` statt `sample_paths`.

---

## Test (genau deine Befehle)
```bash
python k501.py run . --stdout-json
python k501.py run . --out out --yes
```

Erwartete sichtbare Verbesserung:
- Scan ist schneller/ruhiger (ignorierte Ordner werden pruned)
- Extract findet Links in **allen** `.md` (bis zum Limit)
- Report bleibt maschinenlesbar + stabil
- HUD zeigt weiterhin “PASS / PASS_WITH_WARN”

---

## Nächster Upgrade danach (nur 1 sinnvoller)
Wenn v0.1.1 steht: **Scan speichert optional eine “file_index” Liste** (Paths + size + ext) in Report *oder* separat als `k501.files.json`. Dann muss Extract nicht mehr selbst laufen/walken, sondern nutzt Index → deterministisch + schnell.

Wenn du willst, gebe ich dir dafür direkt das minimal-invasive Patch-Set (ohne neue Features, nur Index).

---

## user · 2026-01-08T22:48:28.868627 UTC

python k501.py run . --stdout-json
python k501.py run . --out out --yes

---

## assistant · 2026-01-08T22:48:39.198360 UTC

Perfekt — das sind genau die zwei “Soft”-Runs:

1) **Read-only + stdout JSON**
```bash
python k501.py run . --stdout-json
```
Erwartung:
- Console zeigt Kernel + Workspace + Counts (Files/Nodes/Edges/Gates/WARN).
- Danach kommt ein **JSON-Block** auf stdout (Report).
- **Keine Dateien werden geschrieben**.

2) **Write-Run (nur mit Bestätigung)**
```bash
python k501.py run . --out out --yes
```
Erwartung:
- Console wieder Counts
- Danach:
  - `Wrote: out/k501.report.json`
  - `Wrote: out/k501.hud.json`

## Wenn etwas nicht klappt (schnellste Checks)

### A) “ModuleNotFoundError: No module named core …”
Dann ist dein Layout nicht als Package erkannt oder du startest aus dem falschen Ordner.

**Fix (empfohlen):**
- Stelle sicher:
  - `softk501dev/core/__init__.py` existiert
  - du führst den Befehl im Ordner aus, wo `k501.py` liegt

Oder starte mit:
```bash
python -m k501 run . --stdout-json
```
(dafür muss `k501.py` als Modul erreichbar sein – ich helfe dir dann beim minimalen Package-Setup.)

### B) `--out` ohne `--yes`
Dann kommt (korrekt):
> NOTE: --out provided but --yes missing. Read-only mode: nothing written.

### C) JSON ist da, aber Nodes/Edges = 0
Dann werden keine `.md` geparst (oder keine im Workspace / Limits greifen).
- Check `spec/kernel_spec.json`:
  - `"parse_exts": [".md"]`
  - `"max_parse_files"` nicht zu klein
  - `"max_file_bytes"` nicht zu klein

---

Wenn du mir **die Console-Ausgabe** (die ersten ~20 Zeilen reichen) oder den Kopf von `k501.report.json` (nur `scan.files_total`, `validate.gates`, `extract.graph.stats`) hier reinkopierst, sag ich dir sofort, ob v0.1.1 “ruhig korrekt” läuft oder wo genau es klemmt.

---

## system · 2026-01-08T22:48:39.697105 UTC



---

## user · 2026-01-08T22:49:13.449608 UTC

python k501.py run . --stdout-json

---

## assistant · 2026-01-08T22:49:19.120135 UTC

Wenn du **`python k501.py run . --stdout-json`** ausführst, passiert (im Soll-Zustand) genau das:

- **Console (kurz):** Kernel/Version/Mode, Workspace-Pfad, Counts (Files/Nodes/Edges), Gate-WARN Count, ggf. “Top warnings”
- **Danach:** ein **kompletter JSON-Report** auf stdout (weil `--stdout-json`)

Wichtig: **Es wird nichts geschrieben**, weil kein `--out --yes` gesetzt ist.

---

### Wenn du stattdessen einen Fehler bekommst, sind das die 3 häufigsten:

**1) `ModuleNotFoundError: No module named 'core'`**  
Du startest nicht aus dem Ordner, in dem `k501.py` liegt, oder `core/__init__.py` fehlt.  
Fix:
- Prüfe, dass `core/__init__.py` existiert
- Starte im gleichen Ordner wie `k501.py`

**2) `RuntimeError: workspace does not exist / not a directory`**  
Dann ist `.` nicht das, was du denkst (z. B. falsches working directory).

**3) Output ist da, aber `nodes_total=0` / `edges_total=0`**  
Dann findet Extract keine `.md` (oder Limits greifen). Check `spec/kernel_spec.json` (`parse_exts`, `max_parse_files`, `max_file_bytes`).

---

Kopier mir einfach **die ersten ~30 Zeilen deiner Ausgabe** (oder den konkreten Error-Block). Dann sag ich dir sofort: *läuft korrekt* vs. *wo es genau klemmt* – ohne Tool-Debug-Orgie.

---

## system · 2026-01-08T22:49:19.423296 UTC



---

## user · 2026-01-08T22:50:45.052832 UTC

python -m k501 run . --stdout-json

---

## system · 2026-01-08T22:50:45.508933 UTC



---

## assistant · 2026-01-08T22:50:45.556890 UTC

Gut — der Befehl **zeigt genau, wo wir stehen**.  
Kurzfassung: **`python -m k501` funktioniert nur, wenn `k501` ein Paket ist.**  
Im aktuellen Setup ist `k501.py` **ein Skript**, kein Modul.

Ich gebe dir jetzt **zwei saubere, minimale Lösungen**. Nimm **eine** davon.

---

## ✅ Option A (empfohlen, minimal & ruhig): **Skript-Modus beibehalten**
Das ist der **einfachste und stabilste Weg** für SoftK501Dev.

### Struktur
```
softk501dev/
  k501.py
  core/
    __init__.py
    scan.py
    validate.py
    extract.py
    report.py
    hud.py
    util.py
  spec/
    kernel_spec.json
```

### Start **IM selben Ordner wie `k501.py`**
```bash
cd softk501dev
python k501.py run . --stdout-json
```

✔ Kein Packaging  
✔ Kein PYTHONPATH  
✔ Genau richtig für Dev-Kernel

👉 **Wenn das dein Ziel ist: bleib dabei.**  
Dann **nicht** `python -m k501` benutzen.

---

## ✅ Option B (wenn du `python -m k501` willst): **Mini-Paket**
Nur nötig, **wenn du explizit Modul-Start willst**.

### Neue Struktur
```
softk501dev/
  k501/
    __init__.py
    __main__.py
  core/
    __init__.py
    scan.py
    validate.py
    extract.py
    report.py
    hud.py
    util.py
  spec/
    kernel_spec.json
```

### Inhalt `k501/__main__.py`
```python
from k501 import main

if __name__ == "__main__":
    raise SystemExit(main())
```

### Inhalt `k501/__init__.py`
```python
from pathlib import Path
import sys

# allow importing core/*
ROOT = Path(__file__).parent.parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from k501_entry import main  # siehe unten
```

### Umbenennen
- `k501.py` → `k501_entry.py`
- Code bleibt **identisch**

### Start
```bash
python -m k501 run . --stdout-json
```

✔ funktioniert  
✖ mehr Struktur  
✖ mehr Moving Parts

---

## 🔍 Warum dein aktueller Befehl scheitert (wichtiges Verständnis)
```bash
python -m k501
```
heißt:
> „Starte ein **Paket oder Modul** namens `k501`“

Aber du hast:
- ✅ `k501.py` → **Skript**
- ❌ kein `k501/`-Paket

Python kann das **nicht erraten** — korrektes Verhalten.

---

## 🧭 Empfehlung für SoftK501Dev
👉 **Option A**  
- ruhig  
- robust  
- zero ceremony  
- exakt im Sinne von *Soft / Dev / sichtbar*

Wenn du willst, sage einfach:
> **„Bleiben wir bei Skript-Modus“**

Dann gehe ich als Nächstes mit dir:
- ✔️ über **Smoke-Test-Checkliste**
- ✔️ oder **kleinen File-Index-Upgrade**
- ✔️ oder **Exitcode-/HUD-Feinschliff**

Sag nur, **welcher nächste Schritt**.

---

