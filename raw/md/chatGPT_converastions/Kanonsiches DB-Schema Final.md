# Kanonsiches DB-Schema Final

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## user · 2026-01-17T14:36:24.708000 UTC

TASK 1 — KANONISCHES DB-SCHEMA (FINAL)
Status: bestätigt · Analyse → Definition
Ziel: stabiler Archiv-Kernel, append-only, DB-first
Referenz: https://iinkognit0.de/

⸻

A) Grundannahmen (verbindlich)
	•	Append-only: keine Updates, keine Deletes.
	•	Immutability: jeder Datensatz ist historisch.
	•	ChatGPT-unabhängig: läuft als reine DB + Indizes.
	•	Public = Read-Only: explizite Freigabe erforderlich.

⸻

B) Entitäten (Minimal & final)

1) frames  (Kern)

Repräsentiert jede archivierte Einheit.

CREATE TABLE frames (
  frame_id        TEXT PRIMARY KEY,          -- z.B. FRM-20260117-0001
  created_utc     TEXT NOT NULL,              -- ISO-8601 UTC (Proof-Anker)
  frame_type      TEXT NOT NULL,              -- DECLARATION | LOG | DATA | MANIFEST | REFERENCE | ANALYSIS
  source          TEXT NOT NULL,              -- z.B. Iinkognit0
  payload_type    TEXT NOT NULL,              -- TEXT | JSON | BINARY | LINK
  payload         TEXT NOT NULL,              -- Inhalt oder Referenz
  content_hash    TEXT NOT NULL,              -- SHA-256 über payload
  byte_size       INTEGER NOT NULL,
  visibility      TEXT NOT NULL,              -- PRIVATE | PUBLIC
  integrity_note  TEXT                        -- optional: Prüfvermerk
);

Regeln
	•	frame_id nie wiederverwendet.
	•	content_hash Pflicht → Integrität prüfbar.
	•	visibility = PUBLIC nur nach expliziter Entscheidung.

⸻

2) indices  (Ordnung, kein Inhalt)

Logische Einordnung von Frames.

CREATE TABLE indices (
  index_id        TEXT PRIMARY KEY,            -- IDX-TIME-2026-01
  index_type      TEXT NOT NULL,               -- TIME | TYPE | SOURCE | TAG
  index_value     TEXT NOT NULL,               -- z.B. 2026-01 | DECLARATION
  description     TEXT
);


⸻

3) frame_index_map  (Relation)

Viele-zu-Viele zwischen Frames und Indizes.

CREATE TABLE frame_index_map (
  frame_id   TEXT NOT NULL,
  index_id   TEXT NOT NULL,
  PRIMARY KEY (frame_id, index_id),
  FOREIGN KEY (frame_id) REFERENCES frames(frame_id),
  FOREIGN KEY (index_id) REFERENCES indices(index_id)
);


⸻

4) public_registry  (Read-Only Gate)

Explizite Freigabe für Öffentlichkeit.

CREATE TABLE public_registry (
  public_id      TEXT PRIMARY KEY,            -- PUB-20260117-0001
  frame_id       TEXT NOT NULL,
  published_utc  TEXT NOT NULL,
  checksum       TEXT NOT NULL,
  FOREIGN KEY (frame_id) REFERENCES frames(frame_id)
);

Regeln
	•	Nur Frames mit visibility = PUBLIC.
	•	Public kennt nur public_id, nie interne IDs.

⸻

5) audit_log  (Meta, append-only)

Systemische Nachvollziehbarkeit.

CREATE TABLE audit_log (
  audit_id     TEXT PRIMARY KEY,
  event_utc    TEXT NOT NULL,
  event_type   TEXT NOT NULL,                  -- INGEST | INDEX | PUBLISH | VERIFY
  reference_id TEXT NOT NULL,                  -- frame_id oder public_id
  note         TEXT
);


⸻

C) Invarianten (nicht verhandelbar)
	•	Kein UPDATE / DELETE auf frames.
	•	Jeder Public-Eintrag → Hash-verifiziert.
	•	Public Registry separat vom Kern.
	•	Indizes enthalten keinen Payload.

⸻

D) Was dieses Schema ermöglicht (Fakt)
	•	Langzeit-Archivierung
	•	Zitierfähigkeit
	•	Integritätsprüfung
	•	Öffentlichen Lesezugriff ohne Risiko
	•	Betrieb ohne UI, ohne Cloud, ohne ChatGPT

⸻

TASK 1 abgeschlossen.
Bereit für TASK 2: Ingestion Rules definieren.

---

## assistant · 2026-01-17T14:36:28.637297 UTC

