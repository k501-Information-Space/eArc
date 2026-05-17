### Status kurz und klar

**Erledigt:** Dein Wrapper `run_sparse_and_collect.sh` wurde angelegt und ausgeführt. Er hat `spectral_analysis.py` gestartet, die Ergebnisse eingesammelt und in **`~/k501_results_sparse`** abgelegt. Du hast jetzt:

- **eigenvalues.txt** (zwei Kopien, eine mit Zeitstempel)
- **eigenvectors_real.txt** (zwei Kopien)
- **spectrum.png**
- **run_stdout.log** und **run_stderr.log**

---

### Was du jetzt praktisch tun kannst

- **Stationäre Verteilung extrahieren und anzeigen**

```bash
python3 - <<'PY'
import numpy as np
from pathlib import Path
out = Path.home()/ "k501_results_sparse"
vals = np.loadtxt(out/"eigenvalues.txt", dtype=complex)
vecs = np.loadtxt(out/"eigenvectors_real.txt")
idx = int(np.argmin(np.abs(vals - 1.0)))
v = np.abs(vecs[:, idx])
v = v / v.sum()
print("stationary index:", idx)
print("\n".join(f"{x:.12f}" for x in v))
PY
```

- **Eigenwerte nach Betrag sortiert anzeigen**

```bash
python3 - <<'PY'
import numpy as np
from pathlib import Path
vals = np.loadtxt(Path.home()/ "k501_results_sparse"/ "eigenvalues.txt", dtype=complex)
for i,v in enumerate(sorted(vals, key=lambda z: abs(z), reverse=True)[:10]):
    print(i, v, "abs=", abs(v))
PY
```

- **Alte Duplikate mit Zeitstempel prüfen und optional löschen**

```bash
ls -l ~/k501_results_sparse | grep '\.[0-9]\{9\}$' || true
# Wenn du sicher bist, lösche die zeitgestempelten Kopien:
# rm -v ~/k501_results_sparse/*.[0-9]*
```

- **Wenn du die Analyse reproduzierbar in einem einzigen Outdir laufen lassen willst**

```bash
# Führe das Skript direkt mit outdir aus (ohne Wrapper)
export OPENBLAS_NUM_THREADS=4 OMP_NUM_THREADS=4
python3 ~/k501/spectral_analysis.py --input ~/k501/P_csr.npz --sparse --k 6 --threads 4 --outdir ~/k501_results_sparse
```

---

### Kurzinterpretation der Ergebnisse

- **Eigenwert 1.0** bestätigt: eine stationäre Verteilung existiert.
- **Komplexe Eigenwerte in Paaren** deuten auf zyklische/periodische Modi; ihr Betrag (|\lambda|) bestimmt die Abklingrate.
- **Warnung k >= N - 1** ist für deinen Test mit (N=10) unkritisch; bei größeren Matrizen solltest du `k` deutlich kleiner als (N) wählen.

---

### Nächste sinnvolle Schritte

- **Wenn du Unsicherheiten willst:** führe Bootstrap mit `--nboot 20` (rechenintensiv).
- **Wenn du große Matrizen planst:** ich kann dir ein chunked‑Konvertierungs‑Skript liefern oder `spectral_analysis.py` so patchen, dass es strikt das übergebene `--outdir` nutzt (falls du das noch möchtest).
- **Wenn du möchtest, speichere die Analyse‑Skripte in Git** (ich gebe dir die Befehle).

Sag kurz welches der nächsten Schritte du willst: **Bootstrap**, **Chunked convert**, **Git commit** oder **nichts weiter** — ich liefere die exakten Befehle sofort.