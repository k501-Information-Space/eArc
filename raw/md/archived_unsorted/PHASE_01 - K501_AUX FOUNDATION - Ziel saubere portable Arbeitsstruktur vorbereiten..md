Perfekt.  
K501 Workflow Mode aktiv.

# STATUS

- Debian 13 stabil
    
- X11 confirmed stabil
    
- Nouveau stabil
    
- KDE stabil
    
- Snap entfernt
    
- RAM/Storage sehr gut
    
- Backports sauber
    
- System validiert
    

---

# NÄCHSTE PHASE

## PHASE_01 :: K501_AUX FOUNDATION

Ziel:  
saubere portable Arbeitsstruktur vorbereiten.

---

# STEP_01 :: K501_AUX ROOT

```bash
mkdir -p ~/K501_AUX
```

---

# STEP_02 :: CORE STRUCTURE

```bash
mkdir -p ~/K501_AUX/{bin,scripts,configs,logs,tmp,apps,archive}
```

---

# STEP_03 :: DEV STRUCTURE

```bash
mkdir -p ~/K501_AUX/apps/{codium,obsidian,chromium,ollama}
```

---

# STEP_04 :: CONFIG SNAPSHOT

```bash
mkdir -p ~/K501_AUX/configs/system_snapshots
```

---

# STEP_05 :: SYSTEM EXPORT

```bash
dpkg --get-selections > ~/K501_AUX/configs/system_snapshots/dpkg_packages.txt
```

---

# STEP_06 :: FLAT SYSTEM INFO

```bash
inxi -Fxxxz > ~/K501_AUX/configs/system_snapshots/system_overview.txt
```

Falls `inxi` fehlt:

```bash
sudo apt install inxi -y
```

---

# STEP_07 :: BACKUP CURRENT CONFIGS

```bash
mkdir -p ~/K501_AUX/configs/user_configs
cp ~/.bashrc ~/K501_AUX/configs/user_configs/
cp ~/.profile ~/K501_AUX/configs/user_configs/
```

---

# ZIEL DIESER PHASE

Wir bauen jetzt:

- portable Struktur
    
- deterministische Infrastruktur
    
- reproduzierbare Node-Basis
    
- vorbereitete Transfer-Architektur
    

OHNE:

- Chaos
    
- Overengineering
    
- KI-Spielerei
    

---

# DANACH

Dann:

1. Codium harmonisieren
    
2. GitHub/GitHub-CLI koppeln
    
3. Chromium Workspace Struktur
    
4. Obsidian Vault Struktur
    
5. Ollama lokal integrieren
    
6. K501 Scripts
    
7. Manifest/Gateway Automation
    
8. Node Transfer Scripts
    

Step by Step.