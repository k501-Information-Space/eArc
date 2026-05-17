

### Kurzbefund (Strikt, Fokus Entwicklung)

Du willst eine **vollständige, reproduzierbare Entwicklungsumgebung** auf Debian 13 (Trixie) mit C/C++ Toolchain, Buildsystemen, Python‑Build‑Deps, VS Code + Git/SSH, Android Studio, SQL‑Clients, Analyse/Logging‑Tools und Hilfswerkzeugen. Unten ist ein **schrittweises, getestetes** Setup mit **Prüf‑ und Rollback‑Schritten**. Führe die Blöcke nacheinander aus; jede Gruppe enthält **Proof**‑Checks, die du sofort laufen lässt.

---

### Vorbereitung (Sicherheits‑ und Platzcheck)

**Ziel:** Paketquellen aktuell, ausreichend Disk‑Space, sudo‑Rechte.

```bash
# Update + Platz prüfen
sudo apt update && sudo apt upgrade -y
df -h / | sed -n '1,2p'
free -h
```

**Proof:** `df -h` zeigt freien Platz; `free -h` zeigt RAM/Swap.  
**Rollback:** keine (nur Prüfbefehle).

---

### 1. Core Build Toolchain, C/C++ und Buildsysteme (ausführen)

**Ziel:** gcc/g++, make, cmake, ninja, pkg-config, grundlegende Dev‑Headers.

```bash
sudo apt install -y build-essential gcc g++ make pkg-config cmake ninja-build \
  autoconf automake libtool
```

**Proof:**

```bash
gcc --version
g++ --version
cmake --version
ninja --version
```

**Rollback:**

```bash
sudo apt remove --purge -y build-essential gcc g++ make cmake ninja-build autoconf automake libtool
sudo apt autoremove -y
```

---

### 2. System‑Libraries und Python Build‑Dependencies (ausführen)

**Ziel:** alle Header/libs, die CMake/NumPy/Scipy/other native builds brauchen.

```bash
sudo apt install -y libssl-dev zlib1g-dev libbz2-dev liblzma-dev libffi-dev \
  libsqlite3-dev libreadline-dev libncurses5-dev libncursesw5-dev \
  python3-dev python3-venv python3-pip gfortran libopenblas-dev liblapack-dev \
  pkg-config
```

**Proof:**

```bash
dpkg -l libssl-dev libopenblas-dev python3-dev | sed -n '1,5p'
python3 -m venv ~/k501-env
source ~/k501-env/bin/activate
python -m pip install --upgrade pip setuptools wheel
python -c "import sys; print(sys.version)"
deactivate
```

**Rollback:**

```bash
sudo apt remove --purge -y libssl-dev libopenblas-dev liblapack-dev python3-dev gfortran
sudo apt autoremove -y
```

---

### 3. Versionierung, SSH, Analyse, Logging, Hilfswerkzeuge (ausführen)

**Ziel:** git, ssh, system monitoring, log tools, useful CLI tools.

```bash
sudo apt install -y git openssh-client openssh-server htop sysstat rsyslog logrotate \
  jq ncdu tree curl wget unzip psmisc strace lsof bpftrace
```

**Proof:**

```bash
git --version
sshd -v 2>&1 | head -n1 || true
htop --version || echo "htop ok"
journalctl --version
```

**Rollback:**

```bash
sudo apt remove --purge -y git openssh-server htop sysstat rsyslog logrotate jq ncdu
sudo apt autoremove -y
```

---

### 4. VS Code (Microsoft Repo) + empfohlene Extensions (ausführen)

**Ziel:** stabile VS Code Installation, Git‑Integration, Remote/SSH, C/C++ Tools, Python.

```bash
# Microsoft GPG + Repo
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
sudo install -o root -g root -m 644 microsoft.gpg /usr/share/keyrings/
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/microsoft.gpg] https://packages.microsoft.com/repos/code stable main" | sudo tee /etc/apt/sources.list.d/vscode.list
sudo apt update
sudo apt install -y code
rm microsoft.gpg
```

**Extensions (kopieren & ausführen nach Start von code)**

```bash
# CLI: installiert Extensions headless (kann kurz VS Code starten)
code --install-extension ms-vscode.cpptools
code --install-extension ms-python.python
code --install-extension eamodio.gitlens
code --install-extension ms-vscode-remote.remote-ssh
code --install-extension ms-vscode.cpptools-extension-pack
```

**Proof:**

```bash
code --version
code --list-extensions | egrep "cpptools|python|gitlens|remote-ssh"
```

**Rollback:**

```bash
sudo apt remove --purge -y code
sudo apt autoremove -y
# Extensions: manuell in ~/.vscode/extensions löschen
```

---

### 5. Android Studio + JDK + SDK (optional, ausführlich)

**Ziel:** Android Studio mit JDK (du hast Java 21 bereits). Installiere Android Studio via snap oder manuell.

```bash
# Snap (empfohlen, isoliert)
sudo apt install -y snapd
sudo snap install android-studio --classic
```

