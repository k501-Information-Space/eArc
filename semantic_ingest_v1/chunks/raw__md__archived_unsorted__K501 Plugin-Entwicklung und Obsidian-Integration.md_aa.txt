Absolut verstanden. Wir drosseln das Tempo und konzentrieren uns auf das Wesentliche: **Die physische Erschaffung deines eigenen Plugins.** Nachdem dein T520 die 1.415 Frames nun semantisch "verdaut" hat (v3.6 Ingest), liegen die Daten perfekt strukturiert in der frames.ndjson bereit. Jetzt bauen wir das Fenster, durch das Obsidian diese neuronalen Daten betrachtet, ohne das System zu belasten.

Hier ist die **vollständige Code-Evolution** für das Fundament deines **K501 NeuroFramesNet** Plugins.

### **Schritt 1: Initialisierung des Plugin-Verzeichnisses**

Führe dies im Terminal aus, um den Raum für dein Plugin zu schaffen:

Bash

# Erstelle das Verzeichnis im versteckten Obsidian-Ordner  
mkdir -p ~/Dokumente/K501_Vault/.obsidian/plugins/k501-neuro-frames  
cd ~/Dokumente/K501_Vault/.obsidian/plugins/k501-neuro-frames  

### **Schritt 2: Die Identität (manifest.json)**

Diese Datei ist der "Pass" des Plugins. Sie sagt Obsidian, dass wir existieren.

JSON

{  
"id": "k501-neuro-frames",  
"name": "K501 NeuroFramesNet",  
"version": "1.0.0",  
"minAppVersion": "0.15.0",  
"description": "Neuronaler Navigator für das K501 Lattice. Nutzt DeepRead-Tags für assoziative Suche.",  
"author": "iinkognit0",  
"isDesktopOnly": true  
}  

### **Schritt 3: Das Gehirn (main.js)**

Wir halten den Code schlank. Das Plugin liest beim Öffnen die frames.ndjson und rendert die Frames als interaktive Neuronen. Dank Node.js-Integration in Obsidian greifen wir direkt auf die Datei zu – das ist der Geschwindigkeits-Vorteil gegenüber Dataview.

JavaScript

const { Plugin, ItemView, WorkspaceLeaf } = require('obsidian');  
const fs = require('fs');  
const path = require('path');  
  
const VIEW_TYPE_NEURO = "k501-neuro-view";  
  
class NeuroView extends ItemView {  
constructor(leaf) { super(leaf); }  
getViewType() { return VIEW_TYPE_NEURO; }  
getDisplayText() { return "K501 Neuro-Navigator"; }  
  
async onOpen() {  
const container = this.containerEl.children[1];  
container.empty();  
container.createEl("h2", { text: "🧠 K501 Neuro-Navigator", cls: "k501-title" });  
  
const list = container.createEl("div", { cls: "k501-frame-grid" });  
  
try {  
const vaultPath = this.app.vault.adapter.getBasePath();  
const ndjsonPath = path.join(vaultPath, 'archive', 'frames.ndjson');  
  
// Schnelles Auslesen der semantischen Daten  
const data = fs.readFileSync(ndjsonPath, 'utf8');  
const lines = data.split('\n').filter(line => line.trim());  
  
lines.forEach(line => {  
const frame = JSON.parse(line);  
const neuron = list.createEl("div", { cls: "k501-neuron" });  
  
// Header: ID und Tags  
const header = neuron.createEl("div", { cls: "k501-neuron-header" });  
header.createEl("span", { text: frame.frame_id, cls: "k501-id" });  
  
if (frame.tags) {  
frame.tags.forEach(tag => {  
header.createEl("span", { text: tag, cls: "k501-tag" });  
});  
}  
  
// Inhalt: Dateiname und DeepRead-Vorschau  
neuron.createEl("div", { text: frame.payload.file, cls: "k501-filename" });  
neuron.createEl("div", { text: frame.payload.preview, cls: "k501-preview" });  
  
neuron.onclick = () => {  
// Navigiere zum entsprechenden PackBlock im Lattice  
const pbId = Math.floor(parseInt(frame.frame_id.split('-')[1]) / 100) + 1;  
const pbPath = `02_QuantumLattice/UB-001/SB-001/PB-${pbId.toString().padStart(3, '0')}.md`;  
this.app.workspace.openLinkText(pbPath, "/", true);  
};  
});  
} catch (e) {  
container.createEl("p", { text: "Lattice-Fehler: archive/frames.ndjson nicht lesbar." });  
}  
}  
}  
  
module.exports = class NeuroFramesPlugin extends Plugin {  
async onload() {  
console.log('K501 NeuroFramesNet initialisiert.');  
this.registerView(VIEW_TYPE_NEURO, (leaf) => new NeuroView(leaf));  
  
this.addRibbonIcon('brain', 'Neuro-Navigator öffnen', () => {  
this.activateView();  
});  
}  
  
async activateView() {  
const { workspace } = this.app;  
let leaf = workspace.getLeavesOfType(VIEW_TYPE_NEURO)[0];  
  
if (!leaf) {  
leaf = workspace.getRightLeaf(false);  
await leaf.setViewState({ type: VIEW_TYPE_NEURO, active: true });  
}  
workspace.revealLeaf(leaf);  
}  
};  

### **Schritt 4: Das Design (styles.css)**

Damit dein T520 die Informationen auch visuell hierarchisch darstellt.

CSS

.k501-frame-grid {  
display: flex;  
flex-direction: column;  
gap: 12px;  
padding: 10px;  
}  
  
.k501-neuron {  
background: var(--background-primary-alt);  
border: 1px solid var(--border-color);  
padding: 12px;  
border-radius: 6px;  
cursor: pointer;  
transition: all 0.2s ease;  
}  
  
.k501-neuron:hover {  
border-color: var(--interactive-accent);  
background: var(--background-modifier-hover);  
}  
  
.k501-neuron-header {  
display: flex;  
gap: 8px;  
margin-bottom: 6px;  
flex-wrap: wrap;  
}  
  
.k501-id {  
font-weight: bold;  
color: var(--text-accent);  
}  
  
.k501-tag {  
background: var(--text-selection);  
font-size: 0.75em;  
padding: 2px 6px;  
border-radius: 4px;  
}  
  
.k501-filename {  
font-size: 0.9em;  
font-weight: 500;  
margin-bottom: 4px;  
}  
  
.k501-preview {  
font-size: 0.8em;  
color: var(--text-muted);  
line-height: 1.4;  
overflow: hidden;  
display: -webkit-box;  
-webkit-line-clamp: 2;  
-webkit-box-orient: vertical;  
}  

### **Zusammenfassung des Fortschritts**

Du hast nun:

1. **Den K501_Kernel:** Der die Integrität deiner 1.415 Dateien schützt.
2. **Die DeepRead-Engine:** Die jedem Frame Bedeutung verleiht.
3. **Das NeuroFramesNet Plugin:** Ein chirurgisches Werkzeug, das direkt auf die frames.ndjson zugreift, ohne Obsidian zu verlangsamen.

### **Was du jetzt tun musst:**

1. Erstelle die drei Dateien im genannten Ordner.
2. Gehe in Obsidian zu **Settings -> Community Plugins**.
3. Aktiviere den Schalter für **K501 NeuroFramesNet**.
4. Klicke auf das neue Gehirn-Icon in der linken Leiste.

**Bist du bereit für den ersten Testlauf des Navigators?** Wenn er sich öffnet, werden die DeepRead-Tags zum ersten Mal direkt im Obsidian-Interface leuchten.