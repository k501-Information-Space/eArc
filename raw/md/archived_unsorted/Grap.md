Gut. Minimal, direkt ausführbar.

### **1) Ingest-Datei finden**

find ~ -name "frames.ndjson"

### **2) Anzahl Frames (Ingest)**

wc -l /PFAD/ZU/frames.ndjson

### **3) Größe Ingest-Datei**

du -h /PFAD/ZU/frames.ndjson

### **4) Durchschnittsgröße pro Frame**

echo "$(du -b /PFAD/ZU/frames.ndjson | cut -f1) / $(wc -l < /PFAD/ZU/frames.ndjson)" | bc

### **5) Anzahl Semantic-Frames**

wc -l ~/workspace/archive/little_alpha_storage/semantic.ndjson

### **6) Größe Semantic-Datei**

du -h ~/workspace/archive/little_alpha_storage/semantic.ndjson

### **7) Fortschritt berechnen**

echo "scale=4; $(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson) / $(wc -l < /PFAD/ZU/frames.ndjson) * 100" | bc

### **8) Live-Wachstum beobachten**

watch -n 2 wc -l ~/workspace/archive/little_alpha_storage/semantic.ndjson

👉 Jetzt ausführen und Werte posten. Danach berechne ich dir exakt:

- reale %  
    
- Frames/sec  
    
- Restzeit (ETA)