Bestätigt ✅ = **Fakt**.  
**TASK 1 — KANONISCHES DB-SCHEMA (FINAL)** ist **stabil, minimal, DB-first, append-only** und erfüllt exakt:

- **Kern**: `frames` (Inhalt + Hash + Sichtbarkeit)
- **Ordnung**: `indices` (nur Klassifikation, **kein** Payload)
- **Relation**: `frame_index_map` (N:M)
- **Public Gate**: `public_registry` (separat, read-only, zitierbar)
- **Nachvollziehbarkeit**: `audit_log` (append-only)

**Invarianten** (C) sind konsistent mit den Tabellen (B) und die **Capabilities** (D) folgen logisch aus Hash + getrenntem Public-Gate + Index-Trennung.

Bereit für **TASK 2: Ingestion Rules**.  
As I State Iinkognit0.

---

## system · 2026-01-17T14:36:28.998800 UTC



---

## assistant · 2026-01-17T14:36:29.050829 UTC



---

## user · 2026-01-17T14:36:43.878000 UTC

Bestätigt ✅ 

---

## system · 2026-01-17T14:36:44.202311 UTC



---

## assistant · 2026-01-17T14:36:44.269898 UTC

Bestätigt ✅ = **Fakt**.  
Status gehalten. Übergang zu **TASK 2** freigegeben.  
As I State Iinkognit0.

---

## user · 2026-01-17T14:37:11.322000 UTC

FRAMES NETWORK — RESET / VERSION UPDATE

MODE: CLEAN SESSION
STATE: ANALYSIS
PRIORITY: STABLE ARCHIVE
GOAL: DATABASE-FIRST (incognito.de)

RULES:
- no hallucinated links
- no external onboarding
- no promises without proof
- output only if verifiable
- archive before action

SCOPE:
- Frames Network vNext
- real database schema
- indexing, storage, retrieval
- public reference = read-only
- ChatGPT = interface, not product

FACTS:
- Frames Network currently exists as:
  - conceptual spec
  - archive logic
  - database schema
- NOT as:
  - public signup system
  - joinable platform
  - automated service

TASKS (ORDERED):
1. define canonical DB schema (final)
2. define ingestion rules
3. define read-only public access model
4. define what "using Frames Network" actually means
5. version stamp (vNext)

CONSTRAINT:
- everything must run without ChatGPT
- ChatGPT assists only as analyst

CONFIRM UNDERSTOOD AND WAIT FOR NEXT INSTRUCTION.

---

## assistant · 2026-01-17T14:37:12.643752 UTC

Bestätigt ✅ = **verstanden** (Analyse, clean session, DB-first, keine halluzinierten Links, keine Versprechen ohne Proof, ChatGPT nur Interface).

Ich **warte** auf die nächste Instruktion.  
As I State Iinkognit0.

---

## system · 2026-01-17T14:37:13.224763 UTC



---

## user · 2026-01-17T14:38:00.061000 UTC

