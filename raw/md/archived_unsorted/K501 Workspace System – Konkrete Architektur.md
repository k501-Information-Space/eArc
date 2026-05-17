## **K501 Workspace System – Konkrete Architektur**

Zeitstempel bestätigt:

Unix Epoch 1773249958

11.03.2026 – 18:25:58 CET

Ziel: integrierter lokaler Wissens-Workspace mit deterministischer Architektur.

# **1. Gesamtstruktur**

Das System besteht aus fünf klar getrennten Ebenen.

1. Systemkernel  
    
2. Service Layer  
    
3. Data Engine  
    
4. Orchestrator  
    
5. Interface Layer  
    

Diese Trennung verhindert Abhängigkeitsschleifen.

# **2. Systemkernel**

Der Kernel stellt Runtime und UI-Framework bereit.

Komponenten:

- Browser Engine – basiert auf Chromium  
    
- Window Manager  
    
- Panel System  
    
- Plugin Loader  
    
- Web Runtime  
    

Funktion:

- Rendering der Oberfläche  
    
- Plugin-Host für Module  
    
- WebSocket/HTTP Client  
    

Der Kernel enthält keine Fachlogik.

# **3. Service Layer**

Hier laufen alle lokalen Dienste als separate Prozesse.

|**Service**|**Funktion**|
|---|---|
|K501 Query API|Resonanzanalyse|
|---|---|
|Frame Index Service|Vektorindex|
|---|---|
|Ollama Runtime|lokale Modelle|
|---|---|
|Graph Builder|Netzwerkgenerierung|
|---|---|
|Import Service|Deep Read / Datenimport|
|---|---|
|Event Service|Systemereignisse|
|---|---|

Diese Dienste kommunizieren ausschließlich über HTTP oder WebSocket.

# **4. Data Engine**

Der Datenkern besteht aus drei Elementen.

### **Vault**

Primärer Datenspeicher.

Eigenschaften:

- Markdown Frames  
    
- JSON Metadaten  
    
- Append-only Archiv  
    

Integration mit Obsidian.

### **Frame Index**

Struktur:

- NumPy Vektorindex  
    
- persistente Datei  
    
- float32 Vektoren  
    

Funktion:

- schnelle Ähnlichkeitsberechnung.  
    

### **Resonanzgraph**

Graphstruktur:

- Nodes = Frames  
    
- Edges = semantische Ähnlichkeit.  
    

Exportformate:

- JSON  
    
- Graph-API  
    
- Visualisierung.  
    

# **5. Orchestrator (K501 Client Core)**

Der zentrale Steuerprozess.

Aufgaben:

1. Services starten und überwachen  
    
2. Tasks planen  
    
3. Pipeline ausführen  
    
4. Kontext übertragen  
    

Typische Pipeline:

Import

→ Frame Erstellung

→ Index Update

→ Resonanzanalyse

→ Graph Update.

# **6. Interface Layer**

Mehrere Interfaces greifen auf den Orchestrator zu.

### **Terminal CLI**

Primärer Steuerpunkt.

Beispiele:

- Import starten  
    
- Resonanzanalyse  
    
- Graph erzeugen  
    

### **Editor Interface**

Integration mit Visual Studio Code.

Funktionen:

- Frame bearbeiten  
    
- Resonanzen anzeigen  
    
- Query-Console.  
    

### **Browser Interface**

Web-Panels über Chromium.

Beispiele:

- Graphvisualisierung  
    
- Systemstatus  
    
- Logs.  
    

# **7. Prozessstruktur**

Empfohlene lokale Prozesse.

|**Prozess**|**Beschreibung**|
|---|---|
|k501-client|Orchestrator|
|---|---|
|k501-api|Resonanzservice|
|---|---|
|k501-index|Vektorindexer|
|---|---|
|ollama|LLM Runtime|
|---|---|
|k501-import|Deep Read Importer|
|---|---|
|k501-events|Event Dispatcher|
|---|---|

Alle laufen unabhängig.

# **8. Portstruktur**

Empfohlene Ports.

|**Port**|**Service**|
|---|---|
|27124|K501 Query API|
|---|---|
|27125|Graph Service|
|---|---|
|27126|Frame Index|
|---|---|
|11434|Ollama|
|---|---|
|27127|Event Bus|
|---|---|
|27128|Web Dashboard|
|---|---|

Alle Services lokal gebunden.

# **9. Datenfluss**

### **Import Pipeline**

Quelle

→ Import Service

→ Frame Erstellung

→ Vault Speicherung.

### **Index Pipeline**

Vault

→ Frame Loader

→ Vektorisierung

→ Index Datei.

### **Analyse Pipeline**

Index

→ Resonanz Engine

→ Graph Builder

→ API.

### **Visualisierung**

API

→ Browser Interface

→ Graph Darstellung.

# **10. Kommunikation**

Systeminterne Kommunikation erfolgt über drei Kanäle.

HTTP

Service-zu-Service Kommunikation.

WebSocket

Live-Events.

Dateisystem

persistente Daten.

# **11. Ereignissystem**

Event Bus verarbeitet Systemereignisse.

Typische Events:

Frame Created

Index Updated

Resonance Found

Import Finished.

Events können an externe Kanäle gesendet werden.

# **12. KI-Integration**

Lokale Modelle laufen über Ollama.

Typische Aufgaben:

- Frame Tagging  
    
- Zusammenfassungen  
    
- Query Interpretation.  
    

Die KI greift nicht in deterministische Berechnungen ein.

# **13. Sicherheitsmodell**

Empfohlene Schutzmaßnahmen:

- lokale Bindung der Services  
    
- API Token  
    
- isolierte Prozessrechte  
    
- Vault Backup.  
    

# **14. Systemstart**

Startreihenfolge:

1. Vault prüfen  
    
2. Frame Index laden  
    
3. API starten  
    
4. Ollama starten  
    
5. Event Bus starten  
    
6. K501 Client aktivieren  
    
7. UI öffnen.  
    

# **15. Ergebnis**

Nach Implementierung entsteht ein integriertes lokales Wissenssystem.

Eigenschaften:

- deterministischer Frame-Speicher  
    
- semantische Resonanzanalyse  
    
- lokale KI-Assistenz  
    
- modulare Werkzeuge  
    
- integrierte Entwicklungsumgebung.  
    

Der K501-Client fungiert als Systemoperator, während die eigentlichen Funktionen in unabhängigen Services laufen.