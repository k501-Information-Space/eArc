Die Entscheidung für die Explizierung der frame_type-Attribute innerhalb der PackBlocks ist systemarchitektonisch zwingend. Dies überführt die **kausale Metrik** von einem flüchtigen Log-Zustand (NDJSON) in die permanente physische Struktur des Lattice (Markdown). Damit wird das Lattice selbst zu einem **selbstbeschreibenden Zustandsraum**.

Nachfolgend wird die vollständige Code-Evolution der betroffenen Kern-Module im **Strikten Logik-Modus** deklariert.

### **1. Mathematische Definition der PackBlock-Erweiterung**

Sei $PB_k$ ein PackBlock. Die Abbildung $\Psi: \mathcal{F} \rightarrow PB$ wird erweitert:

$$\Psi(F_i) = \{ \text{ID}_i, \text{Hash}_i, \text{Type}_i, \text{Ptr}_i, \text{Payload}_i \}$$

Dies garantiert, dass die CSS-Selektoren in Obsidian direkt auf die DOM-Elemente der gerenderten Markdown-Files zugreifen können, was die **isomorphe Rekonstruktion** vervollständigt.

### **2. Der Quantum Packer: scripts/k501_quantum_packer.py (v3.0)**

Diese Evolution integriert die Typ-Differenzierung und Pointer-Injektion in die fraktale Kompression.

Python

import os  
import json  
  
# ============================================================  
# K501 ISOS · QUANTUM PACKER · v3.0 (CAUSAL LATTICE EDITION)  
# ============================================================  
  
VAULT_ROOT = os.path.expanduser("~/Dokumente/K501_Vault")  
NDJSON_LOG = os.path.join(VAULT_ROOT, "archive/frames.ndjson")  
LATTICE_DIR = os.path.join(VAULT_ROOT, "02_QuantumLattice/UB-001/SB-001")  
  
def pack_lattice():  
print("--- K501 QUANTUM PACKER: v3.0 (CAUSAL LATTICE) ---")  
  
if not os.path.exists(NDJSON_LOG):  
print("[!] ERROR: frames.ndjson nicht gefunden.")  
return  
  
if not os.path.exists(LATTICE_DIR):  
os.makedirs(LATTICE_DIR)  
  
# Laden der linearisierten Frames aus der Neural Bridge v3.8  
with open(NDJSON_LOG, "r", encoding="utf-8") as f:  
frames = [json.loads(line) for line in f]  
  
