Alles klar. Ich fasse jetzt alle Optimierungen und Systemparameter des T520 für K501 in einer kompakten, operativen Checkliste zusammen. Ziel: direkt startklar, minimalistisch, reproduzierbar, Multipass- und iGPU-ready.

## **K501 T520 – Startklar-Checkliste**

### **1. Kernel- & System-Tuning (Bash / Sysctl)**

- Swappiness → 10  
    
- Overcommit Memory → 1  
    
- vfs_cache_pressure → 50  
    
- dirty_ratio → 10  
    
- dirty_background_ratio → 5  
    
- CPU-Frequenz → Performance-Modus aktiv  
    

Befehle:

sudo sysctl -w vm.swappiness=10

sudo sysctl -w vm.overcommit_memory=1

sudo sysctl -w vm.vfs_cache_pressure=50

sudo sysctl -w vm.dirty_ratio=10

sudo sysctl -w vm.dirty_background_ratio=5

cpupower frequency-set -g performance

### **2. RAM-Aufteilung & Limits**

- OS / Desktop: 2 GB  
    
- LLM / Transmutation: 2–3 GB  
    
- Frame Cache: 3 GB  
    
- Index + Vektoren: 2 GB  
    
- Reserve: 2 GB  
    
- iGPU-Speicher: 128–256 MB  
    

### **3. Ingest-Pipeline (Python)**

Struktur:

1. Safe-Read → 10 KB / Datei (Linux Page Size kompatibel)  
    
2. Embedding → nomic-embed-text  
    
3. LLM-Analyse → qwen2.5:0.5b  
    
4. Frame-Hash → SHA256 (inkl. prev-Hash)  
    
5. Vector Projection → AVX1-optimiert / iGPU-SIMD  
    
6. Resonance Check → libk501.so  
    
7. Ledger Append → NDJSON, append-only  
    

Multiprocessing:

- Max Worker = 2 (physische Kerne)  
    
- Worker 1: read → embed → hash  
    
- Worker 2: read → embed → hash  
    
- Queue-Pipeline zur overlap-Optimierung  
    

Multipass-Konzept:

- Pass 1: Schnelldurchlauf → semantische Übersicht  
    
- Pass 2: Detaildurchlauf → tiefere Vektorprojektionen  
    
- Pass n: Vollständige Frame-Ingest → alle Inhalte  
    

### **4. iGPU (Intel HD 3000) Integration**

- Aktiv: kleine Vektor-SIMD-Rechenoperationen  
    
- Nutzung: dot_product, vector_norm, cosine_similarity  
    
- Speicher: 128–256 MB RAM zuweisen  
    
- Vorteil: CPU-Last reduziert, deterministisch  
    

### **5. Frame-Ledger & Navigation**

- Ledger: NDJSON, append-only, SHA256 ID  
    
- Indizes: sequence / time / hash / type  
    
- Zugriff: unabhängig von Originaldateien, Navigation über Frame-Raum  
    
- Social-Integration: Mastodon direkt aus Frames publishen  
    

### **6. Startsequenz (Operational)**

1. Kernel-Tuning aktivieren (Sysctl / CPU-Performance)  
    
2. RAM & iGPU konfigurieren  
    
3. Multipass-Pipeline starten (parallel_ingest.py)  
    
4. Embedding + LLM initialisieren  
    
5. Ledger prüfen → Hashes validieren  
    
6. Optional: Frames an Mastodon senden / spiegeln  
    

### **7. Monitoring & Performance**

- CPU-Temp: ~71°C (Sweetspot)  
    
- RAM-Auslastung: max. ~9–10 GB (inkl. iGPU)  
    
- Durchsatz 915 Dateien / ~10–15 min mit 2 Worker Multipass  
    

Wenn du willst, kann ich als nächstes eine ultrakompakte „Quick Start“-Version schreiben, die wirklich alles in einem Schritt ausführt, inkl. Multipass, iGPU, LLM & Ledger-Initialisierung, sodass du den T520 direkt hochfahren und starten kannst.

Willst du, dass ich das erstelle?