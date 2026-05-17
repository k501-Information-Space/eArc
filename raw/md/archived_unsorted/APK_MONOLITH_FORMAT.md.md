/release/APK_MONOLITH_FORMAT.md
# eArc · APK Monolith Source Bundle Format
Status: release · frozen-ready · deterministic

HEUREKA 🌋

---

## Zweck
Ein einzelner Copy/Paste-Block enthält den kompletten Android-Quellcode (Projektstruktur + Dateien),
so dass er später **verlustfrei rekonstruiert** und gebaut werden kann.

---

## Grundsatz
- **Ein Block** = viele Dateien
- **Keine Ausführung** (nur Source)
- **Deterministisch** (1:1 rekonstruierbar)
- **Keine Interpretation** (nur Container)

---

## Separator-Standard (verbindlich)

Jede Datei beginnt exakt so:

===== FILE: <RELATIVE_PATH> =====
<CONTENT>
===== END FILE =====

Beispiele:
===== FILE: settings.gradle.kts =====
...
===== END FILE =====

===== FILE: app/src/main/AndroidManifest.xml =====
...
===== END FILE =====

---

## Pfadregeln
- `<RELATIVE_PATH>` ist relativ zur Projektwurzel
- Nur `/` als Separator (auch auf Windows)
- Keine absoluten Pfade
- Keine zufälligen Zusatzzeilen vor dem ersten `FILE:`

---

## Encoding & Zeilen
- UTF-8
- LF (`\n`) bevorzugt
- Inhalt wird exakt übernommen

---

## Rekonstruktion (manuell)
1. Neues leeres Verzeichnis anlegen (Projektroot)
2. Monolith-Block Datei für Datei abarbeiten:
   - Pfad anlegen (Ordnerstruktur)
   - Inhalt exakt einfügen
3. Danach Build via Android Studio oder Gradle

---

## Rekonstruktion (Script-Idee, optional)
- Parser liest den Monolith
- Für jeden `FILE:` Block:
  - mkdir -p dirname(path)
  - write content
- Keine Extras, kein Template

---

## Release-Konventionen
- Monolith-Dateiname: `APK_MONOLITH.md` oder `APK_MONOLITH.txt`
- Zusätzlich (klein):
  - `README.md`
  - `LICENSE`
  - `CHANGELOG.md` (optional)

---

## Sicherheits- und eArc-Regeln
- Kein Push, kein Tracking, keine Telemetrie
- COMM default OFF (nur bewusst)
- Alles additiv, nichts überschreiben
- Logs append-only (wenn Logs genutzt werden)

---

—
Quelle: iinkognit0.de