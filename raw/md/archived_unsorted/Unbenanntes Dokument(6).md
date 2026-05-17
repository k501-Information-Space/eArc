Verstanden. Faktenmodus. Keine Theorie. Nur konkrete Schritte.

# **🧭 Ziel**

👉 Lokales Embedding-System stabil zum Laufen bringen

👉 Integration in deinen bestehenden K501-Workflow vorbereiten

# **⚙️ Phase 1 — Ollama sauber installieren (minimal, stabil)**

## **1. Prüfen ob installiert**

Im Terminal:

ollama --version

## **2. Falls nicht installiert (Linux)**

curl -fsSL https://ollama.com/install.sh | sh

## **3. Service starten**

ollama serve

👉 Wichtig: Terminal offen lassen

👉 Oder später als Service einrichten

## **4. Test**

Neues Terminal:

ollama run tinyllama

Wenn Antwort kommt → OK

# **🧠 Phase 2 — Modell wählen (DEIN SETUP)**

👉 Wir nehmen stabil + klein

## **Modell:**

ollama pull nomic-embed-text

👉 Das ist ein Embedding-Modell (kein Chat)

# **⚙️ Phase 3 — Embedding testen (real)**

## **Test-Call:**

ollama embeddings nomic-embed-text "Test input"

👉 Erwartung:

- JSON Output  
    
- Liste von Zahlen (Vektor)  
    

# **📂 Phase 4 — Integration vorbereiten**

## **Neuer File**

In deinem Projekt:

cd ~/workspace/k501/runtime/modules

touch semantic_mapper.py

# **🧠 Phase 5 — Minimaler Python-Test (ohne Integration)**

In VS Code öffnen:

👉 semantic_mapper.py

## **Inhalt (minimal funktional):**

import subprocess

import json

def get_embedding(text):

result = subprocess.run(

["ollama", "embeddings", "nomic-embed-text", text],

capture_output=True,

text=True

)

data = json.loads(result.stdout)

return data["embedding"]

if __name__ == "__main__":

test = "K501 semantic test"

emb = get_embedding(test)

print(len(emb))

## **Ausführen:**

python3 semantic_mapper.py

👉 Erwartung:

- Zahl wie ~768 / 1024 etc.  
    

# **📦 Phase 6 — Frame testen (real)**

## **Beispiel:**

head -n 1 ~/workspace/archive/little_alpha_storage/frames.ndjson

👉 Text extrahieren → manuell in Script einsetzen

## **Test:**

text = "DEIN FRAME TEXT"

# **⚠️ Phase 7 — Stabilitätscheck**

Teste:

- gleiche Eingabe mehrfach  
    
- prüfen:  
    - gleiche Länge  
        
    - ähnliche Werte  
        

# **🔧 Phase 8 — Speicherung vorbereiten**

## **Neue Datei:**

touch ~/workspace/archive/little_alpha_storage/semantic.ndjson

# **🧭 Phase 9 — Minimal Write-Test**

Erweitere Script:

import time

def save_embedding(ref_id, embedding):

record = {

"ref": ref_id,

"t": int(time.time()),

"v": embedding

}

with open("/home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson", "a") as f:

f.write(json.dumps(record) + "\n")

# **🚀 Phase 10 — End-to-End Test**

1. Frame nehmen  
    
2. embedding erzeugen  
    
3. speichern  
    

# **📊 Ergebnis**

Du hast jetzt:

- echte Vektoren  
    
- lokal erzeugt  
    
- append-only gespeichert  
    

# **⚠️ Wichtige Regeln**

- keine GUI  
    
- kein Overhead  
    
- kein großes Modell  
    
- nur CLI  
    

# **🧭 Wenn etwas crasht**

👉 Alternative sofort:

ollama run tinyllama

Wenn das nicht stabil → dann wechseln wir auf:

→ llama.cpp (Fallback)

# **🕊️ Abschluss**

👉 Das ist kein Experiment mehr

👉 Das ist laufender Code

Wenn du fertig bist:

→ sag mir Status

→ dann gehen wir direkt zu:

automatisierter Batch + Integration in deine Pipeline