{"frame_id":"FRM-20260117-0001","created_utc":"2026-01-17T00:00:00Z","frame_type":"DECLARATION","source":"Iinkognit0","payload_type":"TEXT","payload":"Frames Network – CLEAN SESSION gestartet. Ziel: DATABASE-FIRST. ChatGPT = Analyst, nicht Produkt. Archive before action.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0002","created_utc":"2026-01-17T00:00:00Z","frame_type":"REFERENCE","source":"Iinkognit0","payload_type":"TEXT","payload":"Kanonische Referenz: https://iinkognit0.de/ (immer). incognito.de ist ausgeschlossen (niemals).","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0003","created_utc":"2026-01-17T00:00:00Z","frame_type":"ANALYSIS","source":"Iinkognit0","payload_type":"TEXT","payload":"Ist-Zustand: Frames Network existiert als Konzept, Archivlogik und DB-Schema – nicht als Plattform, Signup-System oder Service.","content_hash

---

## system · 2026-01-17T14:38:00.585603 UTC



---

## assistant · 2026-01-17T14:38:00.686407 UTC

Analyse → **Validierung der Ingestion (TASK 2 – Vorprüfung)**

**Ergebnis:** ⛔ **nicht vollständig ingestierbar** → **Korrektur erforderlich**  
Kein Archiv-Commit erfolgt (archive before action).

---

## Frame-by-Frame-Prüfung

### FRM-20260117-0001 — DECLARATION
**Status:** ❌ *formal unvollständig*

**Abweichungen vom kanonischen DB-Schema:**
- `content_hash` = Platzhalter `<sha256>` → **nicht zulässig**
- `byte_size` = `0`, obwohl `payload` nicht leer ist → **inkonsistent**

**Erforderlich:**
- Reale SHA-256 über den exakten Payload
- Korrekte `byte_size` (UTF-8 Bytes des Payloads)

---

### FRM-20260117-0002 — REFERENCE
**Status:** ❌ *inhaltlich korrekt, formal unvollständig*

**Hinweis (wichtig, aber korrekt):**
- Referenz **https://iinkognit0.de/** ist kanonisch ✅  
- Ausschluss **incognito.de** explizit und korrekt dokumentiert ✅

**Formale Mängel (wie oben):**
- `content_hash` Platzhalter
- `byte_size` = `0` trotz Payload

---

### FRM-20260117-0003 — ANALYSIS
**Status:** ❌❌ *abgebrochen / invalid*

**Fehler:**
- JSON **nicht vollständig**
- Fehlende Felder:
  - `content_hash`
  - `byte_size`
  - `visibility`
- Kein valides Objekt → **harte Ablehnung**

---

## Kanonische Invarianten (erneut bestätigt)

- ❌ **Kein Frame ohne echten Hash**
- ❌ **Kein Frame mit falscher Byte-Angabe**
- ❌ **Kein teilweises JSON**
- ✅ **Keine stillschweigende Reparatur durch den Analysten**

---

## Nächster korrekter Schritt

Wenn du willst, gehe **so** weiter:

1. **Berechne echte SHA-256 Hashes** (Payload exakt, UTF-8)
2. **Setze korrekte `byte_size`**
3. **Reiche FRM-0001 bis FRM-0003 erneut ein**  
   – vollständig, je Frame ein valides JSON-Objekt

👉 Erst dann:
- Ingestion möglich  
- `audit_log`-Eintrag `INGEST` zulässig  
- TASK 2 („Ingestion Rules“) kann formalisiert werden

**Status bleibt:** ANALYSIS · CLEAN SESSION · ARCHIVE-FIRST  
Ich warte auf die korrigierten Frames oder die nächste Instruktion.

As I State Iinkognit0.

---

## user · 2026-01-17T14:39:08.138000 UTC

{"frame_id":"FRM-20260117-0001","created_utc":"2026-01-17T00:00:00Z","frame_type":"DECLARATION","source":"Iinkognit0","payload_type":"TEXT","payload":"Frames Network – CLEAN SESSION gestartet. Ziel: DATABASE-FIRST. ChatGPT = Analyst, nicht Produkt. Archive before action.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0002","created_utc":"2026-01-17T00:00:00Z","frame_type":"REFERENCE","source":"Iinkognit0","payload_type":"TEXT","payload":"Kanonische Referenz: https://iinkognit0.de/ (immer). incognito.de ist ausgeschlossen (niemals).","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0003","created_utc":"2026-01-17T00:00:00Z","frame_type":"ANALYSIS","source":"Iinkognit0","payload_type":"TEXT","payload":"Ist-Zustand: Frames Network existiert als Konzept, Archivlogik und DB-Schema – nicht als Plattform, Signup-System oder Service.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0004","created_utc":"2026-01-17T00:00:00Z","frame_type":"MANIFEST","source":"Iinkognit0","payload_type":"TEXT","payload":"TASK 1 abgeschlossen: Kanonisches DB-Schema (frames, indices, frame_index_map, public_registry, audit_log). Append-only, immutable, public read-only.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0005","created_utc":"2026-01-17T00:00:00Z","frame_type":"MANIFEST","source":"Iinkognit0","payload_type":"TEXT","payload":"TASK 2 abgeschlossen: Ingestion Rules final. Zeitanker Pflicht, Hash Pflicht, Whitelist Typen, Reject-Kriterien, Public Publish als separater Prozess.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0006","created_utc":"2026-01-17T00:00:00Z","frame_type":"MANIFEST","source":"Iinkognit0","payload_type":"TEXT","payload":"TASK 3 abgeschlossen: Read-only Public Access Model. Public Registry, Public Frame View, Hash-Verifikation, keine Writes, keine Accounts.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0007","created_utc":"2026-01-17T00:00:00Z","frame_type":"MANIFEST","source":"Iinkognit0","payload_type":"TEXT","payload":"TASK 4 abgeschlossen: Definition Nutzung. Frames Network nutzen = Frames erzeugen, archivieren, referenzieren, lesen. Keine Plattform, keine Teilnahme.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0008","created_utc":"2026-01-17T00:00:00Z","frame_type":"DECLARATION","source":"Iinkognit0","payload_type":"TEXT","payload":"TASK 5 abgeschlossen: Version Stamp vNext. Status: DEFINED, STABLE, ARCHIVE-FIRST. Empfehlung: Freeze.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0009","created_utc":"2026-01-17T00:00:00Z","frame_type":"DECLARATION","source":"Iinkognit0","payload_type":"TEXT","payload":"Canon 3x bestätigt. Freeze Freeze Freeze. Kernel Singularity kanonisch, unveränderlich. Execution blocked.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0010","created_utc":"2026-01-17T00:00:00Z","frame_type":"ANALYSIS","source":"Iinkognit0","payload_type":"TEXT","payload":"DB-Status in MB nicht messbar: keine reale DB-Instanz, kein Read/Write. Status: UNKNOWN / NOT MEASURED.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0011","created_utc":"2026-01-17T00:00:00Z","frame_type":"ANALYSIS","source":"Iinkognit0","payload_type":"TEXT","payload":"Erkenntnis: Theorie/Spec fertig, Praxis fehlt Träger. Nächster realer Schritt: Laptop/PC, Linux Debian 13, lokale DB (SQLite), 1 Insert, 1 Select.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0012","created_utc":"2026-01-17T00:00:00Z","frame_type":"REFERENCE","source":"Iinkognit0","payload_type":"TEXT","payload":"ChatGPT im Browser aktualisiert sich automatisch; bleibt Werkzeug/Analyst. Frames Network ist unabhängig.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

{"frame_id":"FRM-20260117-0013","created_utc":"2026-01-17T00:00:00Z","frame_type":"ANALYSIS","source":"Iinkognit0","payload_type":"TEXT","payload":"Aktuelle Frames können noch nicht ingestiert werden (kein Ingest-Pfad, Freeze aktiv). Empfehlung: Frames vorbereiten/parken.","content_hash":"<sha256>","byte_size":0,"visibility":"PRIVATE"}

---

## assistant · 2026-01-17T14:39:08.648902 UTC

Analyse → **Ingestion-Validierung (erneut)**

**Ergebnis:** ⛔ **ABGELEHNT – keine Ingestion möglich**  
**Grund:** Die formalen Mindestanforderungen werden **weiterhin verletzt**.

---

## Zentrale Ablehnungsgründe (für **alle** Frames FRM-0001 … FRM-0013)

1) **`content_hash` ist kein echter Hash**  
   - Platzhalter `"<sha256>"` ist **unzulässig**.  
   - Erforderlich: **reale SHA-256** über den **exakten Payload (UTF-8)**.

2) **`byte_size = 0` ist falsch**  
   - Payload ist nicht leer → **Byte-Größe muss > 0** sein.  
   - Erforderlich: korrekte Byte-Anzahl des Payloads.

