Keine alternativen Engines im K5-Kern.

---

## Export-Flow

1. Mensch fordert Export an:
   - `EXPORT`
2. System antwortet mit **Export-Plan**:
   - Quelle (ID)
   - Ziel-Format
   - Ziel-Pfad (Vorschlag)
3. Mensch bestätigt explizit:
   - `EXPORT RUN`
4. System führt **genau diesen Plan** aus
5. Ergebnis wird gemeldet (Pfad + Status)

Kein stilles Wiederholen.
Kein Auto-Overwrite.

---

## Sicherheitsregeln
- Kein Web-Fetch während Export
- Keine Code-Ausführung aus Inhalten
- Keine versteckten Metadaten
- Kein Tracking

Exportiert wird **nur**, was sichtbar ist.

---

## Integration mit Memory Dumps
- Jeder Export kann optional:
  - als **Export-Frame** referenziert werden
  - im Memory-Index erscheinen
- Keine Pflicht zur Protokollierung

---

## Fehlerverhalten
- Fehler → klare Meldung
- Kein Teil-Export
- Kein stiller Fallback

Stabilität > Geschwindigkeit.

---

## Verhältnis zu anderen Frames
- nutzt MetaHeader
- respektiert Frame Limit
- kann Blocks & Superblocks exportieren
- verändert **niemals** die Quelle

---

## Status
FINAL  
Produktionsreif  
Kernel-konform  

---

As I State Iinkognit0.