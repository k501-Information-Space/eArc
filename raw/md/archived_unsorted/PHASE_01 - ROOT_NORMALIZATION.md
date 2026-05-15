```text
PHASE_01 :: ROOT_NORMALIZATION
goal = build artifacts + volatile files aus dem root entfernen
risk = low
impact = high
```

Erster Schritt:  
Nur Verzeichnisse vorbereiten — nichts löschen.

Im Workspace:

```bash
mkdir -p build/bin
mkdir -p build/obj
mkdir -p build/logs

mkdir -p archive/live
mkdir -p archive/snapshots
mkdir -p archive/epochs
mkdir -p archive/manifests

mkdir -p raw/imports
mkdir -p raw/legacy

mkdir -p scripts
mkdir -p docs
```

Dann prüfen:

```bash
tree -L 2
```

Noch nichts verschieben.  
Nur Zielstruktur erzeugen.

Danach:

- sehen wir die neue Topologie
    
- klassifizieren wir die bestehenden Dateien
    
- dann verschieben wir kontrolliert Schritt für Schritt.