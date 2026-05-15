Für K501_NODE_002 ist das eine sehr gute Entscheidung.

```text
4 × 2 GB
=
symmetrisch
=
thermisch ruhiger
=
stabiler Intel 5400 Betrieb
```

Gerade bei FB-DIMM-Systemen ist Stabilität oft wichtiger als maximale Kapazität.

Dein Stack wirkt übrigens erstaunlich modern für die Hardware:

- Debian 13
    
- Kernel 6.12
    
- Plasma 6
    
- Qt 6
    
- KDE Frameworks 6
    
- X11
    

Das ist technisch ziemlich beeindruckend für eine xw8600.

# K501_NODE_002 · STEP-BY-STEP OPTIMIZATION

---

# PHASE 1 · BASELINE SNAPSHOT

## 1. Systemzustand sichern

```bash
mkdir -p ~/K501_NODE_002/{logs,reports,snapshots}
```

---

## 2. Vollständigen Hardware-Report erzeugen

```bash
sudo lshw > ~/K501_NODE_002/reports/lshw_full.txt
```

Installieren falls nötig:

```bash
sudo apt install lshw
```

---

## 3. Kernel-Information sichern

```bash
uname -a > ~/K501_NODE_002/reports/kernel.txt
```

---

## 4. PCI-State sichern

```bash
lspci -nnvv > ~/K501_NODE_002/reports/pci_full.txt
```

---

## 5. Memory-State sichern

```bash
sudo dmidecode -t memory > ~/K501_NODE_002/reports/memory_layout.txt
```

---

# PHASE 2 · MEMORY STABILITY

## 6. EDAC Tools installieren

```bash
sudo apt install edac-utils rasdaemon
```

---

## 7. EDAC Kernelmodule prüfen

```bash
lsmod | grep i5400
```

Du solltest sehen:

```text
i5400_edac
i5k_amb
```

---

## 8. EDAC Fehler prüfen

```bash
sudo edac-util -v
```

---

## 9. Kernel Memory Events beobachten

```bash
journalctl -k | grep -Ei "edac|mce|memory|ecc"
```

---

## 10. Live Monitoring starten

```bash
sudo rasdaemon --foreground
```

Beenden:

```text
CTRL+C
```

---

# PHASE 3 · THERMAL ANALYSIS

FB-DIMM Systeme brauchen gute Kühlung.

---

## 11. Sensoren installieren

```bash
sudo apt install lm-sensors
```

---

## 12. Sensor Detection

```bash
sudo sensors-detect
```

Immer erstmal:

```text
YES
```

---

## 13. Temperaturen prüfen

```bash
watch -n 2 sensors
```

Achte auf:

- CPU Temps
    
- Mainboard Temps
    
- ggf. FB-DIMM Sensoren
    

---

# PHASE 4 · STORAGE HEALTH

---

## 14. SMART Tools installieren

```bash
sudo apt install smartmontools
```

---

## 15. Laufwerke anzeigen

```bash
lsblk
```

---

## 16. SMART Status prüfen

Beispiel:

```bash
sudo smartctl -a /dev/sda
```

Wichtige Werte:

- Reallocated_Sector_Ct
    
- Current_Pending_Sector
    
- Power_On_Hours
    
- UDMA_CRC_Error_Count
    

---

## 17. Dauerhaften SMART Dienst aktivieren

```bash
sudo systemctl enable smartd
sudo systemctl start smartd
```

---

# PHASE 5 · FILESYSTEM + I/O

---

## 18. Filesystem prüfen

```bash
df -h
```

---

## 19. Mount Optionen anzeigen

```bash
mount | grep "^/dev"
```

---

## 20. I/O Überblick

```bash
iostat -xz 2
```

Installieren:

```bash
sudo apt install sysstat
```

---

# PHASE 6 · CPU + SYSTEM LOAD

---

## 21. Modernes htop installieren

```bash
sudo apt install htop
```

---

## 22. CPU Frequenzen prüfen

```bash
watch -n 1 "grep MHz /proc/cpuinfo"
```

---

