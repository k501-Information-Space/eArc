## **Go — Ausführungsschritte (kompakt, direkt nutzbar)**

### **1) Tiny LLM Test starten (Node B)**

# Modell prüfen

ollama list

# Test-Run (1 Frame)

sed -n '1p' ~/k501_llm_test/in/batch_001.ndjson > ~/k501_llm_test/tmp/frame.json

ollama run qwen2:0.5b-instruct \

"$(cat ~/k501_llm_test/prompt.txt)

$(cat ~/k501_llm_test/tmp/frame.json)"

### **2) Batch laufen lassen (Outputs sammeln)**

: > ~/k501_llm_test/out/semantic_llm.ndjson

while IFS= read -r line; do

echo "$line" > ~/k501_llm_test/tmp/frame.json

ollama run qwen2:0.5b-instruct-q4 \

"$(cat ~/k501_llm_test/prompt.txt)

$(cat ~/k501_llm_test/tmp/frame.json)" \

>> ~/k501_llm_test/out/semantic_llm.ndjson

done < ~/k501_llm_test/in/batch_001.ndjson

### **3) Parallel: Gemini Fast (gleiche Frames)**

Vorgehen (manuell in Gemini):

- gleiche 5–10 Frames verwenden  
    
- exakt gleicher Prompt (kopieren)  
    
- Output speichern (Textfile)  
    

Datei anlegen:

nano ~/k501_llm_test/out/gemini_fast.txt

### **4) Strukturvergleich vorbereiten**

# erste 5 Outputs anzeigen

head -n 5 ~/k501_llm_test/out/semantic_llm.ndjson

# Anzahl prüfen

wc -l ~/k501_llm_test/out/semantic_llm.ndjson

### **5) Beobachtung (jetzt nur sammeln)**

Achte auf:

- JSON sauber?  
    
- Labels konsistent?  
    
- Länge stabil?  
    
- keine freien Texte?  
    

👉 nichts ändern, nur beobachten

## **Minimal-Flow**

frames → batch_001

→ qwen (lokal)

→ semantic_llm.ndjson

parallel:

frames → gemini fast → gemini_fast.txt

## **Stop-Kriterium**

- ~20–50 Outputs gesammelt  
    
- beide Modelle getestet  
    

👉 dann Pause → später Pro-Analyse

## **Wichtig**

- keine Optimierung jetzt  
    
- kein Prompt-Tuning jetzt  
    
- nur Daten erzeugen  
    

Wenn das durch ist:

→ sag „fertig“ → dann gehen wir in Vergleich + Strukturfixierung