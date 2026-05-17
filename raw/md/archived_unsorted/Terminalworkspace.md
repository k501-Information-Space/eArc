#!/bin/bash

# K501 Workspace Setup Script

# Debian 13 LXQT

# Autor: iinkognit0

# Ziel: Workspace, VSCodium, Git, Ledger-Verzeichnisse einrichten

set -e # Stop bei Fehler

echo "== K501 Workspace Setup Start =="

# 1. Update System

sudo apt update && sudo apt full-upgrade -y

sudo apt autoremove -y

# 2. Minimal Tools prüfen/installieren

sudo apt install -y git curl wget nano htop jq build-essential \

python3 python3-pip python3-venv ffmpeg

# 3. Workspace Verzeichnisse anlegen

mkdir -p ~/workspace/k501

mkdir -p ~/workspace/ledger

mkdir -p ~/workspace/archive

mkdir -p ~/workspace/temp

echo "Workspace Verzeichnisse erstellt."

# 4. Git initialisieren für Ledger / Projekte

cd ~/workspace/k501

git init

echo "Git Repository für K501 Workspace initialisiert."

# 5. VSCodium Installation (Debian)

# Repository hinzufügen

wget -qO - https://gitlab.com/paulcarroty/vscodium-deb-rpm-repo/raw/master/pub.gpg | gpg --dearmor | sudo tee /usr/share/keyrings/vscodium-archive-keyring.gpg >/dev/null

echo 'deb [ signed-by=/usr/share/keyrings/vscodium-archive-keyring.gpg ] https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs/ vscodium main' | sudo tee /etc/apt/sources.list.d/vscodium.list

sudo apt update

sudo apt install -y codium

echo "VSCodium installiert."

# 6. Git in VSCodium konfigurieren

git config --global user.name "iinkognit0"

git config --global user.email "example@example.com"

git config --global init.defaultBranch main

echo "Git global konfiguriert."

# 7. Nano als Standardeditor setzen

git config --global core.editor "nano"

echo "Nano als Git-Editor gesetzt."

# 8. Optional: Workspace-Projektstruktur initialisieren

cd ~/workspace/k501

mkdir -p src bin docs

echo "# K501 Workspace Projektstruktur" > README.md

git add .

git commit -m "Initial commit: Workspace Struktur erstellt"

echo "Workspace Projektstruktur und Initial Commit erstellt."

# 9. Übersicht

echo "== K501 Workspace Setup Fertig =="

echo "Pfad: ~/workspace/k501"

echo "Verzeichnisse: ledger, archive, temp, src, bin, docs"

echo "VSCodium + Git ready."