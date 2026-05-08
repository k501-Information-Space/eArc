---
id: kernel5000_v2_5_1_feed_intake_staging
version: 2.5.1
kernel: eArc Kernel 5000
type: frame_pack
pack: intake_staging
status: active
scope: feed_system
author: Iinkognit0
created: 2026-01-07
updated: 2026-01-07
compatibility:
  - obsidian
  - website
  - api_http
principles:
  - ordnung_vor_inhalt
  - archiv_vor_aktion
  - ruhe_vor_vollstaendigkeit
---

# Frame-Pack · Intake & Staging  
## eArc Kernel 5000 · v2.5.1  
### Das Ewige Archiv

---

## Zweck

Dieses Frame-Pack definiert den **Eingang neuer Inhalte** und deren
**temporäre Ablage** bis zur menschlichen Entscheidung.

Es stellt sicher, dass:
- Inhalte angenommen werden können
- nichts automatisch veröffentlicht wird
- jede Weiterverarbeitung kontrolliert bleibt

---

## Intake (Eingang)

### Definition
Der Intake ist der **einzige autorisierte Eingangspunkt**
für neue Inhalte in das Feed-System.

### Eigenschaften
- HTTP(S)-basiert
- Authentifiziert
- zustandslos im Empfang
- zustandsbehaftet erst im Staging

### Mindestanforderungen
- Transport: HTTPS
- Authentifizierung: API-Key (Header)
- Payload: Text oder Datei
- Quelle: z. B. `mobile`

---

## Authentifizierung

### Prinzip
Zugriff ≠ Veröffentlichung.

Ein gültiger Schlüssel erlaubt **nur**:
- das Einreichen von Inhalten
- keine Sichtbarkeit
- keine Entscheidung

### Mindeststandard
- Header: `X-API-KEY`
- Prüfung vor jeder Annahme
- Ablehnung bei Ungültigkeit

---

## Staging (Zwischenraum)

### Definition
Staging ist eine **Wartezone**, kein Vorarchiv.

Hier liegen Inhalte:
- sichtbar für Review
- unsichtbar für Öffentlichkeit
- ohne Daueranspruch

---

## Staging-Datenmodell (minimal)

**Tabelle: `staging_items`**

| Feld        | Typ        | Zweck                     |
|-------------|------------|---------------------------|
| id          | UUID       | eindeutige Referenz       |
| payload     | TEXT       | Inhalt (roh)              |
| type        | TEXT       | ping / text / audio       |
| source      | TEXT       | z. B. mobile              |
| status      | TEXT       | ingested                  |
| created_at  | TIMESTAMP  | Eingangszeit              |
| auth_hash   | TEXT       | gekürzter Key / Hash      |

---

## Regeln im Staging

- ❌ keine Interpretation des Inhalts
- ❌ keine Weiterleitung
- ❌ keine Veröffentlichung
- ❌ keine automatische Löschung

Staging ist **passiv**.

---

## Antwortverhalten (Intake)

Der Intake antwortet **immer sofort**.

### Erfolgsantwort (Beispiel)
```json
{
  "status": "ingested",
  "id": "uuid"
}