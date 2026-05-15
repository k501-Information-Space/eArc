## **1. Ausgangsproblem**

Die bisherige Ingest-Strategie liest pro Dokument nur einen kleinen Abschnitt (z. B. 8–16 KB).

Das ist effizient und erlaubt schnelle Verarbeitung, hat jedoch eine Schwäche:

- Teile des Dokuments bleiben zunächst ungelesen.  
    
- Die erzeugte semantische Repräsentation ist nur eine Annäherung.  
    
- Potenziell wichtige Informationen könnten im ersten Durchlauf fehlen.  
    

Für ein Wissensarchiv ist vollständige Informationserhaltung jedoch ein zentrales Ziel.

Deshalb wird die Pipeline sinnvollerweise mehrstufig erweitert.

# **2. Mehrstufige Ingest-Strategie**

Das System kann in mehreren Durchläufen arbeiten, ähnlich wie Videocodierungssysteme (z. B. HandBrake) oder klassische Mehrpass-Encoder.

Das Prinzip:

1. Schneller Überblick  
    
2. Gezielte Vertiefung  
    
3. Vollständige Archivierung  
    

Jeder Durchlauf verwendet Informationen aus den vorherigen Frames.

# **3. Pass 1 – Schnellscan (Semantic Sketch)**

Der erste Durchlauf dient nur dazu, schnell eine semantische Karte des Archivs zu erzeugen.

Eigenschaften:

- nur kleiner Textabschnitt pro Dokument  
    
- minimale CPU-Last  
    
- schnelle Vektorerzeugung  
    
- schnelle Frame-Erstellung  
    

Ziel:

- Überblick über Themen  
    
- erste semantische Cluster  
    
- erste Resonanzen zwischen Dokumenten  
    

Ergebnis dieses Passes:

- jedes Dokument besitzt einen Basis-Frame  
    
- der Frame enthält einen groben semantischen Vektor  
    

Damit entsteht eine erste semantische Landkarte des Archivs.

Dieser Schritt ist sehr schnell, selbst auf alter Hardware.

# **4. Nutzung der ersten Frames**

Die Frames aus dem ersten Durchlauf haben bereits mehrere Funktionen:

- Dokumente sind eindeutig identifiziert  
    
- semantische Nähe ist erkennbar  
    
- Cluster können gebildet werden  
    
- redundante Dokumente werden sichtbar  
    

Der Node weiß damit bereits:

- welche Dokumente wichtig erscheinen  
    
- welche Themen häufiger vorkommen  
    
- wo tiefer gelesen werden sollte.  
    

# **5. Pass 2 – Selektive Vertiefung**

Im zweiten Durchlauf wird nicht mehr jedes Dokument gleich behandelt.

Der Node nutzt Informationen aus Pass 1.

Typische Kriterien:

- hohe semantische Relevanz  
    
- ungewöhnliche Themen  
    
- starke Resonanz mit anderen Frames  
    
- große Dokumente mit vielen möglichen Informationen.  
    

Für solche Dokumente wird mehr Text eingelesen.

Beispielsweise:

- mehrere Abschnitte  
    
- Anfang + Mitte + Ende  
    
- zufällige zusätzliche Segmente.  
    

Dadurch verbessert sich:

- semantische Genauigkeit  
    
- Kontextverständnis  
    
- Vektorqualität.  
    

Der Frame kann erweitert werden, ohne alte Frames zu verändern.

Das System bleibt append-only.

# **6. Pass 3 – Vollständige Ingest**

Der dritte Durchlauf dient der vollständigen Archivierung.

Jetzt wird das Dokument komplett gelesen.

Dieser Schritt kann erfolgen:

- wenn Ressourcen verfügbar sind  
    
- wenn ein Dokument oft referenziert wird  
    
- oder periodisch im Hintergrund.  
    

Im Ergebnis besitzt das Dokument:

- einen vollständigen Inhalts-Hash  
    
- detaillierte Vektoren  
    
- vollständige Archivrepräsentation.  
    

Damit geht keine Information verloren.

# **7. Nutzung früherer Frames**

Ein zentraler Vorteil dieser Methode:

Frühere Frames bleiben wertvolle Informationsquellen.

Sie liefern:

- semantische Vorhersagen  
    
- Kontext für neue Segmente  
    
- Resonanzreferenzen.  
    

Wenn ein späterer Pass zusätzliche Informationen entdeckt, kann das System:

- neue Frames erzeugen  
    
- bestehende Beziehungen aktualisieren  
    
- semantische Cluster verfeinern.  
    

Die Architektur bleibt dabei unverändert:

alte Frames bleiben unverändert.

Neue Erkenntnisse erscheinen als zusätzliche Frames.

# **8. Effizienzgewinn über Zeit**

Mit jedem Durchlauf wird das System effizienter.

Grund:

Der Node kennt sein Archiv immer besser.

Das führt zu mehreren Effekten:

### **Bessere Priorisierung**

Der Node weiß, welche Dokumente wichtig sind.

### **Reduzierte Rechenlast**

Unwichtige Dokumente werden nicht ständig vollständig analysiert.

### **Verbesserte Semantik**

Neue Frames nutzen bereits vorhandene Resonanzinformationen.

# **9. Parallele Hintergrundverarbeitung**

Der dritte Pass kann vollständig im Hintergrund laufen.

Während der Node bereits arbeitet:

- neue Frames erzeugt  
    
- Netzwerkkommunikation betreibt  
    
- Mastodon-Posts sendet.  
    

Die vollständige Archivierung erfolgt langsam und stabil.

Diese Strategie ist ideal für Systeme mit begrenzter Hardware.

# **10. Auswirkungen auf Node-Netzwerke**

Wenn mehrere Nodes existieren, wird diese Strategie noch stärker.

Ein Node kann:

- Frames anderer Nodes sehen  
    
- eigene Prioritäten anpassen  
    
- gezielt Dokumente vertiefen.  
    

Beispiel:

Node A erkennt ein neues Thema.

Node B sieht den Frame und vertieft ähnliche Dokumente im eigenen Archiv.

So entsteht eine Art kooperative Archivierung.

# **11. Verhalten in einem Netzwerk von 25 Nodes**

Angenommen, es existieren 25 Nodes.

Dann entsteht folgende Dynamik:

1. viele schnelle Erstanalysen  
    
2. verteilte Vertiefungen  
    
3. unterschiedliche Perspektiven auf Dokumente.  
    

Das Netzwerk arbeitet wie ein verteiltes Lesesystem.

Jeder Node:

- liest andere Dokumente intensiver  
    
- erzeugt neue Frames  
    
- erweitert das gemeinsame semantische Netz.  
    

# **12. Warum diese Methode gut zu alter Hardware passt**

Mehrpass-Ingest nutzt eine wichtige Eigenschaft alter Systeme:

Zeit statt Rechenleistung.

Statt alles sofort vollständig zu analysieren:

- arbeitet das System schrittweise  
    
- nutzt Idle-Zeit  
    
- verteilt Rechenlast über Stunden oder Tage.  
    

Das passt sehr gut zu Maschinen wie dem Lenovo ThinkPad T520.

Solche Systeme können über lange Zeiträume stabil arbeiten, ohne hohe Lastspitzen zu erzeugen.

# **13. Langfristige Wirkung**

Mit dieser Methode entsteht ein Archiv, das:

- zuerst grob verstanden wird  
    
- danach immer präziser analysiert wird  
    
- schließlich vollständig gelesen wird.  
    

Das Archiv wächst nicht nur in Größe, sondern auch in semantischer Tiefe.

# **14. Zusammenfassung**

Die Erweiterung der Pipeline führt zu einem mehrstufigen Ingest-Modell:

Pass 1

Schnelle semantische Skizze des gesamten Archivs.

Pass 2

Gezielte Vertiefung wichtiger Dokumente.

Pass 3

Vollständige Archivierung aller Inhalte.

Frühere Frames bleiben erhalten und dienen als Kontext für spätere Analysen.

Damit entsteht ein System, das:

- effizient startet  
    
- kontinuierlich präziser wird  
    
- langfristig vollständige Information bewahrt.