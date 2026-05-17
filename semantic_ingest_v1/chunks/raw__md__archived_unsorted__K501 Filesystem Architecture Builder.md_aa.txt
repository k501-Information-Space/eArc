### **Hardware Reality Acknowledged: The eSATA Advantage**

Your hardware correction regarding the ThinkPad T520 is critical and actually works heavily in your favor.

Using the **eSATA port** instead of USB 2.0 is the mathematically correct choice for the K501eArc. USB 2.0 caps at roughly 40 MB/s with heavy CPU overhead. The eSATA port hooks directly into the T520’s SATA controller, giving you raw SATA II speeds (up to 300 MB/s) with zero USB-translation overhead.

This means your fast 250GB internal SSD will handle the OS and the Sovereign Toolchain (/opt/k501/st_root), while the Crucial 1TB over eSATA will swallow the continuous append-only writes (/mnt/crucial_1tb) without bottlenecking the CPU.

Let’s build the exact deterministic structure you defined.

### **Execution: The Filesystem Scaffolding Script**

Open your Debian 13 terminal. Because we are writing to /opt/ and /mnt/, we must run this as root (via sudo), but we will mathematically lock the ownership back to your standard operator account so you don't need sudo to run the K501 node later.

Save this script as build_k501_fs.sh, make it executable (chmod +x build_k501_fs.sh), and run it with sudo ./build_k501_fs.sh:

Bash

#!/bin/bash  
# ==============================================================================  
# K501 Filesystem Architecture Builder  
# Target: Debian 13 | ThinkPad T520 (Internal SSD + eSATA Crucial 1TB)  
# ==============================================================================  
  
# Ensure root execution for base directory creation  
if [ "$EUID" -ne 0 ]; then  
echo "[FATAL] Must be run as root to create /opt and /mnt structures."  
exit 1  
fi  
  
# Detect the actual human operator running the script  
OPERATOR=${SUDO_USER:-$USER}  
echo "[K501] Building architecture for Operator: $OPERATOR"  
  
# Define immutable paths  
OPT_BASE="/opt/k501"  
MNT_BASE="/mnt/crucial_1tb/k501_data"  
  
# 1. Build the Sovereign Toolchain & Runtime (Internal 250GB SSD)  
echo "[K501] Scaffolding isolated execution environment in $OPT_BASE..."  
mkdir -p "$OPT_BASE/st_root/"{bin,lib,interfaces,comms,genesis_src}  
mkdir -p "$OPT_BASE/runtime/"{modules,boot_loader,node_A_primary,node_B_replica}  
  
# 2. Build the Bounded Storage Domain (External eSATA 1TB SSD)  
echo "[K501] Scaffolding append-only domains in $MNT_BASE..."  
mkdir -p "$MNT_BASE/"{blob_archive,hard_index,network_deltas}  
  
# 3. Establish the Symlink Bridge  
echo "[K501] Binding active data symlink..."  
ln -sfn "$MNT_BASE" "$OPT_BASE/data"  
  
# 4. Enforce Operator Permissions (Crucial step to avoid sudo lockouts)  
echo "[K501] Locking permissions to operator identity..."  
chown -R "$OPERATOR:$OPERATOR" "$OPT_BASE"  
chown -R "$OPERATOR:$OPERATOR" "/mnt/crucial_1tb"  
  
echo "=============================================================================="  
echo "[K501] ARCHITECTURE MANIFESTED SUCCESSFULLY."  
echo "=============================================================================="  

### **Operator Verification Step**

Once the script completes, run the following command to verify the structure and permissions:

Bash

tree -a /opt/k501  

_(If tree is not installed, run sudo apt install tree or use ls -la /opt/k501/)_

You should see the exact structure you outlined, with data glowing as a symlink pointing to /mnt/crucial_1tb/k501_data/.

### **Mounting the eSATA Drive (Next Step)**

Since the directory /mnt/crucial_1tb now physically exists, your next operational step will be to connect the 1TB Crucial SSD via the eSATA port, format it (EXT4 or XFS recommended for append-only data), and mount it to that specific directory.

Are you ready to format and mount the Crucial SSD via /etc/fstab to lock it into the system permanently, or would you prefer to move directly into writing the isolated Python/Bash logic for the runtime/modules/?