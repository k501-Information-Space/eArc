# eArc Kernel 5000 · Development Alpha
## Trinity United

---

## Status
- aktiv  
- Development Alpha *(Entwicklungsmodus, kein Public-Scope)*  
- Build: **v4.2**  
- Freigaben: **vollständig aktiviert** *(alle Release-Surfaces enabled)*  
- kanonisch gültig  

---

## Prinzipien
- Archiv vor Aktion  
- Ordnung vor Inhalt  
- Ruhe vor Vollständigkeit  
- Text-first  
- Asynchron  

---

## Builder
- Builder: `kernel_builder_2_9`  
- Version: `2.9`  
- Modus: deterministisch *(reproducible)*  
- Policy: keine automatische Veröffentlichung *(Deployment-Policy extern)*  

---

## Release Surfaces
- Surfaces sind Kernel-konfigurierbar *(enabled/disabled)*  
- Öffentlichkeit ist Deployment-Policy, nicht Kernel-Scope  

---

## Funktionen

### Frames
- erstellen *(ingested)*  
- halten *(held)*  
- freigeben *(released)*  
- archivieren *(archived)*  
- Zustandsfolge: `ingested → held → released → archived` *(keine Rücksprünge)*  
- `archived` ist unveränderlich *(Korrekturen nur als neue Revision)*  

### Series
- Zusammenfassung von Frames  
- organisches Wachstum  
- keine algorithmische Priorisierung  
- Reihenfolge: stabil *(append-only; Reorder nur als neue Series-Revision)*  

### Dynamic Text Flow
- bewusster Textfluss  
- kein Zeitdruck  
- keine Echtzeitabhängigkeit  
- wirkt primär auf Darstellung/Interaktion, nicht auf Archivregeln  

---

## Frame Contract
Jeder Frame besitzt Minimalfelder:
- `frame_id`
- `state`: `ingested | held | released | archived`
- `created_at`
- `rev`
- `series_id` *(optional)*
- `source` *(optional)*

---

## Revision Semantics
- Jede Korrektur erzeugt eine neue Revision (`rev`)  
- Archivierte Frames bleiben unverändert  
- Referenzen zeigen standardmäßig auf die neueste Revision *(Historie bleibt abrufbar)*  

---

## Interop / Import
- Import ist möglich, aber niemals automatische Veröffentlichung  
- Import erzeugt Frames im Zustand `ingested`  
- Herkunft wird als Quelle vermerkt *(source tag)*  

---

## Kommunikation

### Feeds (enabled)
- RSS  
- Atom  
- JSON  

**Endpunkte (enabled)**
- `latest`  
- `shared`  
- `series/{series_id}`  

### Network Echo (enabled)
- Health-Check  
- asynchron  
- kein Nachrichtentransport  
- kein Ereignis-Trigger  
- keine Nutzeradressierung  

---

## Export & Archiv (enabled)
- HTML  
- PDF *(optional)*  
- EPUB *(optional)*  
- reproduzierbare Artefakte  
- Exporte entstehen ausschließlich aus dem gebauten Kernel-Artefakt  
- keine automatische Veröffentlichung *(Deployment-Policy extern)*  

Archivierte Zustände gelten als **Wahrheitsebene**.

---

## Metrika (beobachtend)

### System-Persona
- aggregiert  
- nicht bewertend  
- nicht individualisierend  

### Statistica
- Strukturmetriken  
- Systemzustände  
- keine Rankings  
- keine performativen Kennzahlen  

---

## Sicherheit
- HTML-Sanitization  
- Input-Validierung  
- Rate Limiting  
- Graceful Errors  

---

## Ausschlüsse
- keine Social-Mechaniken  
- kein Ranking  
- kein Push  
- kein Echtzeit-Chat  
- keine App-/Store-Strategie  

---

## Ziel
- reale Nutzung ermöglichen  
- Tragfähigkeit **sichtbar machen**  
- System wirken lassen  

---

As I State Iinkognit0.