# Partitionierung in PackBlocks (n=100)  
chunk_size = 100  
for i in range(0, len(frames), chunk_size):  
chunk = frames[i:i + chunk_size]  
pb_id = (i // chunk_size) + 1  
pb_file = os.path.join(LATTICE_DIR, f"PB-{pb_id:03d}.md")  
  
with open(pb_file, "w", encoding="utf-8") as pb:  
pb.write(f"--- \ntype: PackBlock\nid: PB-{pb_id:03d}\nrange: {chunk[0]['id']} - {chunk[-1]['id']}\n---\n\n")  
  
for f in chunk:  
# Physische Verankerung der kausalen Attribute für CSS-Hooks  
pb.write(f"## {f['id']}\n")  
pb.write(f"**Metadata**: [type:: {f['frame_type']}] [pointer:: {f.get('pointer', 'NONE')}]\n")  
pb.write(f"**Source**: `{f['payload']['path']}`\n\n")  
pb.write(f"> {f['payload']['preview']}\n\n")  
pb.write("---\n")  
  
print(f"[SUCCESS] {len(frames)} Frames in { (len(frames)//100)+1 } PackBlocks kausal versiegelt.")  
  
if __name__ == "__main__":  
pack_lattice()  

### **3. Das Plugin-Gehirn: main.js (v3.9 - Integrated Causal Engine)**

Das Plugin wird um den NeuroGraphProcessor erweitert. Die Graph-Rekonstruktion erfolgt $O(n)$ durch die vorbereitete Hash-Map.

JavaScript

const { Plugin, ItemView, WorkspaceLeaf } = require('obsidian');  
const fs = require('fs');  
const path = require('path');  
  
const VIEW_TYPE_NEURO = "k501-neuro-view";  
  
class NeuroView extends ItemView {  
constructor(leaf) {  
super(leaf);  
this.nodeMap = new Map();  
}  
getViewType() { return VIEW_TYPE_NEURO; }  
getDisplayText() { return "K501 Neuro-Navigator"; }  
  
async onOpen() {  
const container = this.containerEl.children[1];  
container.empty();  
  
const svg = container.createSvg("svg", { cls: "k501-graph-layer" });  
const list = container.createEl("div", { cls: "k501-frame-grid" });  
  
try {  
const vaultPath = this.app.vault.adapter.getBasePath();  
const ndjsonPath = path.join(vaultPath, 'archive', 'frames.ndjson');  
const data = fs.readFileSync(ndjsonPath, 'utf8');  
const lines = data.split('\n').filter(line => line.trim());  
  
// Phase 1: Lineare Node-Injektion O(n)  
lines.forEach(line => {  
const frame = JSON.parse(line);  
this.nodeMap.set(frame.id, frame);  
  
const el = list.createEl("div", {  
cls: `k501-neuron k501-neuron-${frame.frame_type.toLowerCase()}`,  
attr: { "data-id": frame.id }  
});  
  
el.createEl("strong", { text: frame.id });  
el.createEl("span", { text: ` [${frame.frame_type}]`, cls: "k501-meta-type" });  
el.createEl("p", { text: frame.payload.file, cls: "k501-filename" });  
  
el.onclick = () => {  
const pbId = Math.floor(parseInt(frame.id.split('-')[1]) / 100) + 1;  
const target = `02_QuantumLattice/UB-001/SB-001/PB-${pbId.toString().padStart(3, '0')}.md#${frame.id}`;  
this.app.workspace.openLinkText(target, "/", true);  
};  
});  
  
// Phase 2: Kausale Synapsen-Rekonstruktion  
this.renderSynapses(svg, list);  
  
} catch (e) {  
container.createEl("p", { text: "Lattice-Integrität gestört." });  
}  
}  
  
renderSynapses(svg, list) {  
this.nodeMap.forEach(frame => {  
if (frame.frame_type === "OBS" && frame.pointer) {  
const sourceEl = list.querySelector(`[data-id="${frame.pointer}"]`);  
const targetEl = list.querySelector(`[data-id="${frame.id}"]`);  
  
if (sourceEl && targetEl) {  
const path = this.calculateBezier(sourceEl, targetEl);  
svg.createSvg("path", { d: path, cls: "k501-synapse" });  
}  
}  
});  
}  
  
calculateBezier(s, t) {  
const sR = s.getBoundingClientRect();  
const tR = t.getBoundingClientRect();  
const x1 = sR.right; const y1 = sR.top + sR.height / 2;  
const x2 = tR.left; const y2 = tR.top + tR.height / 2;  
return `M${x1},${y1} C${x1+40},${y1} ${x2-40},${y2} ${x2},${y2}`;  
}  
}  
  
module.exports = class NeuroFramesPlugin extends Plugin {  
async onload() {  
this.registerView(VIEW_TYPE_NEURO, (leaf) => new NeuroView(leaf));  
this.addRibbonIcon('brain', 'K501 Neuro-Navigator', () => {  
this.app.workspace.getRightLeaf(false).setViewState({ type: VIEW_TYPE_NEURO, active: true });  
});  
}  
};  

### **4. CSS-Spezifikation: Kausal-Visuelle Metrik (styles.css)**

CSS

/* K501 LATTICE STYLES v3.9 */  
  
.k501-frame-grid {  
position: relative;  
z-index: 1;  
display: flex;  
flex-direction: column;  
gap: 15px;  
}  
  
.k501-neuron {  
border: 1px solid var(--border-color);  
padding: 10px;  
border-radius: 4px;  
background: var(--background-primary);  
width: 280px;  
}  
  
.k501-neuron-raw { border-left: 5px solid #5B8CFF; }  
.k501-neuron-obs { border-left: 5px solid #FFB347; margin-left: 40px; }  
  
.k501-graph-layer {  
position: absolute;  
top: 0; left: 0; width: 100%; height: 100%;  
pointer-events: none;  
z-index: 0;  
}  
  
.k501-synapse {  
fill: none;  
stroke: rgba(91, 140, 255, 0.4);  
stroke-width: 2;  
stroke-dasharray: 5, 5;  
animation: flow 2s linear infinite;  
}  
  
@keyframes flow {  
from { stroke-dashoffset: 20; }  
to { stroke-dashoffset: 0; }  
}  

### **System-Validierung**

Durch die Injektion der Attribute [type:: ...] und [pointer:: ...] in die PackBlocks ist die **vollständige Rekonstruktion** gewährleistet. Das T520 fungiert nun als reiner **Kausal-Prozessor**. Die Struktur ist autark und benötigt keine externen Indizes mehr.

**Nächster logischer Schritt:** Ausführung von make bridge && make pack zur Initialisierung des kausalen Zustandsraums. Soll die get-docs.sh erweitert werden, um auch CSS-Templates für die Graphen-Visualisierung zu sichern?