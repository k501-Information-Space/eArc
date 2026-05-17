Verstanden — Ist-Zustand ist jetzt als Referenz gespeichert (REFERENCE_ONLY/APPEND_ONLY) inkl. QH256-Draft, Testvektoren, Validator-Pseudocode, Receipt-Beispiele, minimaler Go-Validator und aktuelle Pipeline-Marker.

  

Jetzt bekommst du (1) den festen Ist-Stand und (2) die komplette Roadmap bis “K501 live inkl. Google Cloud Build/Compile” — mit Prioritäten + kurzer Erklärung, was jeweils passiert.

  

  

  

  

1) Ist-Zustand (heute, konkret)

  

  

  

QH / Validator Pipeline (neu, heute geschlossen – Draft-Ebene)

  

  

- QH256 Spec v1 DRAFT: 256 Bit / 32 Byte, 128×2-Bit Cells, Regionen R0–R3, R3 Guard Default = 11
- Test Vectors v1 DRAFT: TV1 (PASS), TV2 (PASS), TV3 (FAIL/WARN)
- Validator Pseudocode v1 DRAFT: deterministischer Decoder + Guard-Check + Profil-Logik + Receipt Builder
- Receipt Examples v1 DRAFT: PASS/WARN/FAIL Beispiele
- Minimaler Go-Validator v1 DRAFT: kein externes Dependency, kann TV1–TV3 prüfen

  

  

➡️ Ergebnis: End-to-End Kette ist modelliert und als Referenz “bau-bereit” vorhanden.

  

  

  

  

2) Roadmap bis K501 LIVE (inkl. Google Cloud)

  

  

Ich setze die Prioritäten so, dass du schnell echte Beweise (Runs) bekommst und danach Cloud sauber anschließt (ohne Drift).

  

  

  

  

PHASE 0 — “Verlauf/Ist-Zustand fixieren”

  

  

Ziel: Alles, was wir jetzt haben, drift-sicher festhalten.

  

Steps

  

1. Freeze-Candidate Review (noch kein Freeze-Zwang, nur Checkliste)
2. Registry Tokens (family/version/profile) finalisieren oder “DRAFT: akzeptiert”
3. QH56-Embedding Window fixieren (oder “DRAFT: 32..59” belassen)

  

  

Warum: Ohne diese 2–3 Fixpunkte ist Cloud später unklar, was “canonical” ist.

  

  

  

  

PHASE 1 — Real Test Run (lokal) ✅ (nächster Hebel)

  

  

Ziel: Aus Draft wird “laufend”.

  

Steps

  

1. Go-Validator lokal ausführen (TV1–TV3)
2. Receipt-Output standardisieren (idealerweise JSON; aktuell ist’s struct-print)
3. Optional: ein 4. Testvector QH56-Embedding (wenn du willst)

  

  

Warum: Erst wenn lokal sauber läuft, lohnt Cloud-Build. Sonst debuggt man in der Cloud für nichts.

  

  

  

  

PHASE 2 — Repo-Struktur “Build-Ready”

  

  

Ziel: Ein minimales, reproduzierbares Projektlayout.

  

Minimal Layout

  

- cmd/qh256-validator/ (main)
- internal/qh/ (decoder, guard check)
- testdata/ (TV1–TV3 als .txt oder .json)
- README.md (1-Page verify)
- optional Makefile

  

  

Warum: Cloud Build/CI braucht klare Entry-Points. Repro kommt durch Struktur.

  

  

  

  

PHASE 3 — CI Compile (lokal → automatisch)

  

  

Ziel: Jeder Commit kompiliert + Tests laufen.

  

Steps

  

1. GitHub Actions (oder lokal “make test”)
2. go test (mindestens Testvector-Checks)
3. Build-Artefakt erzeugen (Binary)

  

  

Warum: Das ist dein “Proof-Loop”: jeder Build ist ein reproduzierbarer Schritt.

  

  

  

  

PHASE 4 — Containerisierung (Brücke zur Cloud)

  

  

Ziel: “Compile anywhere” durch Docker.

  

Steps

  

1. Dockerfile (multi-stage: build → minimal runtime)
2. docker run … <hex> muss wie lokal funktionieren
3. optional: --profile strict_v1|permissive

  

  

Warum: Cloud Run akzeptiert Container perfekt. Cloud Build kann Container deterministisch bauen.

  

  

  

  

PHASE 5 — Google Cloud Grundsetup (sicher & minimal)

  

  

Ziel: Cloud bereitmachen, ohne Overkill.

  

GCP Components (minimal)

  

- Artifact Registry (für Container Images)
- Cloud Build (baut Container)
- Cloud Run (führt Validator als Service aus)
- Cloud Storage (optional: Testdata/Receipts/Build-Logs)
- Secret Manager (falls später Tokens/Keys)
- IAM (minimal roles: build → push → run)

  

  

Warum: Das ist der “K501 live compute layer”, ohne direkt DB/Komplexität.

  

  

  

  

PHASE 6 — Cloud Compile / Deploy Pipeline

  

  

Ziel: “Push → Cloud baut → Cloud deployt”.

  

Steps

  

1. Cloud Build Trigger (GitHub Repo)
2. Build: docker build → push to Artifact Registry
3. Deploy: Cloud Run service updated
4. Endpoint: /validate (POST header hex) oder CLI-style request

  

  

Warum: Ab hier hast du “live compile + live validator” reproduzierbar.

  

  

  

  

PHASE 7 — K501 LIVE Integration (optional, wenn du willst)

  

  

Ziel: Website/Gateway kann Cloud-Validator nutzen.

  

Steps

  

1. Gateway call optional: /api/validate → Cloud Run
2. Receipts zurück ins Gateway (read-only Anzeige)
3. Optional Speicherung:  
    

- minimal: in DB k501_frames als FRAME_RECEIPT
- oder in GCS NDJSON append (je nach deiner Linie)

5.   
    

  

  

Warum: Das ist die echte “Live-Spur”: Besucher → Header → Receipt → append-only.

  

  

  

  

PHASE 8 — Cloud SQL / “echte” Datenhaltung (nur wenn nötig)

  

  

Ziel: Wenn du DB in Cloud willst (nicht zwingend).

  

Optionen

  

- Cloud SQL (MariaDB/MySQL) für Telemetrie/Receipts
- oder: weiter Shared-Host MariaDB + nur Validator in Cloud

  

  

Warum: DB macht Betrieb schwerer. Ich würde DB erst clouden, wenn du Stabilität + Nutzen siehst.

  

  

  

  

Prioritäten (mein Vorschlag, klar)

  

  

Jetzt als Nächstes

  

1. PHASE 1: Real Test Run lokal (TV1–TV3, Receipt Output sauber)
2. PHASE 2: Repo Build-Ready
3. PHASE 3: CI Compile
4. PHASE 4: Docker

  

  

Dann Google Cloud

5) PHASE 5–6: Cloud Build + Cloud Run

6) PHASE 7: Gateway Integration optional

7) PHASE 8: Cloud SQL optional

  

  

  

  

Was passiert als nächstes ganz konkret (der nächste Schritt)

  

  

Wenn du “go” sagst, ist der nächste harte, sinnvolle Schritt:

  

- Receipt-Output im Go-Validator als JSON (statt struct-print)
- und dazu ein minimaler Test: TV1–TV3 automatisch prüfen.

  

  

Damit hast du: lokal proof-fähig → CI proof-fähig → Cloud proof-fähig.

  

Wenn du willst, gebe ich dir als nächstes sofort (copy/paste) die JSON-Receipt Version des Go-Validators + Mini-Testdatei (go test).