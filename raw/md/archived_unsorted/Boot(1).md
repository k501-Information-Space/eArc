Alles klar. Wir gehen Schritt für Schritt vor, damit du einen fertigen automatisierten Bootstick für Debian 13 LXQt auf dem T520 bekommst, inkl. Preseed und Postinstall-Skript. Das Ziel: ein sauberes, schlankes System, direkt startklar, alle Libraries, Tools, Firmware, iGPU-Tuning, ohne manuelles Nacharbeiten.

## **1. Debian 13 Netinstall ISO vorbereiten**

1. Lade die Debian 13 Netinstall ISO für LXQt:  
      
    [Debian 13 Trixie Netinstall LXQt  
    ](https://www.debian.org/releases/trixie/debian-installer/)
2. Prüfe SHA256 der ISO → Integrität sichern.  
    
3. Erstelle den Bootstick (UEFI-kompatibel) z.B. mit dd oder Rufus / BalenaEtcher:  
    

sudo dd if=debian-13-lxqt-netinst.iso of=/dev/sdX bs=4M status=progress oflag=sync

Hinweis: /dev/sdX ersetzen durch den USB-Stick. Alle Daten werden gelöscht.

## **2. Preseed Datei vorbereiten**

Erstelle z. B. preseed.cfg auf dem USB-Stick oder per Netzwerk:

# Locale & Keyboard

d-i debian-installer/locale string en_US.UTF-8

d-i console-setup/ask_detect boolean false

d-i keyboard-configuration/layoutcode string us

# Network

d-i netcfg/choose_interface select auto

d-i netcfg/get_hostname string debian-t520

d-i netcfg/get_domain string local

# Timezone

d-i time/zone string Europe/Berlin

# Disk Partitioning UEFI / GPT

d-i partman-auto/disk string /dev/sda

d-i partman-auto/method string regular

d-i partman-auto/choose_recipe select atomic

d-i partman-auto/confirm boolean true

d-i partman/confirm_write_new_label boolean true

d-i partman/confirm boolean true

# User accounts

d-i passwd/root-password password rootpass

d-i passwd/root-password-again password rootpass

d-i passwd/user-fullname string iinkognit0

d-i passwd/username string iinkognit0

d-i passwd/user-password password userpass

d-i passwd/user-password-again password userpass

# Install LXQt Desktop

tasksel tasksel/first multiselect standard, desktop, laptop, lxqt

# Package selection

d-i pkgsel/include string sudo build-essential cmake git python3 python3-pip python3-venv \

ffmpeg vlc chromium codium htop btop net-tools wireless-tools iw nmap tcpdump traceroute iproute2 \

firmware-misc-nonfree intel-microcode i965-va-driver

# Bootloader

d-i grub-installer/only_debian boolean true

d-i grub-installer/with_other_os boolean true

# Finish

d-i finish-install/reboot_in_progress note

Damit wird UEFI + GPT automatisch partitioniert, LXQt installiert und alle Basis-Tools installiert.

## **3. Postinstall Script**

Leg auf dem USB-Stick postinstall.sh ab und markiere ausführbar (chmod +x postinstall.sh):

#!/bin/bash

# Postinstall Script für Debian 13 LXQt T520

set -e

echo "[*] System Update & Upgrade"

sudo apt update && sudo apt full-upgrade -y

echo "[*] Kernel & Performance Tuning"

sudo sysctl -w vm.swappiness=10

sudo sysctl -w vm.overcommit_memory=1

sudo sysctl -w vm.vfs_cache_pressure=50

sudo sysctl -w vm.dirty_ratio=10

sudo sysctl -w vm.dirty_background_ratio=5

echo "performance" | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

echo "[*] Firmware & iGPU"

sudo apt install -y firmware-misc-nonfree intel-microcode i965-va-driver

echo "[*] Python & Pip"

sudo python3 -m pip install --upgrade pip

echo "[*] Zusätzliche Tools (Monitoring, Netzwerk, Multimedia)"

sudo apt install -y htop btop net-tools wireless-tools iw nmap tcpdump traceroute iproute2 ffmpeg vlc

echo "[*] System fertig: LXQt + Tools + Firmware + iGPU optimiert"

Damit wird alles automatisch aktualisiert, getunt und vorbereitet.

## **4. Bootstick Einsatz**

1. USB einstecken → BIOS auf UEFI Boot stellen  
    
2. Vom USB starten → Debian Netinstall  
    
3. Preseed Datei automatisch nutzen oder manuell referenzieren  
    
4. Nach Installation postinstall.sh ausführen  
    

Ergebnis: frisches, stabiles LXQt-System, alle Libraries, Tools, Firmware, iGPU optimiert, bereit für Workspace-Setup.

## **5. Nächster Schritt: K501 Workspace**

- Backup bestehender K501-Ordner  
    
- Kopieren in /K501GeminiNet  
    
- Postinstall für Multipass + Quick Start v2.0 starten  
    

Dann ist der T520 sofort als deterministischer Wissensprozessor einsatzbereit.

Wenn du willst, kann ich jetzt eine fertige Schritt-für-Schritt Anleitung inkl. automatischem USB-Buildskript erstellen, die Preseed + Postinstall zusammenpackt, sodass du nur noch den USB erzeugst, einsteckst und alles automatisch läuft.

Willst du, dass ich das direkt erstelle?