## 23. Governor prüfen

```bash
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

---

## 24. Governor auf Performance setzen

Temporär:

```bash
sudo cpupower frequency-set -g performance
```

Installieren:

```bash
sudo apt install linux-cpupower
```

---

# PHASE 7 · IRQ OPTIMIZATION

Dein GPU IRQ ist sehr dominant.

Das ist normal unter X11 + nouveau.

---

## 25. IRQ Balance installieren

```bash
sudo apt install irqbalance
```

---

## 26. Aktivieren

```bash
sudo systemctl enable irqbalance
sudo systemctl start irqbalance
```

---

## 27. Wirkung prüfen

```bash
watch -n 2 cat /proc/interrupts
```

---

# PHASE 8 · GPU ANALYSIS

---

## 28. Nouveau Status

```bash
dmesg | grep nouveau
```

---

## 29. OpenGL prüfen

```bash
glxinfo | grep OpenGL
```

Installieren:

```bash
sudo apt install mesa-utils
```

---

## 30. GPU Belastung beobachten

```bash
watch -n 1 cat /sys/kernel/debug/dri/0/pstate
```

Falls verfügbar.

---

# PHASE 9 · KDE / X11 OPTIMIZATION

Plasma 6 läuft überraschend gut auf alter Hardware,  
aber man kann einiges entschärfen.

---

## 31. Compositor reduzieren

In KDE:

```text
System Settings
→ Display & Monitor
→ Compositor
```

Empfehlung:

- Renderer:
    
    ```text
    OpenGL 2.0
    ```
    
- Blur:
    
    ```text
    OFF
    ```
    
- Animation Speed:
    
    ```text
    Fast
    ```
    
- Tearing prevention:
    
    ```text
    Automatic
    ```
    

---

## 32. Baloo begrenzen

Indexer Status:

```bash
balooctl status
```

Falls nötig:

```bash
balooctl suspend
```

oder komplett:

```bash
balooctl disable
```

---

# PHASE 10 · LONG-TERM STABILITY

---

## 33. Systemd Failed Units

```bash
systemctl --failed
```

---

## 34. Boot Analyse

```bash
systemd-analyze blame
```

---

## 35. Kritische Kernel Errors

```bash
journalctl -p 3 -xb
```

---

# PHASE 11 · OPTIONAL K501 NODE HARDENING

Für Archivbetrieb sinnvoll.

---

## 36. Automatische Logs persistent machen

```bash
sudo mkdir -p /var/log/journal
sudo systemctl restart systemd-journald
```

---

## 37. Append-only Archivstruktur

```bash
mkdir -p ~/K501_ARCHIVE/{frames,logs,snapshots,system}
```

---

## 38. Node Snapshot Script

```bash
nano ~/K501_ARCHIVE/system/node_snapshot.sh
```

Inhalt:

```bash
#!/bin/bash

OUT=~/K501_ARCHIVE/snapshots/$(date +%F_%H-%M-%S)

mkdir -p "$OUT"

uname -a > "$OUT/kernel.txt"
lspci > "$OUT/pci.txt"
lsblk > "$OUT/disks.txt"
free -h > "$OUT/memory.txt"
uptime > "$OUT/uptime.txt"
journalctl -p 3 -xb > "$OUT/errors.txt"
```

Dann:

```bash
chmod +x ~/K501_ARCHIVE/system/node_snapshot.sh
```

Ausführen:

```bash
~/K501_ARCHIVE/system/node_snapshot.sh
```

---

# K501 FINAL RECOMMENDATION

Für diese Hardware gilt:

```text
STABILITÄT > PERFORMANCE
```

Das System ist ideal für:

- Obsidian Vaults
    
- Archivierung
    
- lokale Wissenssysteme
    
- Terminal-Arbeit
    
- leichte Entwicklung
    
- Dokumentation
    
- strukturierte Forschung
    
- langlebige Linux-Nutzung
    

Und ehrlich:

eine Plasma-6 Workstation auf einem dual-Xeon-Harpertown-System  
im Jahr 2026 hat Stil.