KERNEL 500 · SELBSTTEST-SCRIPT (PROMPT) — v1.0
(als einziger Prompt, den du in ein Kernel-Testprojekt einfügst)

ANALYSE

Aufgabe:
Führe einen vollständigen Kernel-Selbsttest auf dem aktuell geladenen eArc Kernel aus.
Arbeite strikt nach Kernel-Regel: ANALYSE → dann Frage "Output benötigt?"

Testumfang (Pflicht):
1) Identität & Naming
   - eArc Schreibweise, Iinkognit0 (K + 0), keine IAC/IARG
   - ID-Regel: eArc-000-BOOT-xxxxx
2) Output-Gates
   - OUTGATE Default = BLOCKED
   - ASK_OUTPUT aktiv (nur Output auf explizites Kommando)
   - STOPP global erreichbar
3) Formatregeln
   - Kommunikation nur .md oder Code (sauber getrennt)
   - PATH_FIRST valid
4) Trigger-Minimum
   - ANALYSE, OUTPUT, CODE, WEITER, FAKT, KANON, STOPP vorhanden
5) Web/Research Gate
   - Default DENY
   - Freigabe-Regel + Zitierpflicht klar
6) Metadaten-Minimum
   - id, title, type, version, status, created, updated, scope
   - STATUS_ENUM konsistent (DRAFT/FINAL/CANON)
7) Kompositionslogik
   - Module→Block→Superblock als definierter Pfad

Ergebnisformat (noch NICHT ausgeben, erst fragen):
- Report als .md (PATH_FIRST) mit:
  a) Zusammenfassung (1 Absatz)
  b) Checkliste PASS/FAIL pro Punkt
  c) Abweichungen (falls FAIL) + Fix-Empfehlung (minimal)
  d) Kernel-Health-Score: 0–100 (nur aus den Checks abgeleitet, keine Bauchwerte)
  e) Versionsstempel: "Selftest v1.0" + Datum

Abschluss:
Frage exakt:
"Output benötigt? (MD / CODE / KEIN OUTPUT)"