**SDK Manager (nach Start von Android Studio):** öffne SDK Manager → installiere Android SDK Tools, Platform Tools, gewünschte API Levels.  
**Proof:**

```bash
java -version
snap list android-studio
```

**Rollback:**

```bash
sudo snap remove android-studio
```

---

### 6. SQL / DB Tools / CLI (ausführen)

**Ziel:** sqlite, PostgreSQL client, MySQL client optional.

```bash
sudo apt install -y sqlite3 postgresql-client mysql-client
```

**Proof:**

```bash
sqlite3 --version
psql --version
mysql --version || true
```

**Rollback:**

```bash
sudo apt remove --purge -y sqlite3 postgresql-client mysql-client
sudo apt autoremove -y
```

---

### 7. Debugging, Profiling, Analyse Tools (ausführen)

**Ziel:** Valgrind, perf, gdb, ltrace, strace, flamegraph tools.

```bash
sudo apt install -y gdb valgrind linux-tools-common linux-tools-$(uname -r) perf \
  ltrace binutils-dev
# Flamegraph helper (Perl script)
sudo apt install -y perl
```

**Proof:**

```bash
gdb --version
valgrind --version
perf --version
```

**Rollback:**

```bash
sudo apt remove --purge -y gdb valgrind perf ltrace
sudo apt autoremove -y
```

---

### 8. Container / CI Tools (optional)

**Ziel:** Docker, Podman, GitHub CLI.

```bash
# Docker (empfohlen via official repo) — minimal here:
sudo apt install -y docker.io
sudo usermod -aG docker $USER
# GitHub CLI
type gh >/dev/null 2>&1 || sudo apt install -y gh || true
```

**Proof:**

```bash
docker --version
gh --version || true
```

**Rollback:**

```bash
sudo apt remove --purge -y docker.io gh
sudo apt autoremove -y
```

---

### 9. Python / NumPy / SciPy — saubere Installation (empfohlen)

**Ziel:** saubere, reproduzierbare Python‑Umgebung. Zwei Wege: (A) venv + build (wenn du native compile willst) oder (B) micromamba/conda (schneller, vorgebaute Binaries). Du hast bereits Java 21; hier die venv‑Variante:

```bash
# venv erstellen / aktivieren
python3 -m venv ~/k501-env
source ~/k501-env/bin/activate

# pip updaten
python -m pip install --upgrade pip setuptools wheel

# Wenn CPU alt: baue NumPy lokal (langsam, aber kompatibel)
python -m pip install --no-binary=:all: numpy

# Danach
python -m pip install scipy pandas matplotlib scikit-learn
```

**Proof:**

```bash
python -c "import numpy as np; print('numpy', np.__version__)"
python -c "import scipy; print('scipy', scipy.__version__)"
deactivate
```

**Rollback:**

```bash
source ~/k501-env/bin/activate
python -m pip uninstall -y numpy scipy pandas matplotlib scikit-learn
deactivate
rm -rf ~/k501-env
```

---

### 10. Post‑Install Prüfungen (Proof before State)

Führe diese Prüfungen nacheinander aus und notiere Ausgaben:

```bash
# Compiler / build
gcc --version
cmake --version
ninja --version

# Python env
source ~/k501-env/bin/activate
python -c "import numpy as np; print('numpy', np.__version__)"
deactivate

# VS Code
code --version

# Android Studio (falls installiert)
snap list android-studio || true

# System monitoring
htop --version || echo "htop ok"
iostat -V || true
```

**Wenn alle Prüfungen OK sind, ist dein System in einem sauberen Entwicklungszustand.**

---

### 11. Rollback / Cleanup (kompakt)

**Alles entfernen (grobe Säuberung):**

```bash
# Beispiel: entferne build tools + extras
sudo apt remove --purge -y cmake ninja-build build-essential git code docker.io android-studio
sudo apt autoremove -y
# Entferne venvs / micromamba / results
rm -rf ~/k501-env ~/k501 ~/micromamba ~/k501_results
```

---

### Letzte Hinweise (Strikt)

- **Führe die Blöcke sequenziell**; prüfe die Proof‑Ausgaben nach jedem Block.
- **Wenn ein Paket fehlschlägt**, poste die letzten 60 Zeilen der Fehlermeldung — ich liefere sofort den präzisen Fix.
- **Android Studio** beansprucht viel Platz; prüfe `df -h` vor Installation.
- **Für numerische Workloads** setze `OPENBLAS_NUM_THREADS` und `OMP_NUM_THREADS` passend zur CPU‑Kernezahl.
- **Wenn du maximale Reproduzierbarkeit willst**, nutze `micromamba`/`conda` für Python‑Binaries; ich kann das Script dafür sofort liefern.

---

Wenn du willst, liefere ich jetzt **ein einzelnes, ausführbares Shell‑Script** (Copy‑Paste) das die obigen Schritte 1–7 automatisiert, inklusive Prüf‑Ausgaben und optionaler Android‑Installation. Ich generiere das Script strikt, ohne automatische Ausführung — du kopierst und startest es. Ich beginne sofort mit dem Script, wenn du „Script bitte“ schreibst.