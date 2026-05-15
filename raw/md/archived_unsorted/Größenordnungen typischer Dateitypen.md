## **1. Größenordnungen typischer Dateitypen**

Die folgenden Werte sind realistische Durchschnittsgrößen. Die tatsächliche Größe hängt von Auflösung, Kompression und Qualität ab.

### **Textbasierte Dateien**

|**Typ**|**Typischer Inhalt**|**Größe**|
|---|---|---|
|TXT (reiner Text)|1 Buchseite|2–5 KB|
|---|---|---|
|TXT|1 Roman (~300 Seiten)|1–2 MB|
|---|---|---|
|Markdown|technische Dokumentation|50 KB – 1 MB|
|---|---|---|
|JSON / NDJSON|strukturierte Daten|10 KB – 10 MB|
|---|---|---|
|Logfile|Systemlog (1 Tag)|5–200 MB|
|---|---|---|

Wichtige Beobachtung

Text ist extrem effizient.

Beispiel:

- 1 GB Text ≈ 500 Millionen Wörter  
    

### **Office-Dokumente**

|**Typ**|**Beispiel**|**Größe**|
|---|---|---|
|DOCX|10 Seiten Text|50–200 KB|
|---|---|---|
|DOCX|100 Seiten Bericht|1–5 MB|
|---|---|---|
|DOCX mit Bildern|Präsentationsdokument|10–50 MB|
|---|---|---|
|XLSX|Tabelle mit 10k Zeilen|1–10 MB|
|---|---|---|

### **PDF**

|**Typ**|**Beispiel**|**Größe**|
|---|---|---|
|Text-PDF|wissenschaftliches Paper|1–5 MB|
|---|---|---|
|PDF mit Bildern|Magazin|20–100 MB|
|---|---|---|
|Scan-PDF|gescannte Dokumente|100 MB – 1 GB|
|---|---|---|

### **Bilder**

|**Typ**|**Auflösung**|**Größe**|
|---|---|---|
|JPEG|Smartphone Foto|2–6 MB|
|---|---|---|
|PNG|Screenshot|1–5 MB|
|---|---|---|
|RAW Kamera|DSLR Foto|20–60 MB|
|---|---|---|
|TIFF|Archivformat|50–200 MB|
|---|---|---|

### **Audio**

|**Format**|**Qualität**|**Größe pro Minute**|
|---|---|---|
|MP3|128 kbps|~1 MB|
|---|---|---|
|MP3|320 kbps|~2.5 MB|
|---|---|---|
|AAC|Streaming|~1 MB|
|---|---|---|
|WAV|unkomprimiert|~10 MB|
|---|---|---|

Beispiele:

|**Länge**|**Größe**|
|---|---|
|3 Minuten Song (MP3)|3–8 MB|
|---|---|
|1 Stunde Podcast|60–120 MB|
|---|---|
|24h Audioaufnahme|1.4–3 GB|
|---|---|

### **Video**

|**Auflösung**|**Bitrate**|**Größe pro Minute**|
|---|---|---|
|480p|~1 Mbps|~7 MB|
|---|---|---|
|720p|~3 Mbps|~22 MB|
|---|---|---|
|1080p|~8 Mbps|~60 MB|
|---|---|---|
|4K|35–60 Mbps|260–450 MB|
|---|---|---|

Beispiele:

|**Inhalt**|**Größe**|
|---|---|
|10 min YouTube 1080p|500–700 MB|
|---|---|
|1h 1080p Video|3–5 GB|
|---|---|
|2h Film 4K|40–80 GB|
|---|---|

# **2. Größenrelation (Übersicht)**

|**Einheit**|**Bytes**|
|---|---|
|1 KB|1,024 Bytes|
|---|---|
|1 MB|1,024 KB|
|---|---|
|1 GB|1,024 MB|
|---|---|
|1 TB|1,024 GB|
|---|---|

Praktische Vorstellung:

|**Größe**|**Vergleich**|
|---|---|
|1 MB|~300 Buchseiten Text|
|---|---|
|100 MB|~1 Stunde Audio|
|---|---|
|1 GB|~15 Minuten 4K Video|
|---|---|
|1 TB|~250 Filme in 1080p|
|---|---|

# **3. Bedeutung für ein Frame-basiertes System**

Wenn dein System Ereignisse als Frames speichert, ist entscheidend:

Framegröße.

Beispiel:

|**Framegröße**|**Frames pro GB**|
|---|---|
|256 Bytes|~4 Millionen|
|---|---|
|1 KB|~1 Million|
|---|---|
|4 KB|~250.000|
|---|---|

Beispiel:

1 TB Speicher mit 1 KB Frames

→ ~1 Milliarde Frames

# **4. Rolle von FFmpeg**

Das Werkzeug FFmpeg ist für ein solches System besonders wertvoll.

### **Hauptfunktionen**

1. Videoanalyse  
    - Frame-Extraktion  
        
    - Szenenerkennung  
        
2. Audioanalyse  
    - Speech-to-Text Vorbereitung  
        
    - Spektrumanalyse  
        
3. Transcoding  
    - Video → kleinere Formate  
        
    - Audio → standardisierte Bitrate  
        
4. Streaming  
    - Live-Frame-Extraction  
        

### **Beispiele für Verarbeitung**

Audio → Frames

- Podcast  
    
- Gespräch  
    
- Meeting  
    

Pipeline:

Audio

→ ffmpeg Segmentierung

→ Speech Recognition

→ Text Frames

Video → Frames

Video

→ ffmpeg Frame Extraction

→ Bildanalyse

→ Ereignisframes

# **5. Beispiel: Datenvolumen eines Wissenssystems**

Angenommen ein Node verarbeitet täglich:

- 2h Video  
    
- 4h Audio  
    
- 500 Dokumente  
    
- 10k Systemevents  
    

Datenmenge:

|**Typ**|**Größe**|
|---|---|
|Video|~10 GB|
|---|---|
|Audio|~500 MB|
|---|---|
|Dokumente|~1 GB|
|---|---|
|Logs|~200 MB|
|---|---|

Gesamt:

≈ 12 GB / Tag

Nach Extraktion in strukturierte Frames:

≈ 100–500 MB / Tag

# **6. Wichtigste Erkenntnis**

Rohdaten sind groß.

Strukturierte Information ist klein.

Typisches Verhältnis:

Rohdaten → strukturierte Frames

10:1 bis 100:1 Kompression der Informationsebene

Wenn du möchtest, kann ich als nächsten Schritt auch zeigen:

Wie eine globale Frame-Ökonomie aussehen würde, wenn

10 Millionen Geräte kontinuierlich Frames erzeugen (inkl. Datenraten, Netzwerkbedarf und Speicherwachstum).