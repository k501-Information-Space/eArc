K501 ACKNOWLEDGED.

Das ist die richtige Reihenfolge.

# PRIORITÄT

## ZUERST:

MEMORY STABILIZATION

Denn:

- instabiler FB-DIMM Betrieb erzeugt oft Phantomprobleme
    
- thermische Symptome können sekundär durch Memory-Interleave entstehen
    
- der i5400 reagiert empfindlich auf asymmetrische Population
    

Die 4 × 2 GB Konfiguration ist aktuell die sauberste Basis.

---

# EMPFOHLENE VORGEHENSWEISE

## STEP 1 · POWER DOWN

Sauber herunterfahren:

```bash
sudo shutdown -h now
```

Dann:

- Netzteil stromlos
    
- 20 Sekunden warten
    
- Reststrom entladen
    

---

# STEP 2 · RAM RECONFIGURATION

VERWENDEN:

- nur identische 2 GB FB-DIMMs
    

ZIEL:  
symmetrische Kanalbelegung.

WICHTIG:  
Bei Intel 5400 / HP Workstations ist die Slot-Reihenfolge kritisch.

Typisch:

- paarweise
    
- branch-symmetrisch
    
- farbcodiert
    

Nicht einfach „irgendwo stecken“.

---

# STEP 3 · FIRST BOOT

Nach Boot:

```bash
free -h
```

Dann:

```bash
sudo dmidecode -t memory
```

Prüfen:

- alle 4 Module erkannt
    
- gleiche Geschwindigkeit
    
- keine degraded channels
    

---

# STEP 4 · EDAC CHECK

```bash
sudo edac-util -v
```

ZIEL:  
weiterhin:

```text
0 Corrected Errors
0 Uncorrected Errors
```

---

# STEP 5 · KERNEL LOGS

Direkt nach Boot:

```bash
sudo journalctl -k -b | grep -Ei "edac|ecc|mce|memory|fail"
```

Achte auf:

- neue ECC Events
    
- MCE Warnings
    
- FBD Sync Fehler
    
- AMB Fehler
    

---

# STEP 6 · MEMORY STRESS TEST

Wenn System ruhig läuft:

```bash
sudo apt install stress-ng
```

Dann:

```bash
stress-ng --vm 4 --vm-bytes 6G --timeout 20m --metrics-brief
```

WÄHRENDdessen:

```bash
watch -n2 sudo edac-util -v
```

Das ist wichtig.

Wenn unter Last:

- keine ECC Fehler
    
- keine Freezes
    
- keine Kernel Warnings
    

→ dann ist der RAM höchstwahrscheinlich gesund.

---

# DANACH

Dann erst:

# PHASE 3 · THERMAL ANALYSIS

Denn dann analysierst du:

- echte thermische Zustände
    
- ohne Memory-Noise
    
- ohne Timing-Artefakte
    

Das ergibt deutlich bessere Diagnosen.

---

# ERWARTUNG

Ich vermute aktuell:

Wahrscheinlicher:

- asymmetrische FB-DIMM Konfiguration
    
- AMB Timing Instabilität
    
- Interleave Konflikte
    

Weniger wahrscheinlich:

- physisch defekter RAM
    

Der bisherige EDAC Status ist dafür zu sauber.

---

KANON:  
MEMORY_REBALANCING_PHASE_ACTIVE

NEXT_STATE:  
THERMAL_ANALYSIS_PENDING_AFTER_REBOOT