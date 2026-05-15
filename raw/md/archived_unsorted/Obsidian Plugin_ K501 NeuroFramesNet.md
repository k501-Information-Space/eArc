Das ist eine konsequente und richtige Entscheidung. **Dataview** ist zwar mächtig, aber es ist ein "Generalist" – es indiziert alles über eine JavaScript-Abstraktionsschicht, was auf der Hardware eines T520 (i5, 2. Gen) bei großen Datenmengen schnell zum Flaschenhals wird.

Wir ersetzen den "schweren Panzer" Dataview jetzt durch eine chirurgische Eigenentwicklung: das **K501 NeuroFramesNet Plugin**.

Da du keine Plugins installiert hast, bauen wir dieses Plugin als **Internal Scripting System** oder als **schlankes Custom Plugin**, das direkt auf die vor-optimierten Daten zugreift, die dein C-Kernel und die Python-Bridge bereits geliefert haben.

## 🛠️ Blueprint: K501 NeuroFramesNet Plugin

Der Grundgedanke: Das Plugin soll **nicht** indizieren (das hat der Kernel schon getan), sondern nur **visualisieren und verknüpfen**.

### 1. Die Architektur (The Lean Approach)

Anstatt dass Obsidian jede Datei scannt, liest das **NeuroFramesNet** direkt die archive/frames.ndjson. Das ist für das T520 eine einfache Leseoperation im Millisekundenbereich.

- **Backend:** Dein vorhandener C-Kernel (für Integrität).
- **Data-Source:** archive/frames.ndjson (Der Single Point of Truth).
- **Frontend:** Ein dediziertes Obsidian-Ribbon-Icon, das eine "Neural Map" öffnet.

### 2. Kern-Features des Plugins

#### **A. Instant Lattice Navigator**

Anstelle einer langsamen Dataview-Tabelle nutzen wir ein **virtuelles Scroll-System**.

- Es zeigt alle 1.415 Frames blitzschnell an, da es nur die JSON-Daten im Speicher hält, anstatt 1.415 Markdown-Objekte zu rendern.

#### **B. Synaptisches Linking (The Neural Part)**

Das Plugin erkennt "Resonanzen". Wenn du einen Frame betrachtest, zeigt es dir am Rand eine Liste von **verwandten Frames** an.

- Die Logik berechnet die Distanz zwischen den qh256-Hashes oder nutzt die Schlagwort-Gewichtung der Bridge.

#### **C. Quantum Root Status**

In der Statusbar von Obsidian siehst du permanent den Status deines Lattice:

[K501: 1dc9... | STABLE]

- Das Plugin ruft im Hintergrund periodisch den C-Kernel auf, um zu prüfen, ob die 350 MB in 03_Archive noch integer sind.

### 3. Technisches Implementierungs-Konzept

Wir nutzen das **Obsidian API** in Kombination mit einem lokalen **Node.js-Worker** (da Obsidian auf Electron basiert).

#### **Warum das schneller ist als Dataview:**

1. **Kein File-Watching:** Dataview reagiert auf jede Dateiänderung im gesamten Vault. NeuroFramesNet reagiert nur auf Änderungen in der frames.ndjson.
2. **Direkt-Zugriff:** Wir umgehen den Obsidian-Metadaten-Cache und greifen direkt auf die Festplatte zu (Raw Reading).
3. **C-Interoperabilität:** Wir können das Plugin so bauen, dass es Befehle direkt an das Makefile sendet.

### 4. Der "Neuro-Interface" Entwurf

Stell dir eine Ansicht vor, die nicht wie ein Ordner aussieht, sondern wie ein **Interaktions-Grid**.

Markdown

[ 💠 F-001 ] <--- Synapse ---> [ 💠 F-412 ]  
| |  
+---- Gewicht: 0.87 (Programmer) ----+  

**Operator-Entscheidung:** Sollen wir das Plugin als **"Obsidian-Script"** (via Templater/QuickAdd, aber ohne deren Ballast) oder als **echtes lokales Plugin** im Ordner .obsidian/plugins/k501-neuro-frames/ anlegen?

Ein echtes Plugin gibt uns volle Kontrolle über das T520-Rendering.

### Nächster Schritt:

Ich kann dir das manifest.json und die main.js für das **K501 NeuroFramesNet** entwerfen. Es wird ein "Surgical Plugin" – minimaler Code, maximale Geschwindigkeit.

**Soll ich das Grundgerüst für das Plugin-Verzeichnis erstellen, damit du es nur noch in deinen .obsidian/plugins Ordner kopieren musst?**