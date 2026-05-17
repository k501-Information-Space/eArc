# SQL-Historie · Initialisierung

> Kategorie: Fakten · SQL  
> Rolle: Historie · Struktur  
> Status: aktiv  
> Priorität: hoch  

---

## Zweck dieses Dokuments

Dieses Dokument beschreibt die **Initialisierung der SQL-Historie**
für das Projekt iInkognit0.

Es definiert:
- welche Tabellen existieren
- wofür sie gedacht sind
- wie sie mit MD & YAML zusammenhängen

Es enthält **keine Daten**.

---

## Grundsatz

> **SQL speichert Verlauf, nicht Bedeutung.**  
> **Bedeutung liegt im Vault.**

SQL-Einträge verweisen immer auf bestehende MD-Dateien.

---

## Tabellenübersicht

### 1. project_snapshots
Zeitliche Fixpunkte des Projektzustands.

**Verwendung:**
- Zustand über Zeit
- Phasenwechsel
- ruhige Dokumentation

---

### 2. platform_stats
Zeitreihen für Plattform-Kennzahlen.

**Verwendung:**
- Impressions
- Streams
- Follower
- andere messbare Größen

---

## Referenzen

- Architektur:
  → `05_Architektur/00_System_YAML_SQL_Obsidian.md`
- Projekt-Snapshot:
  → `01_Fakten/Snapshots/00_Projekt_Snapshot_Aktuell.md`
- Statistik-Snapshot (Spotify):
  → `01_Fakten/Statistiken/Spotify/00_Statistik_Snapshot_Aktuell.md`

---

## Status

Die SQL-Historie ist **initialisiert**, aber leer.

Erst bei einem **zweiten Statistik-Snapshot**
wird SQL aktiv genutzt.

Datum der Initialisierung: YYYY-MM-DD