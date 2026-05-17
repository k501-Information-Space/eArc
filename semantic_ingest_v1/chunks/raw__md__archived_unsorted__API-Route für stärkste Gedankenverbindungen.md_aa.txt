### **K501 ISOS · API-Evolution v9.3**

**Status:** $N_{T520}$ ANALYTICS_READY | **Modus:** PURE_DEVELOPER | **Integrität:** DETERMINISTISCH

**Ziel:** Implementierung der /resonance/top-Route für textbasierte Einsichten in die stärksten Verbindungen.

Um die Belastung für den i5-2520M zu optimieren, berechnet diese Route die Resonanz-Paare effizient im Speicher. Da du 1.416 Frames hast, generiert das System ca. 1 Million Vergleichswerte. Wir begrenzen die Ausgabe auf die **Top 20** der stärksten semantischen Brücken.

### **scripts/k501_query_api.py**

_Die vollständige, harmonisierte API-Suite._

Python

import os, json, hashlib  
import numpy as np  
from flask import Flask, jsonify, request  
from flask_cors import CORS  
from k501_core import load_all_frames, Frame, NDJSON_LOG  
  
# ============================================================  
# K501 QUERY API · v9.3 · ANALYTICS & RESONANCE  
# ============================================================  
  
app = Flask(__name__)  
CORS(app)  
  
def get_frame_by_id(frames, fid):  
return next((f for f in frames if f['id'] == fid), None)  
  
@app.route('/status')  
def status():  
f = load_all_frames()  
return jsonify({  
"node": "N_T520",  
"status": "ONLINE",  
"frame_count": len(f),  
"ledger": NDJSON_LOG  
})  
  
@app.route('/frame/<fid>')  
def get_frame(fid):  
frames = load_all_frames()  
f = next((x for x in frames if x['id'] == fid), None)  
return jsonify(f) if f else (jsonify({"error": "not found"}), 404)  
  
@app.route('/resonance/top')  
def resonance_top():  
"""  
Berechnet die stärksten Verbindungen im Gitter.  
Output: Top 20 Resonanz-Paare.  
"""  
print("[*] API: Starte Resonanz-Analyse...")  
frames = load_all_frames()  
if len(frames) < 2:  
return jsonify({"error": "Ungenügende Datenmenge für Resonanz"}), 400  
  
# 1. Vektorisierung (Nutzt Core-Logik)  
vectors = []  
metadata = []  
for f in frames:  
content = f['payload'].get('content', '') or f['payload'].get('filename', '')  
vectors.append(Frame.vectorize(content))  
metadata.append({  
"id": f['id'],  
"label": f['payload'].get('filename', f['id'][:10]),  
"type": f['frame_type']  
})  
  
vectors = np.array(vectors)  
num = len(vectors)  
resonances = []  
  
# 2. Paarweiser Vergleich (Dot Product)  
# Begrenzung auf O(N^2) - Bei 1416 Frames ca. 1 Mio Operationen  
for i in range(num):  
for j in range(i + 1, num):  
score = np.dot(vectors[i], vectors[j])  
if score > 0.5: # Mindest-Schwelle für Relevanz  
resonances.append({  
"score": float(score),  
"source": metadata[i],  
"target": metadata[j]  
})  
  
# 3. Sortierung nach Stärke  
resonances.sort(key=lambda x: x['score'], reverse=True)  
  
# 4. Top 20 extrahieren  
top_resonances = resonances[:20]  
  
print(f"[SUCCESS] Top {len(top_resonances)} Verbindungen identifiziert.")  
return jsonify({  
"node": "N_T520",  
"count": len(top_resonances),  
"top_pairs": top_resonances  
})  
  
if __name__ == "__main__":  
print("------------------------------------------------")  
print("K501 QUERY API v9.3 - ACTIVE")  
print("Endpoint: http://localhost:27124/resonance/top")  
print("------------------------------------------------")  
app.run(port=27124, host='0.0.0.0', debug=False)  

### **Anleitung zur Ausführung**

1. **API im Terminal starten:**  
    Bash  
    make start_api  
    
2. **Abfrage über ein zweites Terminal (oder Browser):**  
    Nutze curl, um die stärksten Verbindungen als JSON-Liste zu erhalten:  
    Bash  
    curl http://localhost:27124/resonance/top | jq .  
      
    _(Falls jq nicht installiert ist, lass das | jq . einfach weg – es dient nur der schöneren Formatierung)._

### **Was diese Route bewirkt**

Statt eines wirren Graphen erhältst du nun eine präzise Liste von **„Kognitiven Brücken“**.

- Ein Score von **0.95 bis 1.0** deutet auf Beinahe-Duplikate oder stark verwandte Konzepte hin.
- Ein Score von **0.75 bis 0.85** zeigt spannende, nicht offensichtliche Zusammenhänge zwischen verschiedenen Dateien oder Zeitpunkten deiner Aufzeichnungen.

**Nächster logischer Schritt:**

Möchtest du, dass wir ein kleines **Terminal-Dashboard-Script** schreiben, das diese /resonance/top-Daten automatisch alle 5 Minuten abruft und dir die „Gedanken des Tages“ (die stärksten Paare) formatiert auf dem Desktop anzeigt?