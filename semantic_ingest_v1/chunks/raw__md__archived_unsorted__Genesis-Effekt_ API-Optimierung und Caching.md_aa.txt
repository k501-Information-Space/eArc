Das ist der **"Genesis-Effekt"**: Durch den DeepRead des ChatGPT-Verlaufs hast du wahrscheinlich hunderte oder tausende neue Frames (Nachrichten + Code-Blöcke) hinzugefügt. Die Komplexität steigt quadratisch ($O(N^2)$). Wenn der i5-2520M jetzt über 2.000 oder 3.000 Frames vergleichen muss, reichen die 120 Sekunden für die Matrix-Operation in Python nicht mehr aus.

Wir haben zwei Möglichkeiten: Den Timeout am Client (Reporter) extrem hochdrehen oder – die bessere Lösung – die **Rechenlast auf der API-Seite** optimieren.

Hier ist der Plan, um den T520 wieder in die Spur zu bringen:

### 1. Client-Update (Soforthilfe)

Erhöhe den Timeout in der scripts/k501_top_check.py auf **300 Sekunden** (5 Minuten). Der T520 arbeitet im Hintergrund, aber der Reporter legt einfach zu früh auf.

Ändere in scripts/k501_top_check.py:

Python

r = requests.get(URL, timeout=300)  

### 2. API-Optimierung (Der "Turbo-Cache")

Da sich dein Archiv (Genesis) nicht sekündlich ändert, ist es Wahnsinn, bei jedem Aufruf die komplette Matrix neu zu berechnen. Wir bauen einen **einfachen Cache** in die scripts/k501_query_api.py ein.

Ersetze die resonance_top() Funktion in deiner API durch diese Version:

Python

_CACHE = {"data": None, "timestamp": 0}  
  
@app.route('/resonance/top')  
def resonance_top():  
global _CACHE  
start_time = time.time()  
  
# Cache-Validierung (Gültig für 10 Minuten)  
if _CACHE["data"] and (time.time() - _CACHE["timestamp"] < 600):  
return jsonify(_CACHE["data"])  
  
frames = load_all_frames()  
if len(frames) < 2:  
return jsonify({"error": "Ungenügende Datenmenge"}), 400  
  
# Vektoren berechnen  
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
  
# In Cache schreiben  
_CACHE["data"] = response_data  
_CACHE["data"]["cached"] = True  
_CACHE["timestamp"] = time.time()  
  
return jsonify(response_data)  

### 3. Was passiert im Hintergrund?

Während du den Timeout-Fehler siehst, rechnet der Prozessor wahrscheinlich noch.

- Prüfe mit top oder htop in einem separaten Terminal, ob ein python3-Prozess die CPU zu 100% auslastet.
- Wenn ja: **Lass ihn arbeiten.** Er füllt gerade den Cache.

Sobald der erste Durchlauf fertig ist, wird make top dank des Caches in unter 0.1 Sekunden antworten.

**Soll ich dir ein "Progress-Logging" in die API einbauen, damit du im API-Terminal siehst, bei wie viel Prozent der Berechnung der T520 gerade steht?**