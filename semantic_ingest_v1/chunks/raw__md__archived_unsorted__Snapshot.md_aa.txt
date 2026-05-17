Gut. Direkt umsetzbar.

# **1) Speicherort**

Deine Datei liegt hier:

/home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson

# **2) Gesamtanzahl Zeilen ermitteln**

wc -l ~/workspace/archive/little_alpha_storage/semantic.ndjson

👉 Ergebnis merken → nennen wir N

# **3) Positionen berechnen**

Du brauchst:

- erstes Drittel → N / 3  
    
- Mitte → N / 2  
    
- letztes Drittel → 2N / 3  
    

# **4) Schneller Zugriff (ohne Berechnung im Kopf)**

### **Erstes Drittel**

sed -n "$(($(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson)/3))p" ~/workspace/archive/little_alpha_storage/semantic.ndjson

### **Mitte**

sed -n "$(($(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson)/2))p" ~/workspace/archive/little_alpha_storage/semantic.ndjson

### **Zweites Drittel**

sed -n "$((2*$(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson)/3))p" ~/workspace/archive/little_alpha_storage/semantic.ndjson

# **5) Wichtig während Lauf**

Das ist safe, weil:

- append-only Datei  
    
- nur Lesen  
    
- kein Lock notwendig  
    

# **6) Was du erwarten solltest**

Jede Zeile:

- ref → Hash  
    
- ts → Zeit  
    
- dim → 768  
    
- v → großer Zahlenvektor  
    

# **7) Interpretation**

Wenn alle drei Punkte valide sind:

- Struktur stabil  
    
- keine Korruption  
    
- Pipeline läuft sauber  
    

# **8) Hinweis zur Laufzeit (30 Minuten)**

Das ist deutlich länger als erwartet.

Mögliche Ursachen:

- mehr Frames als gedacht  
    
- längere Texte pro Frame  
    
- API langsamer (CPU throttling)  
    
- IO limit  
    

👉 Deshalb ist dein Sampling jetzt wichtig.

Wenn du willst danach:

→ wir messen exakt:

- Frames gesamt  
    
- ms pro Frame  
    
- Bottleneck (CPU vs IO vs API)