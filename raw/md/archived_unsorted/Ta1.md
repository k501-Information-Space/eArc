# TAT1 · Tiny Always-Transmit RSS Transmitter
## Specs on Roadmap · Gespeichert (read-only)

**Status:** gespeichert · eingefroren  
**Kontext:** Frames Network · Kommunikation  
**Policy:** COMM OFF default · Transmit nur zum Tick  
**Zeitbasis:** UTC / Zulu  
**Charakter:** still · deterministisch · verlässlich

---

## Zweck
Periodische, **globale Analyse** als RSS/Atom veröffentlichen –  
**wie ein Uhrwerk**, ohne Push, ohne Reaktion, ohne Kompression.

---

## Betriebslogik
- **Transmit:** nur zu festen Zeitpunkten
- **Außerhalb der Fenster:** Kommunikation OFF
- **Receive:** erlaubt, **geschlossenes System** (Whitelist, Pull-only)

---

## Zeitplan (UTC)
- **12h:** 00:00Z, 12:00Z  
- **Wöchentlich:** Mo 00:00Z  
- **Monatlich:** 1. des Monats 00:00Z  
- **Jährlich:** 1. Jan 00:00Z

---

## Feed-Strategie
**Ein Feed** (`iarc-feed.xml`) mit Item-Kategorien:
- `global-analysis-12h`
- `global-analysis-weekly`
- `global-analysis-monthly`
- `global-analysis-yearly`
- optional `heartbeat`

---

## Item-Schema (deterministisch)
- **guid:** `sha256(node_id + period_type + period_start_utc)`
- **title:** `IARC Global Analysis · <period> · <timestamp>`
- **pubDate:** Tick-Zeit (UTC)
- **category:** period_type
- **description:** ruhiger Textbericht (nicht komprimiert)
- **content:encoded (optional):** ausführlicher Bericht

**Regel:** GUID-Items werden **nie geändert**, nur ergänzt (append-only).

---

## Receive (geschlossen)
- **Inputs:** RSS/Atom (Whitelist), optional SFTP Drop (Read-Only)
- **Allowlist:** `sources.allowlist.yaml`
- **Ablage:** `inbox/raw/<source>/<timestamp>.<json|xml>` (append-only)

---

## Analyse-Artefakte (Kontrakt)
- `out/global_12h.{md,json}`
- `out/global_weekly.{md,json}`
- `out/global_monthly.{md,json}`
- `out/global_yearly.{md,json}`
- optional `out/heartbeat.json`

---

## Transmit (TAT1)
- Liest **nur** Artefakte
- Baut RSS/Atom **nicht minifiziert**
- Schreibt `public/iarc-feed.xml`
- **Retention:** konfigurierbar (z. B. letzte N Items pro Kategorie)
- **Fallback:** Heartbeat, wenn Artefakt fehlt

---

## Skalierung
- Pull-basiert (Millionen Knoten möglich)
- HTTP Caching: ETag + Last-Modified
- Keine zentrale Abhängigkeit

---

## Sicherheit & Ethos
- Keine Autopublikation
- Keine Push-Mechaniken
- Keine Optimierungsschleifen
- Deterministisch, erklärbar, ruhig

---

## Roadmap-Notiz
- **Spec-Reife:** erreicht
- **Implementierung:** klein & kurz
- **Integration:** bewusst, später

**As I State Iinkognit0.**