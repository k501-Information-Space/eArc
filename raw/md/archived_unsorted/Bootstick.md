Alles klar. Ich erstelle dir einen kompletten Preseed- und Post-Installations-Plan für Debian 13 „Trixie“, LXQt, UEFI und direkt startklar für den T520 inklusive Kernel-Tuning, iGPU, Build-Tools, LLM-Stack und optionaler K501 Frame-Struktur.

# **1️⃣ Preseed-Datei (automatisierte Installation)**

Speichere als preseed.cfg:

### Localization

d-i debian-installer/locale string en_US.UTF-8

d-i console-setup/ask_detect boolean false

d-i keyboard-configuration/xkb-keymap select us

### Network

d-i netcfg/choose_interface select auto

d-i netcfg/get_hostname string t520

d-i netcfg/get_domain string local

### Mirror settings

d-i mirror/country string manual

d-i mirror/http/hostname string ftp.debian.org

d-i mirror/http/directory string /debian

d-i mirror/http/proxy string

### Clock and time zone

d-i clock-setup/utc boolean true

d-i time/zone string Europe/Berlin

d-i clock-setup/ntp boolean true

### Partitioning (UEFI + GPT, automated)

d-i partman-auto/method string lvm

d-i partman-auto-lvm/guided_size string max

d-i partman-auto/choose_recipe select atomic

d-i partman-lvm/device_remove_lvm boolean true

d-i partman-auto/confirm boolean true

d-i partman/confirm_write_new_label boolean true

d-i partman/confirm boolean true

### User setup

d-i passwd/root-password password root

d-i passwd/root-password-again password root

d-i passwd/user-fullname string user

d-i passwd/username string user

d-i passwd/user-password password user

d-i passwd/user-password-again password user

### Package selection

tasksel tasksel/first multiselect standard, desktop-lxqt

d-i pkgsel/include string build-essential cmake git curl wget python3 python3-pip chromium codium

d-i pkgsel/upgrade select safe-upgrade

d-i pkgsel/language-packs multiselect en

### Firmware / microcode

d-i hw-detect/load_firmware boolean true

d-i preseed/early_command string \

apt-install -y firmware-misc-nonfree intel-microcode

### Bootloader

d-i grub-installer/only_debian boolean true

d-i grub-installer/bootdev string /dev/sda

d-i finish-install/reboot_in_progress note

### Finish

d-i preseed/late_command string \

in-target systemctl enable NetworkManager

Hinweis: Partitionierung ist LVM-basiert, GPT + UEFI. EFI-Partition wird automatisch erstellt.

# **2️⃣ Bootstick vorbereiten (UEFI)**

1. Download Debian netinst ISO: debian-13.0.0-netinst-amd64.iso  
    
2. USB vorbereiten:  
    

sudo dd if=debian-13.0.0-netinst-amd64.iso of=/dev/sdX bs=4M status=progress conv=fsync

1. Preseed einbinden:  
    - Entpacke ISO, kopiere preseed.cfg in /preseed/ im ISO  
        
    - Passe Bootloader-Eintrag an:  
        

append file=/preseed/preseed.cfg auto=true priority=critical

1.   
      
    
2. ISO wieder schreiben auf USB → UEFI-bootfähig  
    

# **3️⃣ Post-Installation Skript (optimiert, direkt startklar)**

Speichere als postinstall.sh und führe nach Login aus:

#!/bin/bash

# =====================================================

# T520 – Post-Install Optimierung & K501 Ready

# =====================================================

echo "[*] System Update"

sudo apt update && sudo apt full-upgrade -y

echo "[*] Kernel & Performance Tuning"

sudo sysctl -w vm.swappiness=10

sudo sysctl -w vm.overcommit_memory=1

sudo sysctl -w vm.vfs_cache_pressure=50

sudo sysctl -w vm.dirty_ratio=10

sudo sysctl -w vm.dirty_background_ratio=5

echo "performance" | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

echo "[*] Firmware / iGPU Check"

sudo apt install -y firmware-misc-nonfree intel-microcode i965-va-driver

echo "[*] Python & LLM Stack"

sudo python3 -m pip install --upgrade pip

sudo python3 -m pip install nomic-embed-text qwen2.5 olama

echo "[*] Build Tools & Libraries"

sudo apt install -y build-essential cmake git libssl-dev libffi-dev

echo "[*] Browsers & Editor"

sudo apt install -y chromium codium

echo "[*] Create K501 Ledger Structure"

BASE_DIR="$HOME/K501GeminiNet"

LEDGER_DIR="$BASE_DIR/Node01/vault/ledger"

mkdir -p "$LEDGER_DIR"

if [ ! -f "$LEDGER_DIR/frames.ndjson" ]; then

echo '{"id": "genesis", "seq": 0, "prev": null, "ts": '$(date +%s)', "payload": "K501 Genesis", "vector": [0]}' > "$LEDGER_DIR/frames.ndjson"

fi

echo "[+] Postinstall Complete: System ready for K501"

# **4️⃣ Zusammenfassung Ablauf**

1. USB mit netinst + Preseed vorbereiten → UEFI-Boot  
    
2. Debian 13 LXQt installieren → komplett automatisiert  
    
3. Nach Login postinstall.sh ausführen → Kernel-Tuning, Firmware, LLMs, K501 Ledger  
    
4. System ist startklar → Offline, Privacy-fokussiert, K501-resonanzfähig  
    

Wenn du willst, kann ich noch eine erweiterte Version erstellen, die direkt Multipass-Pipeline, iGPU-Vektor-Setup und K501 Quick Start v2.0 schon automatisch ausführt, sobald der Postinstall-Skript fertig ist – dann ist der T520 sofort als Wissensprozessor einsatzbereit.

Willst du, dass ich diese Variante gleich mit erstelle?