# Templates · YAML & SQL · iInkognit0

> Ordnungsstufe: 01  
> Kategorie: Architektur  
> Rolle: Vorlage · operativ  
> Status: aktiv  
> Priorität: hoch  

---

## Zweck dieses Dokuments

Dieses Dokument enthält die **verbindlichen Templates**
für strukturierte Projektdaten im Projekt iInkognit0.

Die Templates dienen:
- der Faktenspeicherung
- der Zustandsabbildung
- der Historisierung

Sie enthalten **keine Bedeutung** und **keine Interpretation**.

---

## Grundregel

- Inhalte → Obsidian  
- Zustand → YAML  
- Verlauf → SQL  

YAML & SQL verweisen **immer** auf bestehende Vault-Dateien.

---

## YAML · Projekt-Snapshot (aktueller Zustand)

```yaml
project:
  name: iInkognit0
  snapshot_date: YYYY-MM-DD
  snapshot_time: HH:MM
  timezone: Europe/Berlin

status:
  phase: ruhig
  fokus: gedaechtnissicherung
  aktiv: true

references:
  grundsaetze:
    vault_path: "00_Grundsaetze/00_Projekt_Grundsaetze_iInkognit0.md"
  manifesto:
    vault_path: "00_Grundsaetze/01_Manifesto_Einheit_Bewusstsein_Frieden.md"
  theorie:
    vault_path: "06_Theorien/00_Theorie_Licht_Zeit_Raum_Singularitaet.md"
  essay_persona:
    vault_path: "03_Essays/00_Persona_Spuren_ohne_Absicht.md"

notes:
  - "Snapshot ohne Interpretation"