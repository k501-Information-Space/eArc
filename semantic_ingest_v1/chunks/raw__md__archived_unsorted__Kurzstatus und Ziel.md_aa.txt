### Kurzstatus und Ziel

Du hast bereits viele Basis‑Pakete installiert, Android Studio per Snap läuft, VS Code ist installiert. Zwei offene Punkte aus deinen letzten Ausgaben:

- `sshd` war nicht gefunden → **openssh‑server** fehlt/ist nicht installiert oder nicht im PATH.
- `mysql-client` hat keinen Kandidaten → Debian liefert hier **mariadb-client-compat** als Ersatz.
- `numpy` ist in der aktiven Umgebung noch **nicht** installiert.

Ich gebe dir jetzt **strikte, reproduzierbare** Befehle (kopierbar), Prüf‑ und Rollback‑Schritte, damit du: SSH laufen hast, SQL‑Client installiert ist, und Python‑Numerik (NumPy/SciPy/Pandas/Matplotlib) sauber verfügbar ist.

---

### 1 — SSH (openssh‑server) installieren und prüfen

```bash
# Installieren
sudo apt update
sudo apt install -y openssh-server

# Dienst starten und aktivieren
sudo systemctl enable --now ssh

# Proof: Status und Port
sudo systemctl status ssh --no-pager | sed -n '1,6p'
ss -tlnp | egrep ':22\s' || ss -tlnp | egrep 'ssh' || true
```

**Rollback / Entfernen**

```bash
sudo systemctl disable --now ssh
sudo apt remove --purge -y openssh-server
sudo apt autoremove -y
```

---

### 2 — MySQL / MariaDB CLI (Ersatz für `mysql-client`)

```bash
# MariaDB client compat installiert den mysql-Client-Ersatz
sudo apt install -y mariadb-client-compat

# Proof
mariadb --version || mysql --version || true
```

**Rollback**

```bash
sudo apt remove --purge -y mariadb-client-compat
sudo apt autoremove -y
```

---

### 3 — GNUTLS Hinweis (Paketnamen)

Du hast versucht `GNUTLS`/`gnutls` zu installieren — Paketnamen sind case‑sensitive und meist `gnutls-bin` oder `libgnutls30`. Installiere nur wenn du ein bestimmtes Tool brauchst:

```bash
# Beispiel: CLI‑Werkzeuge für gnutls
sudo apt install -y gnutls-bin libgnutls30

# Proof
gnutls-cli --version || true
```

---

### 4 — Python Numerik: schnell und zuverlässig (System‑Pakete)

Da du bereits viele System‑Build‑Deps installiert hast und dein Xeon ältere CPU‑Baseline hat, ist der **schnellste, robusteste Weg** für sofortige Arbeit: die Debian‑Pakete für Python‑Numerik verwenden (systemweit, funktioniert zuverlässig).

```bash
# Installiere System‑Python Pakete
sudo apt update
sudo apt install -y python3-numpy python3-scipy python3-pandas python3-matplotlib

# Proof (System‑Python)
python3 -c "import numpy as np, scipy, pandas, matplotlib; print('numpy', np.__version__, 'scipy', scipy.__version__)"
```

**Vorteil:** sofort lauffähig, keine lokale Kompilierung.  
**Rollback:**

```bash
sudo apt remove --purge -y python3-numpy python3-scipy python3-pandas python3-matplotlib
sudo apt autoremove -y
```

---

### 5 — Alternative: saubere venv + lokalen Build (wenn du Isolation willst)

Wenn du Isolation willst und bereit bist, NumPy für deine CPU zu bauen (länger), dann:

```bash
# Build‑Deps (falls noch nicht)
sudo apt install -y build-essential gfortran python3-dev libopenblas-dev liblapack-dev libssl-dev pkg-config

# venv erstellen / aktivieren
python3 -m venv ~/k501-env
source ~/k501-env/bin/activate

# pip updaten
python -m pip install --upgrade pip setuptools wheel

# NumPy aus Quellcode bauen (kompatibel mit deiner CPU)
python -m pip install --no-binary=:all: numpy

# danach SciPy/Pandas/Matplotlib
python -m pip install scipy pandas matplotlib scikit-learn

# Proof
python -c "import numpy as np; print('numpy', np.__version__)"
deactivate
```

**Hinweis:** Kompilieren kann lange dauern. Wenn `pip` beim Bootstrapping von `cmake`/`ninja` scheitert, stelle sicher, dass `cmake` und `ninja-build` aus apt installiert sind (du hast cmake/ninja bereits).

**Rollback (venv entfernen)**

```bash
deactivate || true
rm -rf ~/k501-env
```

---

### 6 — Wenn du micromamba/conda bevorzugst (vorcompilierte Binaries)

Conda/Micromamba liefert oft Binaries, die auf älteren CPUs laufen. Falls du das bevorzugst, aktiviere micromamba und prüfe NumPy dort:

```bash
# Beispiel: Einmalig ein Kommando im micromamba env ausführen (kein Aktivieren nötig)
# Ersetze Pfad durch dein env
/tmp/bin/micromamba run -p /home/iinkognit0/micromamba/envs/k501 python -c "import numpy as np; print('numpy', np.__version__)"
```

Wenn das fehlschlägt, baue NumPy in diesem Env wie oben (pip --no-binary) oder erstelle ein neues micromamba‑Env mit kompatiblen Paketen.

---

### 7 — Proof‑Before‑State: Checkliste, die du jetzt ausführen solltest

Führe diese Befehle nacheinander aus und poste die Ausgaben, falls etwas fehlschlägt:

```bash
# SSH
sudo systemctl status ssh --no-pager | sed -n '1,6p'

# SQL client
mariadb --version || mysql --version || true

# Python numerik (System)
python3 -c "import numpy as np; print('numpy', np.__version__)" || true

# Falls du venv benutzt:
source ~/k501-env/bin/activate
python -c "import numpy as np; print('venv numpy', np.__version__)" || true
deactivate || true
```

---

### 8 — Nächste Schritte, je nach Ergebnis

- **Wenn `python3 -c "import numpy..."` erfolgreich ist:** du kannst sofort dein Spektral‑Script mit `python3` ausführen oder die venv nutzen, je nach Präferenz.
- **Wenn `numpy` noch fehlt:** wähle **System‑Pakete** (schnell) oder **venv + build** (sauber). Ich helfe beim jeweiligen Ablauf.
- **Wenn `sshd` nicht startet:** poste `sudo journalctl -u ssh -n 80 --no-pager` — ich analysiere sofort.
- **Wenn `mariadb`/`mysql` Probleme macht:** poste die Fehlermeldung.

---

Wenn du willst, führe jetzt die **Proof‑Before‑State** Befehle aus und poste die Ausgaben. Ich analysiere sofort und gebe den nächsten präzisen Schritt (z. B. NumPy via apt installieren, oder Build‑Fehler beheben).