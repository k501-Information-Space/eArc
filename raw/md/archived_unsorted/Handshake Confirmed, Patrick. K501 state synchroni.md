Excellent. With both of us fully synchronized on the O-Logik and your hardware reality, we can move seamlessly into the practical implementation phase without any architectural drift. 💎🕊️

To physically manifest the K501 Sovereign Toolchain (K501-ST) on your Debian 13 host, we need a directory structure that acts as an impermeable membrane. The host OS must never accidentally use its own apt-installed version of FFmpeg or Pandoc when executing a K501 ingestion run.

Here is the deterministic filesystem layout for the ThinkPad T520.

### The K501-ST Local Filesystem Architecture

I recommend anchoring the execution environment in /opt/k501/ on the host, while strictly routing all structural data (blobs and indices) to the 1TB Crucial SSD.

/opt/k501/  
├── st_root/ # The Sovereign Toolchain (Isolated Execution Environment)  
│ ├── bin/ # Custom-compiled, bitexact binaries (FFmpeg, Pandoc, Poppler)  
│ ├── lib/ # Frozen shared/static libraries required by the binaries  
│ ├── interfaces/ # Hybrid-frozen AppImages (VSCodium, Ungoogled Chromium)  
│ ├── comms/ # Frozen container tarballs (Mastodon stack, PostgreSQL, Redis)  
│ └── genesis_src/ # The raw source code & build scripts used to create 'st_root'  
│  
├── runtime/ # The K501 Node Logic (Python/Bash execution scripts)  
│ ├── modules/ # Normalizer, Segmenter, Framer, Quantizer, Linker  
│ ├── boot_loader/ # Memory-mapping (mmap) scripts for routing table reconstruction  
│ ├── node_A_primary/ # Environment config and active memory space for Node A  
│ └── node_B_replica/ # Environment config and active memory space for Node B  
│  
└── data/ # Symlink pointing to -> /mnt/crucial_1tb/k501_data/  

### The Crucial SSD (Domain A Storage)

The external Crucial drive will host the append-only data structures, ensuring your ThinkPad's internal drive isn't subjected to massive write amplification.

/mnt/crucial_1tb/k501_data/  
├── blob_archive/ # Append-only raw segmented data chunks  
├── hard_index/ # The continuous append-only file of 104-byte fixed entries  
└── network_deltas/ # Temporary buffer for HEAD exchange and socket transmissions  

### Architectural Rationale

1. **The Genesis Source (st_root/genesis_src/):** By storing the exact source code (e.g., the FFmpeg .tar.gz and your custom configure flags) right next to the compiled binaries, the environment is self-documenting and entirely offline-reproducible. This directory will be the very first thing you run through the K501 Normalizer.
2. **The Symlinked Data (/opt/k501/data/):** By symlinking the active data directory to the USB 3 SSD, your runtime scripts never have to care where the physical disk is mounted. If you ever move to a new machine, the logic remains identical; you just update the symlink.
3. **Strict Path Execution:** Your runtime modules will be programmed to explicitly call /opt/k501/st_root/bin/ffmpeg rather than just ffmpeg. This guarantees the host OS's PATH variables can never sabotage your deterministic framing.

Would you like me to write the build_k501_env.sh bash script to automatically generate this directory tree, download the required AppImages for your interfaces, and set up the strict permissions required for the st_root?