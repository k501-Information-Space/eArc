# Befehle im SoftK501Dev

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## user · 2026-01-08T22:41:07.746031 UTC

python k501.py run . --stdout-json
python k501.py run . --out out --yes

---

## system · 2026-01-08T22:41:08.044132 UTC



---

## assistant · 2026-01-08T22:41:10.477153 UTC

Kurz erklärt, was diese beiden Befehle im **SoftK501Dev-Kontext** bedeuten und wann du welchen nutzt:

---

## 1️⃣ `python k501.py run . --stdout-json`

**Zweck:**  
Analyse **ausführen und Ergebnis direkt nach STDOUT als JSON ausgeben**.

**Was passiert:**
- `run .` → scannt das aktuelle Verzeichnis (`.`)
- `--stdout-json` →
  - **keine Dateien werden geschrieben**
  - kompletter Report geht **nur an STDOUT**
  - ideal für:
    - Pipes (`| jq`, `| less`)
    - Tests
    - CI / manuelle Sichtprüfung
    - schnelles Debugging

**Charakter:**  
🟢 *Read-only, flüchtig, null Seiteneffekte*

**Typische Nutzung:**
```bash
python k501.py run . --stdout-json | jq '.summary'
```

---

## 2️⃣ `python k501.py run . --out out --yes`

**Zweck:**  
Analyse **ausführen und Ergebnisse persistent speichern**.

**Was passiert:**
- `run .` → scannt das aktuelle Verzeichnis
- `--out out` →
  - Zielverzeichnis für alle Outputs (`./out`)
  - z. B.:
    - `report.json`
    - `graph.json`
    - `warnings.json`
    - später: HUD-Inputs
- `--yes` →
  - bestätigt **alle wirksamen Aktionen**
  - kein interaktives Nachfragen
  - notwendig, weil hier **Dateien erzeugt werden**

**Charakter:**  
🟡 *Write-enabled, bewusst bestätigt, reproduzierbar*

**Typische Nutzung:**
```bash
python k501.py run . --out out --yes
```

---

## 🧭 Entscheidungslogik (Soft-Kernel-Philosophie)

| Situation | Empfohlener Befehl |
|--------|------------------|
| Schnell prüfen | `--stdout-json` |
| Debug / Pipe | `--stdout-json` |
| Archiv / Vergleich | `--out … --yes` |
| HUD speisen | `--out … --yes` |
| CI / Automatik | abhängig vom Kontext |

---

## 🧠 Design-Logik dahinter (passt exakt zu K501)

- **STDOUT = Denken**
- **Files = Handeln**
- Handeln braucht Zustimmung (`--yes`)
- Denken ist immer frei

Kein Automatismus.  
Keine Überraschungen.  
Kein versteckter Write.

Wenn du willst, kann ich dir als Nächstes:
- das **erwartete JSON-Schema** skizzieren
- oder eine **Minimal-CI-Pipeline** mit beiden Modi zeigen
- oder die **interne Entscheidungslogik** (`stdout-json` vs `out`) formal festhalten

Sag einfach, in welche Richtung du weitergehen willst.

---

## assistant · 2026-01-08T22:41:10.848857 UTC



---

