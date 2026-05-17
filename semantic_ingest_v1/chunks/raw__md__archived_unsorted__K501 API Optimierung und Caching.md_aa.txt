Hier ist der vollständige, finalisierte Code für die **K501 Query API v9.8.1**.

Ich habe die Graph-Route ebenfalls mit einer **Caching-Logik** ausgestattet. Da die Berechnung des Graphen bei über 1.400 Frames (plus die neuen Genesis-Frames) hunderte Megabyte an Matrix-Operationen erzeugt, würde Obsidian sonst bei jedem Refresh den T520 einfrieren.

### **scripts/k501_query_api.py**

Python

import os  
import json  
import time  
import numpy as np  
from flask import Flask, jsonify  
from flask_cors import CORS  
from k501_frame import Frame  
from k501_core import load_all_frames  
  
# ============================================================  
# K501 QUERY API · v9.8.1 · NEURO-GRAPH & TURBO-CACHE  
# TARGET: N_T520 (AVX OPTIMIZED)  
# ============================================================  
  
app = Flask(__name__)  
CORS(app)  
  
# Globale Caches zur Entlastung des i5-2520M  
_CACHE_TOP = {"data": None, "timestamp": 0}  
_CACHE_GRAPH = {"data": None, "timestamp": 0}  
CACHE_TTL = 600 # 10 Minuten Gültigkeit  
  
@app.route('/resonance/top')  
def resonance_top():  
"""Berechnet die stärksten Resonanz-Paare im Gitter (Cached)."""  
global _CACHE_TOP  
start_time = time.time()  
  
# Cache-Check  
if _CACHE_TOP["data"] and (time.time() - _CACHE_TOP["timestamp"] < CACHE_TTL):  
return jsonify(_CACHE_TOP["data"])  
  
frames = load_all_frames()  
if len(frames) < 2:  
return jsonify({"error": "Ungenügende Datenmenge"}), 400  
  
print(f"[*] Berechne Top-Resonanz für {len(frames)} Frames...")  
  
# Matrix-Operationen  
vectors = np.array([Frame.vectorize(f['payload'].get('content', '')) for f in frames])  
sim_matrix = np.dot(vectors, vectors.T)  
indices = np.triu_indices(len(frames), k=1)  
scores = sim_matrix[indices]  
  
top_idx = np.argsort(scores)[-20:][::-1]  
  
results = []  
for idx in top_idx:  
i, j = indices[0][idx], indices[1][idx]  
results.append({  
"score": round(float(scores[idx]), 4),  
"source": frames[i]['payload'].get('file', frames[i]['id']),  
"target": frames[j]['payload'].get('file', frames[j]['id'])  
})  
  
response_data = {  
"node": "N_T520",  
"frame_count": len(frames),  
"compute_time": round(time.time() - start_time, 2),  
"top_pairs": results,  
"cached": False  
}  
  
# Cache füllen  
_CACHE_TOP = {"data": response_data, "timestamp": time.time()}  
_CACHE_TOP["data"]["cached"] = True  
  
return jsonify(response_data)  
  
@app.route('/resonance/graph')  
def resonance_graph():  
"""Liefert Daten für das Obsidian Plugin: k501-neuro-frames (Cached)."""  
global _CACHE_GRAPH  
start_time = time.time()  
  
# Cache-Check  
if _CACHE_GRAPH["data"] and (time.time() - _CACHE_GRAPH["timestamp"] < CACHE_TTL):  
return jsonify(_CACHE_GRAPH["data"])  
  
frames = load_all_frames()  
if not frames:  
return jsonify({"nodes": [], "links": []})  
  
print(f"[*] Generiere Neuro-Graph für {len(frames)} Frames...")  
  
# 1. Knoten-Mapping  
nodes = []  
for f in frames:  
nodes.append({  
"id": f['id'],  
"label": f['payload'].get('file', f['id'][:8]),  
"type": "EVO" if "EVO" in f.get('tags', []) else "CORE",  
"tags": f.get('tags', [])  
})  
  
# 2. Kanten-Berechnung  
vectors = np.array([Frame.vectorize(f['payload'].get('content', '')) for f in frames])  
sim_matrix = np.dot(vectors, vectors.T)  
indices = np.triu_indices(len(frames), k=1)  
  
links = []  
THRESHOLD = 0.82 # Justierung der Verbindungsdichte  
  
for idx in range(len(indices[0])):  
i, j = indices[0][idx], indices[1][idx]  
score = float(sim_matrix[i, j])  
if score > THRESHOLD:  
links.append({  
"source": frames[i]['id'],  
"target": frames[j]['id'],  
"value": round(score, 4)  
})  
  
response_data = {  
"node": "N_T520_VISUAL",  
"nodes": nodes,  
"links": links,  
"compute_time": round(time.time() - start_time, 2),  
"cached": False  
}  
  
# Cache füllen  
_CACHE_GRAPH = {"data": response_data, "timestamp": time.time()}  
_CACHE_GRAPH["data"]["cached"] = True  
  
return jsonify(response_data)  
  
@app.route('/status')  
def status():  
"""System-Health Check."""  
return jsonify({  
"status": "online",  
"node": "N_T520",  
"version": "9.8.1",  
"epoch": int(time.time()),  
"cache_status": {  
"top": _CACHE_TOP["timestamp"] > 0,  
"graph": _CACHE_GRAPH["timestamp"] > 0  
}  
})  
  
if __name__ == "__main__":  
print("[*] K501 API v9.8.1 online auf Port 27124")  
app.run(port=27124, host='0.0.0.0', debug=False)  

### **Was wir technisch optimiert haben:**

- **Dual-Caching:** Sowohl die Top-Liste als auch der Graph werden separat im RAM gehalten.
- **Performance-Logging:** Im Terminal siehst du jetzt sofort, wenn die API anfängt zu rechnen ([*] Generiere Neuro-Graph...).
- **Obsidian-Ready:** Die Links nutzen jetzt die UUIDs (f['id']), was für das k501-neuro-frames Plugin die stabilste Methode zur Verknüpfung ist.

**Nächster Schritt:**

Soll ich dir ein kurzes Bash-Script schreiben, das beim Systemstart prüft, ob die API läuft, und sie gegebenenfalls im Hintergrund startet, damit dein Obsidian-Plugin immer "Saft" hat?