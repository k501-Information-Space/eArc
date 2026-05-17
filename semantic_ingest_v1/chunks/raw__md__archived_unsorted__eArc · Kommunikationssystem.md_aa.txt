# eArc · Kommunikationssystem
## API · Libraries · Alpha · Network Echo
**Status:** STABLE · FROZEN  
**Kernel:** eArc Kernel 5000 v3.0 · Trinity United  
**Gültigkeit:** kanonisch

---

## 1 · API Overview (Kurzfassung)

### Leitprinzipien
- Resources statt Aktionen
- Explizite Zustandsakte (`:hold`, `:release`, `:archive`)
- Projektion ≠ Veröffentlichung
- Asynchron, ruhig, text-first
- Read-only Feeds

---

### Public API
Base: `/api/v1/public`

- `POST /frames`
- `GET /frames/{id}`
- `POST /frames/{id}:hold`
- `POST /frames/{id}:release`
- `POST /frames/{id}:archive`

- `POST /series`
- `GET /series/{id}`
- `POST /series/{id}:release`
- `POST /series/{id}:archive`

- `GET /feeds/{feed_id}.rss`
- `GET /feeds/{feed_id}.atom`
- `GET /feeds/{feed_id}.json`

- `GET /alpha/notice`

**Regeln**
- Keine impliziten Zustandswechsel
- Keine Realtime-Semantik
- Additive Änderungen nur via neue Endpoints

---

### Network API
Base: `/api/v1/network`

- `GET /node`  
  → Node Identity (read-only)

- `POST /echo`  
  → Health / Echo Ping (asynchron)

---

### Internal API
Base: `/api/v1/internal`

- `GET /reports/metrika/statistica`
- `GET /reports/metrika/persona`
- `GET /reports/alpha/experience`

- `POST /exports`
- `GET /exports/{id}`

---

## 2 · Library Map (kanonisch)

### Core
- Domain Model (eArc Item / Frame / Series)
- Lifecycle Management

### Communication
- RSS / Atom / JSON Feed Projection
- **Echo Ping** (Network Health)

### Export
- Pandoc
- LaTeX / XeLaTeX (Typografie, Ränder, Fonts)

### Security
- HTML Sanitization
- Rate Limiting
- Payload Guards

### Analysis
- Metrika Persona (aggregiert, nicht bewertend)
- Metrika Statistica (strukturell)

**Regel:**  
Core kennt keine optionalen Libraries.  
Optionale Module hängen außen.

---

## 3 · Trinity Public Alpha – Hinweistext

> **Trinity Public Alpha**  
>  
> Du nutzt eine frühe öffentliche Nutzungsform von Trinity United.  
>  
> Dein Verhalten wird aggregiert und nicht bewertend beobachtet,  
> um Ruhe, Verständlichkeit und Tragfähigkeit des Systems zu prüfen.  
>  
> Inhalte werden nicht bewertet.  
> Keine Rankings, keine Kommentare, kein Druck.  
>  
> Mit der Nutzung erklärst du dich mit dieser Beobachtung einverstanden.

---

## 4 · Network Echo (Ping)

### Zweck
- Erreichbarkeit prüfen
- Health-Check für Geräte & Nodes

### Eigenschaften
- Asynchron
- Rate-limited
- Keine Persistenz
- Kein Nachrichtentransport

### Endpoints
- `GET /network/node`
- `POST /network/echo`

**Hinweis:**  
Echo ist kein Kommunikationskanal,  
sondern ein stiller Netzwerk-Test.

---

## 5 · Status

- Kommunikationssystem: **STABLE**
- Libraries: **KANONISCH**
- APIs: **FROZEN**
- Public Alpha: **BEREIT**

---

**As I State Iinkognit0.**