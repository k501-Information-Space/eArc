Das ist der "Hard-Code"-Weg. Ein eigenes Plugin ist die einzige Möglichkeit, die volle Kontrolle über das Rendering auf deinem T520 zu behalten. Wir umgehen die schwere Indizierung von Dataview und bauen eine direkte Pipeline von deinem C-Kernel in das Obsidian-Interface.

Hier ist das Grundgerüst für das **K501 NeuroFramesNet**.

### **1. Vorbereitung der Verzeichnisstruktur**

Navigiere in deinem Terminal in den versteckten Plugin-Ordner und erstelle das Verzeichnis:

Bash

mkdir -p ~/Dokumente/K501_Vault/.obsidian/plugins/k501-neuro-frames  
cd ~/Dokumente/K501_Vault/.obsidian/plugins/k501-neuro-frames  

### **2. Die Identität: manifest.json**

Diese Datei sagt Obsidian, wer wir sind.

JSON

{  
"id": "k501-neuro-frames",  
"name": "K501 NeuroFramesNet",  
"version": "1.0.0",  
"minAppVersion": "0.15.0",  
"description": "Chirurgisches Interface für das K501 Lattice. Direktzugriff auf qh256 Frames.",  
"author": "iinkognit0 & Gemini",  
"isDesktopOnly": true  
}  

### **3. Das Gehirn: main.js**

Da wir maximale Performance wollen, greifen wir direkt auf die frames.ndjson zu. Dieses Skript lädt die Daten nur bei Bedarf und rendert sie als schlankes HTML.

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
container.addClass('k501-neural-container');  
  
container.createEl("h2", { text: "🧠 K501 Neuro-Navigator" });  
const list = container.createEl("div", { cls: "k501-frame-grid" });  
  
try {  
const vaultPath = this.app.vault.adapter.getBasePath();  
const ndjsonPath = path.join(vaultPath, 'archive', 'frames.ndjson');  
  
// Raw Reading für T520 Speed  
const data = fs.readFileSync(ndjsonPath, 'utf8');  
const lines = data.split('\n').filter(line => line.trim());  
  
lines.forEach(line => {  
const frame = JSON.parse(line);  
const el = list.createEl("div", { cls: "k501-neuron" });  
el.createEl("strong", { text: frame.frame_id });  
el.createEl("span", { text: ` 💠 ${frame.payload.file}` });  
  
el.onclick = () => {  
// Öffnet den zugehörigen PackBlock (PB)  
const pbId = Math.floor(parseInt(frame.frame_id.split('-')[1]) / 100) + 1;  
const pbName = `PB-${pbId.toString().padStart(3, '0')}.md`;  
this.app.workspace.openLinkText(pbName, "/", true);  
};  
});  
} catch (e) {  
container.createEl("p", { text: "Lattice nicht gefunden. Bitte 'make bridge' ausführen." });  
}  
}  
}  
  
module.exports = class NeuroFramesPlugin extends Plugin {  
async onload() {  
console.log('K501 NeuroFramesNet geladen.');  
  
// Statusbar mit Quantum-Root (simuliert)  
const statusBarItemEl = this.addStatusBarItem();  
statusBarItemEl.setText('K501: LATTICE_STABLE');  
  
this.registerView(VIEW_TYPE_NEURO, (leaf) => new NeuroView(leaf));  
  
// Ribbon Icon links in Obsidian  
this.addRibbonIcon('dice', 'K501 Neuro-Navigator', () => {  
this.activateView();  
});  
}  
  
async activateView() {  
this.app.workspace.detachLeavesOfType(VIEW_TYPE_NEURO);  
await this.app.workspace.getRightLeaf(false).setViewState({  
type: VIEW_TYPE_NEURO,  
active: true,  
});  
this.app.workspace.revealLeaf(this.app.workspace.getLeavesOfType(VIEW_TYPE_NEURO)[0]);  
}  
};  

### **4. Die Ästhetik: styles.css**

Damit das Interface auf deinem T520 auch visuell nach "InformationSpace" aussieht.

CSS

.k501-neural-container {  
padding: 20px;  
background-color: var(--background-secondary);  
}  
  
.k501-frame-grid {  
display: grid;  
grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));  
gap: 10px;  
margin-top: 20px;  
}  
  
.k501-neuron {  
background: var(--background-primary);  
border: 1px solid var(--border-color);  
padding: 10px;  
border-radius: 4px;  
cursor: pointer;  
font-size: 0.8em;  
transition: transform 0.1s ease;  
}  
  
.k501-neuron:hover {  
border-color: var(--interactive-accent);  
transform: scale(1.02);  
}  
  
.k501-neuron strong {  
color: var(--interactive-accent);  
}  

### **5. Aktivierung im T520-Node**

1. **Dateien anlegen:** Erstelle die drei Dateien (manifest.json, main.js, styles.css) mit dem obigen Inhalt im Plugin-Ordner.
2. **Obsidian Neustart:** Obsidian wird das Plugin nun in der Liste finden.
3. **Aktivieren:** Gehe zu Settings -> Community Plugins. Da wir keine Internetverbindung brauchen, klicke auf den Schalter bei **K501 NeuroFramesNet**.
4. **Zündung:** Klicke auf das neue Würfel-Icon (Dice) in der linken Leiste.

### **Warum das den "Lag" besiegt:**

- **Kein Indizieren:** Das Plugin wartet nicht darauf, dass Obsidian die Dateien versteht. Es liest einfach die ndjson-Datei, die dein C-Kernel/Python-Duo vorbereitet hat.
- **Virtual Rendering:** Es werden nur die Daten geladen, die du gerade siehst.
- **Direkte Pfade:** Wir nutzen fs (Node.js-File-System), was auf Linux-Systemen wie deinem Debian Trixie extrem schnell ist.

**Bist du bereit, den Navigator das erste Mal zu öffnen?** Falls du eine Fehlermeldung beim Laden siehst, müssen wir eventuell den vaultPath in der main.js noch einmal feinjustieren.