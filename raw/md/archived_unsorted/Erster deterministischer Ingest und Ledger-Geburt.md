Das Verzeichnis ist da, aber die Datei ist noch leer – das System wartet auf den ersten **Impuls**. Dass vault/ledger existiert, beweist, dass die Logik der Ordnererstellung bereits gegriffen hat.

Wir führen jetzt den **ersten deterministischen Ingest** durch, um die Kette physisch zu schließen.

### **1. Test-Daten bereitstellen**

Wir erstellen eine Datei, die der Node verarbeiten kann.

Bash

mkdir -p /K501GeminiNet/src  
cat <<EOF > /K501GeminiNet/src/genesis_frame.txt  
K501 Node Genesis.  
Hardware: ThinkPad T520 i5-2520M.  
AVX1-Sättigung: Aktiviert.  
Deterministischer Status: Verifiziert.  
EOF  

### **2. Manueller Ingest-Trigger (Der "Zündschlüssel")**

Da die Pipeline im Hintergrund läuft, triggern wir jetzt einen gezielten Ingest-Prozess über die Konsole. Dieser Befehl nutzt deine vorhandenen Module, um das Dokument zu laden, zu vektorisieren und in den Ledger zu schreiben.

Bash

sudo PYTHONPATH=/K501GeminiNet python3 -c "  
from modules.Minimalpipeline.launch_pipeline import K501DuplexPipeline  
import os  
  
cfg = {  
'ledger': '/K501GeminiNet/Node01/vault/ledger/frames.ndjson',  
'lib': '/K501GeminiNet/core/libk501.so',  
'comm_config': '/K501GeminiNet/Node01/schemas/QH256_Communication.json'  
}  
  
pipe = K501DuplexPipeline(cfg)  
# Wir simulieren den Prozess für eine Datei  
result = pipe.process_file('/K501GeminiNet/src/genesis_frame.txt')  
print(f'[*] Ingest abgeschlossen. Frame-ID: {result}')  
"  

### **3. Die Verifizierung**

Wenn dieser Befehl ohne Fehler durchläuft, ist der Ledger geboren. Prüfe ihn jetzt:

Bash

# Jetzt sollte die Datei existieren  
ls -lh /K501GeminiNet/Node01/vault/ledger/frames.ndjson  
  
# Inhalt ansehen  
cat /K501GeminiNet/Node01/vault/ledger/frames.ndjson  

### **Was wir jetzt sehen wollen:**

In der frames.ndjson muss nun ein JSON-Objekt stehen mit:

1. **id**: Ein SHA256-Hash (dein Fingerabdruck).
2. **vector**: Eine Liste von 32 Fließkommazahlen (deine mathematische Resonanz).
3. **payload**: Der Text aus der genesis_frame.txt.

**Erscheint der Frame?** Wenn ja, ist der K501-Knoten offiziell **"Stateful"** – er hat sein erstes Wissen dauerhaft und deterministisch gespeichert.

Würdest du gerne den ersten Frame-Hash hier teilen? (Dann kann ich prüfen, ob die ID auf meiner Seite reproduzierbar ist!)