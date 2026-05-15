iinkognit0@K501:~$ cat > ~/k501/run_sparse_and_collect.sh <<'SH'  
> #!/usr/bin/env bash  
# ~/k501/run_sparse_and_collect.sh  
# Einfacher Wrapper: führt spectral_analysis.py im Sparse-Modus aus,  
# sammelt alle Ergebnisdateien (auch aus dem Standardordner) und  
# verschiebt sie in das gewünschte outdir.  
# Usage: bash ~/k501/run_sparse_and_collect.sh ~/k501/P_csr.npz ~/k501_results_sparse  
  
set -euo pipefail  
  
INPUT="${1:-$HOME/k501/P_csr.npz}"  
OUTDIR="${2:-$HOME/k501_results_sparse}"  
THREADS="${3:-4}"  
K="${4:-6}"  
  
DEFAULT_OUT="$HOME/k501_results"  
  
mkdir -p "$OUTDIR"  
mkdir -p "$DEFAULT_OUT"  
  
export OPENBLAS_NUM_THREADS="$THREADS"  
export OMP_NUM_THREADS="$THREADS"  
  
echo "Running spectral_analysis.py"  
echo " input: $INPUT"  
echo " outdir requested: $OUTDIR"  
echo " threads: $THREADS, k: $K"  
echo  
  
# Run and capture stdout/stderr into outdir logs  
python3 "$HOME/k501/spectral_analysis.py" --input "$INPUT" --sparse --k "$K" --threads "$THREADS" --outdir "$OUTDIR" \  
   > "$OUTDIR/run_stdout.log" 2> "$OUTDIR/run_stderr.log" || true  
  
# If the script wrote to the default folder, move those files into the requested outdir  
if [ -d "$DEFAULT_OUT" ]; then  
 echo "Collecting results from default folder $DEFAULT_OUT (if any)..."  
 shopt -s nullglob  
 for f in "$DEFAULT_OUT"/*; do  
   # skip parent/hidden entries  
   [ -e "$f" ] || continue  
   base="$(basename "$f")"  
   # don't overwrite existing files in OUTDIR; append suffix if needed  
   if [ -e "$OUTDIR/$base" ]; then  
     mv -v "$f" "$OUTDIR/${base}.$(date +%s)"  
echo "Done. Logs: $OUTDIR/run_stdout.log and $OUTDIR/run_stderr.log"  
> SH  
iinkognit0@K501:~$ chmod +x ~/k501/run_sparse_and_collect.sh  
iinkognit0@K501:~$ bash ~/k501/run_sparse_and_collect.sh ~/k501/P_csr.npz ~/k501_results_sparse 4 6  
Running spectral_analysis.py  
input: /home/iinkognit0/k501/P_csr.npz  
outdir requested: /home/iinkognit0/k501_results_sparse  
threads: 4, k: 6  
  
Collecting results from default folder /home/iinkognit0/k501_results (if any)...  
'/home/iinkognit0/k501_results/eigenvalues.txt' -> '/home/iinkognit0/k501_results_sparse/eigenvalues.txt.1778446153' umbenannt  
'/home/iinkognit0/k501_results/eigenvectors_real.txt' -> '/home/iinkognit0/k501_results_sparse/eigenvectors_real.txt.1778446153' umbenannt  
  
Final contents of /home/iinkognit0/k501_results_sparse:  
insgesamt 56  
drwxrwxr-x  2 iinkognit0 iinkognit0  4096 10. Mai 20:49 .  
drwx------ 30 iinkognit0 iinkognit0  4096 10. Mai 20:42 ..  
-rw-rw-r--  1 iinkognit0 iinkognit0   362 10. Mai 20:33 eigenvalues.txt  
-rw-rw-r--  1 iinkognit0 iinkognit0   362 10. Mai 20:49 eigenvalues.txt.1778446153  
-rw-rw-r--  1 iinkognit0 iinkognit0   941 10. Mai 20:33 eigenvectors_real.txt  
-rw-rw-r--  1 iinkognit0 iinkognit0   941 10. Mai 20:49 eigenvectors_real.txt.1778446153  
-rw-rw-r--  1 iinkognit0 iinkognit0   188 10. Mai 20:49 run_stderr.log  
-rw-rw-r--  1 iinkognit0 iinkognit0    68 10. Mai 20:49 run_stdout.log  
-rw-rw-r--  1 iinkognit0 iinkognit0 21542 10. Mai 20:02 spectrum.png  
  
Quick preview of eigenvalues (first 20 lines if present):  
(1.0+0.0j)  
(0.13016800126412942+0.09770775967179623j)  
(0.13016800126412942-0.09770775967179623j)  
(0.0705156025326621+0.13589065016000795j)  
(0.0705156025326621-0.13589065016000795j)  
(0.14588477791942425+0.0j)  
(-0.038101232779624544+0.1025853180522186j)  
(-0.038101232779624544-0.1025853180522186j)  
(-0.06718155040644838+0.0j)  
(0.025404835907689906+0.0j)  
  
Done. Logs: /home/iinkognit0/k501_results_sparse/run_stdout.log and /home/iinkognit0/k501_results_sparse/run_stderr.log  
iinkognit0@K501:~$