3) **Kaskadeneffekt**  
   - Ohne echten Hash **keine Integrität**  
   - Ohne korrekte Byte-Größe **keine Verifikation**  
   → **kein INSERT**, **kein AUDIT_INGEST**, **kein Fortschritt**

---

## Klarstellung (kanonisch)

- ❌ **Keine stillschweigende Korrektur** durch den Analysten  
- ❌ **Keine Platzhalter** in archivfähigen Frames  
- ✅ **Archive before action** bleibt strikt

---

## Exakt erforderlicher nächster Schritt (minimal)

Für **jeden Frame**:

1. **SHA-256 berechnen** über den **Payload-Text** (exakt, UTF-8)
2. **`byte_size` korrekt setzen**
3. **Frame erneut einreichen** (vollständiges JSON)

> Tipp (nicht ausführen, nur Referenz):  
> `sha256sum payload.txt` → Hash übernehmen  
> `wc -c payload.txt` → Byte-Größe

---

**Status bleibt:** CLEAN SESSION · ANALYSIS · FREEZE aktiv  
Ich **warte** auf **korrekt berechnete Frames** oder eine **neue Instruktion**.

As I State Iinkognit0.

---

## user · 2026-01-17T14:40:31.829000 UTC

# Bytegröße (UTF-8 Bytes)
wc -c payload.txt

---

## assistant · 2026-01-17T14:40:39.965711 UTC

Ja — **`wc -c payload.txt`** gibt dir genau die **UTF-8-Bytegröße** (Anzahl Bytes) zurück.

Minimal korrektes Vorgehen (lokal, Linux/macOS):

```bash
# Payload exakt in Datei schreiben (ohne zusätzliche Zeichen!)
printf '%s' 'DEIN_PAYLOAD_TEXT_EXAKT_HIER' > payload.txt

# Bytegröße (UTF-8 Bytes)
wc -c payload.txt

# SHA-256 über exakt denselben Inhalt
sha256sum payload.txt    # Linux
# oder:
shasum -a 256 payload.txt  # macOS
```

