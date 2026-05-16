### Status kurz

`~/k501/P.csv` existiert nicht. Du hast zwei sinnvolle Wege jetzt: **(A)** eine Test‑/Beispielmatrix erzeugen und die Pipeline durchlaufen, oder **(B)** deine echte `P.csv` an den erwarteten Ort kopieren. Ich liefere präzise, reproduzierbare Befehle für beides plus Validierung und Ausführung des vorhandenen `spectral_analysis.py`.

---

### A — Schnelltest: gültige Beispiel‑P.csv erzeugen und Analyse laufen lassen

1. **Erzeuge Ordner und Beispielmatrix (stochastisch, 10×10)**

```bash
mkdir -p ~/k501
python3 - <<'PY'
import numpy as np, pathlib
out = pathlib.Path.home() / "k501" / "P.csv"
N = 10
rng = np.random.default_rng(42)
P = rng.random((N,N))
P = P / P.sum(axis=1, keepdims=True)
np.savetxt(out, P, delimiter=',', fmt='%.12f')
print("Wrote", out)
PY
```

2. **Kurz prüfen**

```bash
head -n 5 ~/k501/P.csv
wc -l ~/k501/P.csv
```

3. **Validieren (Zeilensummen, NaN/Inf, Quadratisch)**

```bash
python3 - <<'PY'
import numpy as np, pathlib, sys
p = pathlib.Path.home() / "k501" / "P.csv"
P = np.loadtxt(p, delimiter=',')
print("shape:", P.shape)
rs = P.sum(axis=1)
print("row sum min/max:", rs.min(), rs.max())
print("max row deviation:", float(np.max(np.abs(rs-1.0))))
print("NaN count:", int(np.isnan(P).sum()), "Inf count:", int(np.isinf(P).sum()))
PY
```

4. **Skript ausführen (System‑Python, bereits installierte NumPy)**

```bash
export OPENBLAS_NUM_THREADS=4 OMP_NUM_THREADS=4
python3 ~/k501/spectral_analysis.py
ls -la ~/k501_results
cat ~/k501_results/eigenvalues.txt
```

5. **Wenn Fehler auftreten**

- Poste die komplette Fehlermeldung.
- Wenn `eigs` nicht konvergiert: erhöhe `k` nicht zu hoch, probiere `which='LM'` oder `which='LR'` oder reduziere `k`.

---

### B — Deine echte P.csv an den richtigen Ort kopieren

Wähle die passende Methode:

- **Lokale Datei verschieben** (wenn Datei z. B. in `~/Downloads`):

```bash
mkdir -p ~/k501
mv ~/Downloads/P.csv ~/k501/P.csv
# oder kopieren
cp /pfad/zu/deiner/P.csv ~/k501/P.csv
```

- **Per SCP von einem Remote‑Host holen**:

```bash
# Beispiel: von user@host:/path/to/P.csv
scp user@host:/path/to/P.csv ~/k501/P.csv
```

- **Per wget/curl von URL herunterladen**:

```bash
mkdir -p ~/k501
wget -O ~/k501/P.csv "https://example.com/path/to/P.csv"
# oder
curl -o ~/k501/P.csv "https://example.com/path/to/P.csv"
```

Nach Kopie: führe die **Validierung** aus (siehe A.3) und dann das **Skript** (A.4).

---

### C — Wenn die Matrix sehr groß (Speicher/Performance)

Wenn (N) groß ist (z. B. (>5000)):

- **Nutze sparse**: speichere/lade als COO/CSR und verwende `scipy.sparse.linalg.eigs`.
- **Schätze RAM‑Bedarf**: (N^2 \times 8) Bytes für dichte `float64`. Beispiel: (N=10000) → (10000^2*8 \approx 800) MB × 1 = 800 MB (dies ist nur grobe Schätzung).
- **Empfehlung**: wenn Datei > einige 100 MB, sag mir die Dateigröße (`ls -lh ~/k501/P.csv`) — ich gebe dir das sparse‑Lade‑Snippet und ein angepasstes `spectral_analysis.py`.

---

### D — Quick checks, falls du jetzt laufen lässt

Führe diese Befehle nacheinander aus und poste die Ausgaben, falls etwas nicht passt:

```bash
# Existenz prüfen
ls -l ~/k501/P.csv || echo "P.csv fehlt"

# Dateigröße
ls -lh ~/k501/P.csv

# Validierung (ein Befehl)
python3 - <<'PY'
import numpy as np, pathlib, sys
p = pathlib.Path.home() / "k501" / "P.csv"
if not p.exists():
    print("MISSING"); sys.exit(2)
P = np.loadtxt(p, delimiter=',')
print("shape:", P.shape, "rowSumMinMax:", P.sum(axis=1).min(), P.sum(axis=1).max())
PY

# Skript starten (falls Validierung OK)
export OPENBLAS_NUM_THREADS=4 OMP_NUM_THREADS=4
python3 ~/k501/spectral_analysis.py
```

---

### Nächster Schritt von dir

Sag kurz, welche Option du willst: **A** (Beispiel erzeugen und testen), **B** (ich warte, bis du echte `P.csv` kopiert hast), oder **C** (ich erstelle sofort ein sparse‑angepasstes `spectral_analysis.py` für große Matrizen). Ich liefere dann den nächsten Copy‑Paste‑Block oder passe das Skript an.