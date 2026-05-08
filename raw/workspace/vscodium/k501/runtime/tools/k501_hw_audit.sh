#!/usr/bin/env bash
# K501 SYSTEM VERIFICATION SCRIPT
# Target: ThinkPad T520 | 8GB DUAL_CHANNEL | Core i5

OUT="k501_hardware_ledger.txt"
: > "$OUT"

echo "=== K501 HARDWARE AUDIT ===" | tee -a "$OUT"
echo "Timestamp: $(date -u +"%Y-%m-%dT%H:%M:%SZ")" | tee -a "$OUT"
echo "--------------------------------" | tee -a "$OUT"

echo "[*] A. CPU Architecture & Threads" | tee -a "$OUT"
lscpu | grep -E "Architecture|Model name|Thread\(s\)|Core\(s\)|Flags" | tee -a "$OUT"
echo "" | tee -a "$OUT"

echo "[*] B. Memory (RAM) Allocation" | tee -a "$OUT"
free -h | tee -a "$OUT"
echo "" | tee -a "$OUT"

echo "[*] C. Memory Hardware Topology (Dual Channel Proof)" | tee -a "$OUT"
sudo dmidecode -t memory | grep -E "Size|Locator|Speed|Type" | grep -v "No Module Installed" | tee -a "$OUT"
echo "" | tee -a "$OUT"

echo "[*] D. Host System & Motherboard" | tee -a "$OUT"
sudo dmidecode -t system | grep -E "Manufacturer|Product|Version" | tee -a "$OUT"
echo "" | tee -a "$OUT"

echo "[*] E. Kernel & OS Baseline" | tee -a "$OUT"
uname -a | tee -a "$OUT"
grep -E "^PRETTY_NAME" /etc/os-release | tee -a "$OUT"
echo "--------------------------------" | tee -a "$OUT"

echo "[SYS] Audit Complete. Full output preserved in $OUT"