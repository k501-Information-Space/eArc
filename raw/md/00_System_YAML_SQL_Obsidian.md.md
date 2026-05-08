# Systemarchitektur · YAML · SQL · Obsidian

> Ordnungsstufe: 00  
> Kategorie: Architektur  
> Rolle: strukturell · grundlegend  
> Status: aktiv  
> Priorität: sehr hoch  

---

## Zweck dieses Dokuments

Dieses Dokument beschreibt die **Systemarchitektur des Projekts iInkognit0**
für den Umgang mit Wissen, Gedächtnis und Struktur.

Es legt fest:
- wie Informationen entstehen,
- wo sie gespeichert werden,
- wie Gedächtnis geschützt wird,
- und wie Modell-Memory bewusst entlastet wird.

Dieses Dokument ist die **Referenz für alle weiteren Arbeitsweisen**.

---

## Grundproblem

Gespräche sind flüchtig.  
Modell-Memory ist begrenzt.  
Langzeitprojekte benötigen Stabilität.

Ohne klare Trennung entsteht:
- Bedeutungsverlust
- Inkonsistenz
- Abhängigkeit vom Modell

Dieses System löst genau dieses Problem.

---

## Die vier Ebenen des Systems

### 1. Chat · Gespräch · Denken

**Rolle**
- Klärung
- Analyse
- Resonanz
- philosophisches Arbeiten

**Eigenschaften**
- flüchtig
- nicht dauerhaft
- bewusst löschbar

Der Chat ist **kein Gedächtnis**.

---

### 2. Obsidian Vault · Bedeutung · Volltext

**Rolle**
- primäres Gedächtnis
- Essays
- Manifestos
- Theorien
- Projektgrundlagen

**Eigenschaften**
- vollständig ausformuliert
- menschenlesbar
- dauerhaft

Der Vault ist das, **was das Projekt ist**.

---

### 3. YAML · Struktur · Zustand

**Rolle**
- aktueller Projektzustand
- Parameter
- Statistiken
- Konfigurationen

**Eigenschaften**
- leichtgewichtig
- maschinenlesbar
- diff-fähig

YAML speichert **keine Inhalte**, sondern **Zustände**.

---

### 4. SQL · Verlauf · Historie

**Rolle**
- Zeitreihen
- Entwicklungen
- Vergleichswerte

**Eigenschaften**
- langfristig stabil
- konsolidiert
- modellunabhängig

SQL speichert **keine Bedeutung**, nur Verlauf.

---

## Zentrale Design-Regel

> **MD kommt immer zuerst.  
> Keine Referenz ohne existierende Vault-Datei.**

Konsequenzen:
- YAML & SQL enthalten **nur Verweise**
- keine Volltexte außerhalb des Vaults
- kein Gedächtnisverlust möglich

---

## Referenz-Prinzip

Strukturierte Daten verweisen immer auf den Vault.

Beispiel:
- YAML enthält `vault_path`
- SQL enthält `vault_path`
- Der Vault enthält den Inhalt

Der Vault verweist **nicht zurück**.

---

## Gedächtnis-Schutz-Priorität

1. Obsidian Vault ist primäres Gedächtnis  
2. MD-Datei existiert oder wird zuerst erstellt  
3. Danach YAML aktualisieren  
4. Danach optional SQL ergänzen  
5. Chat darf vergessen werden  

---

## Memory-Schonung

Dieses System erlaubt bewusst:

- Löschen von Modell-Erinnerungen
- Ignorieren alter Chats
- Wechsel des Modells

Ohne Informationsverlust.

Das Gedächtnis lebt **außerhalb** des Modells.

---

## Verhältnis zur Vault-Struktur

Das System passt sich der bestehenden Struktur an:

- `00_Grundsaetze` → normativ
- `01_Fakten` → Realität & Daten
- `03_Essays` → Denken & Ausformulierung
- `05_Architektur` → System & Ordnung
- `06_Meta` → Übersichten & Indizes
- `06_Theorien` → Ontologie
- `07_Visionen` → Möglichkeitsräume

Es wird **nichts erzwungen**, nur genutzt.

---

## Zielzustand

- Kein kritisches Wissen im Modell
- Klare Trennung von Ebenen
- Langfristige Stabilität
- Ruhe im Arbeiten

Dieses System dient nicht der Effizienz,
sondern der **Kohärenz**.

---

## Status

Diese Architektur ist aktiv.

Sie darf erweitert,
aber nicht widersprüchlich unterlaufen werden.

Letzte Sicherung: YYYY-MM-DD