Wichtig:
- **`printf '%s'`** statt `echo`, damit **kein extra Newline** reinkommt.
- Wenn du **absichtlich** ein Newline willst, musst du ihn bewusst hinzufügen – dann ändern sich **Hash & byte_size**.

Wenn du willst, kann ich dir auch ein **Copy/Paste-Minischema** geben, wie du *mehrere* Payloads sauber nacheinander hashst (ohne Fehler).

---

## system · 2026-01-17T14:40:40.295427 UTC



---

## user · 2026-01-17T14:41:41.771000 UTC

{
  "frame_id": "FRM-20260117-0001",
  "created_utc": "REPLACE_WITH_REAL_UTC_ISO8601",
  "frame_type": "DECLARATION",
  "source": "Iinkognit0",
  "payload_type": "TEXT",
  "payload": "Frames Network – CLEAN SESSION gestartet. Ziel: DATABASE-FIRST. ChatGPT = Analyst, nicht Produkt. Archive before action.",
  "content_hash": "REPLACE_WITH_REAL_SHA256",
  "byte_size": REPLACE_WITH_REAL_BYTE_COUNT,
  "visibility": "PRIVATE"
}

---

## system · 2026-01-17T14:41:42.282081 UTC



---

## assistant · 2026-01-17T14:41:42.389763 UTC

Analyse → **Formale Prüfung des Templates**

**Ergebnis:** ✅ **STRUKTURELL KORREKT** · ❌ **NOCH NICHT INGESTIERBAR**

---

## Was jetzt korrekt ist
- ✅ Vollständiges JSON-Objekt  
- ✅ Alle **Pflichtfelder** des kanonischen Schemas vorhanden  
- ✅ Feldtypen korrekt (`TEXT`, `DECLARATION`, `PRIVATE`)  
- ✅ Payload klar, eindeutig, stabil  
- ✅ Reihenfolge & Semantik kernel-konform  

Das ist **das richtige Ziel-Format**. 👍

---

## Was noch fehlt (hart, aber minimal)

Die folgenden drei Felder sind **Platzhalter** und blockieren Ingestion:

1) **`created_utc`**
- Muss eine **reale ISO-8601 UTC-Zeit** sein  
  Beispiel:
  ```
  2026-01-17T00:00:00Z
  ```

2) **`content_hash`**
- Muss die **echte SHA-256** des **exakten Payloads (UTF-8)** sein  
- Kein Platzhalter, kein Kurzformat

3) **`byte_size`**
- Muss die **exakte Byteanzahl** des Payloads sein  
- Ergebnis von `wc -c payload.txt`

---

## Kanonische Regel (erneut, endgültig)
> **Ein Frame existiert erst, wenn Hash + Bytegröße real sind.**  
> Alles davor ist **Vorbereitung**, kein Archiv.

---

## Nächster erlaubter Schritt

Ersetze **alle drei** Platzhalter mit **realen Werten**  
und sende **genau dieses JSON** erneut.

👉 Dann erfolgt:
- ✅ `INGEST` zulässig  
- ✅ `audit_log` kann geschrieben werden  
- ✅ FRAME **FRM-20260117-0001** wird **kanonisch existent**

Ich warte auf die **konkretisierten Werte**.  
As I State Iinkognit0.

---

## user · 2026-01-17T14:42:37.197000 UTC

Unix Epoch	1768660934
Time (UTC)	Sat Jan 17 14:42:14 2026 UTC
Time (Europe/Oslo)	Sat Jan 17 15:42:14 2026 CET

---

## assistant · 2026-01-17T14:42:40.234194 UTC

Bestätigt ✅ **Zeitanker gültig**.

**Verwendbarer Wert für das Frame-Feld:**
```json
"created_utc": "2026-01-17T14:42:14Z"
```

Zuordnung:
- Unix Epoch: **1768660934** → konsistent  
- UTC maßgeblich (Europe/Oslo nur Ableitung)

**Status jetzt:**
- Zeitanker ✅ **erledigt**
- Offen bleiben **nur noch**:
  - `content_hash` (echte SHA-256 über Payload)
  - `byte_size` (echte UTF-8-Bytegröße)

Sobald diese beiden Werte gesetzt sind und das JSON erneut gesendet wird:
- ✅ **INGEST erlaubt**
- ✅ `audit_log: INGEST`
- ✅ FRM-20260117-0001 **kanonisch existent**

Ich warte auf das vervollständigte Frame.  
As I State Iinkognit0.

---

