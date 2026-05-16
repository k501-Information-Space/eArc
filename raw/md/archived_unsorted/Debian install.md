Hier sind die relevanten technischen Informationen für eine saubere Installation von Debian 13 (LXQt) mit dem Graphical Expert Installer über Netinstall. Fokus: reproduzierbarer, stabiler Entwicklungs-Workspace für K501.

# **1. Installationsmedium**

Empfohlenes Image

- Debian  
    
- Version: Debian 13 Netinstall ISO  
    

Downloadbereich:

- https://www.debian.org/distrib/  
    

ISO-Typ:

|**Typ**|**Empfehlung**|
|---|---|
|netinst ISO|✔ empfohlen|
|---|---|
|DVD ISO|nicht nötig|
|---|---|
|live ISO|vermeiden|
|---|---|

Größe: ~650 MB

# **2. Boot-Modus**

Im BIOS/UEFI einstellen:

|**Einstellung**|**Wert**|
|---|---|
|Boot Mode|UEFI|
|---|---|
|Secure Boot|optional deaktivieren|
|---|---|
|SATA Mode|AHCI|
|---|---|
|Boot Priority|USB zuerst|
|---|---|

# **3. Installer starten**

Boot-Menü:

Graphical Expert Install

Nicht:

Graphical Install

Expert erlaubt Kontrolle über:

- Partitionierung  
    
- Paketauswahl  
    
- Netzwerk  
    
- Bootloader  
    

# **4. Sprache / Locale**

Empfohlen:

|**Parameter**|**Wert**|
|---|---|
|Language|English|
|---|---|
|Location|Germany|
|---|---|
|Locale|en_US.UTF-8 oder de_DE.UTF-8|
|---|---|

Für Development oft stabiler:

en_US.UTF-8

# **5. Netzwerk**

Optionen:

|**Typ**|**Empfehlung**|
|---|---|
|Ethernet|automatisch|
|---|---|
|WLAN|nur wenn nötig|
|---|---|

Hostname Vorschlag:

k501-node01

Domain:

local

# **6. Benutzerstruktur**

Root:

root password setzen

User:

user: iinkognit0

Optional:

sudo aktivieren

# **7. Partitionierung (UEFI)**

Empfohlene Struktur:

|**Partition**|**Größe**|**Typ**|
|---|---|---|
|EFI|512 MB|FAT32|
|---|---|---|
|root /|40-80 GB|ext4|
|---|---|---|
|home /home|Rest|ext4|
|---|---|---|
|swap|4-8 GB|swap|
|---|---|---|

Beispiel:

/boot/efi 512M

/ 60G

/home rest

swap 8G

Mountpoints im Installer manuell setzen.

# **8. Paketquellen**

Mirror:

deb.debian.org

Contrib + non-free:

aktivieren

Wichtig für:

- Firmware  
    
- Multimedia  
    
- Hardware  
    

# **9. Desktop Auswahl**

Im Tasksel-Dialog:

nur auswählen

LXQt

standard system utilities

SSH server (optional)

Nicht auswählen:

GNOME

KDE

Xfce

Grund:

LXQt ist leicht und stabil.

# **10. Bootloader**

Installer fragt:

Install GRUB?

Antwort:

YES

Target:

/dev/sda oder NVMe Hauptdisk

# **11. Erste Boot-Kontrolle**

Nach Installation prüfen:

Kernel

uname -a

Debian Version

cat /etc/debian_version

# **12. Erste Systemupdates**

sudo apt update

sudo apt full-upgrade -y

Optional Firmware:

sudo apt install firmware-linux firmware-misc-nonfree

# **13. Minimal Development Basis**

Empfohlene Pakete:

sudo apt install \

git \

curl \

wget \

build-essential \

python3 \

python3-pip \

python3-venv \

htop \

ripgrep \

jq \

ffmpeg

# **14. Workspace Basis (für K501)**

Strukturvorschlag:

~/workspace

~/workspace/k501

~/workspace/ledger

~/workspace/archive

# **15. VS Codeium Setup**

Editor:

Visual Studio Code

oder

VSCodium

Empfohlen:

VSCodium

# **16. Browser**

Für Gemini / ChatGPT / Docs:

Chromium

Installation:

sudo apt install chromium

# **17. Backup-Integration**

Nach Installation:

- Git Repository initialisieren  
    
- Ledger Verzeichnis versionieren  
    

Beispiel:

git init

git add .

git commit -m "K501 clean base install"

# **18. Zielzustand**

Nach Setup:

System:

Debian 13

LXQt

UEFI

Minimal packages

Workspace:

K501

Ledger

Archive

Git versioning

Wenn du möchtest, kann ich dir zusätzlich eine komplette Post-Install-Checkliste speziell für K501 Nodes erstellen, die:

- alle Dev-Tools  
    
- Python-Umgebung  
    
- Ollama CPU-Build  
    
- ffmpeg Media-Header  
    
- Git-Auto-Ledger  
    

in ca. 10 Minuten vollständig installiert.