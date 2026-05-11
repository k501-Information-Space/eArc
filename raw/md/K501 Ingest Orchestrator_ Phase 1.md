**Ja, exakt.** Du überschreibst deinen bisherigen Runner vollständig mit diesem neuen Code.

Hier ist der genaue Ablauf für deinen "Go-Live" in Phase 1:

### 1. Code austauschen

Öffne die Datei in deinem Editor (z.B. mit nano, um VSCodium zu schonen):

Bash

nano ~/workspace/k501/runtime/ingest_runner.py  

Lösche den kompletten alten Inhalt, füge den kopierten **v3-Governor** Code ein und speichere die Datei ab (bei nano: Ctrl+O, Enter, Ctrl+X).

### 2. Monitor scharfschalten (Terminal 1)

Bevor du den Runner startest, öffne ein Terminal und starte den Monitor. So haben wir keinen blinden Fleck beim Anlaufen:

Bash

tail -f /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson | python3 -c '  
import json, sys, time  
start_t = time.time()  
count = 0  
prev_hash = None  
print("K501 Monitor: Phase 1 (60 FPS) bereit...")  
for line in sys.stdin:  
try:  
data = json.loads(line)  
count += 1  
curr_hash = data.get("hash")  
parent_hash = data.get("relations", {}).get("hash_prev")  
  
if prev_hash and parent_hash != prev_hash:  
f_id = data.get("id", "unknown")  
print(f"\n[!!!] CHAIN BREAK AT FRAME {f_id}")  
  
if count % 60 == 0:  
elapsed = time.time() - start_t  
fps = count / elapsed  
kbps = (count * 4096) / (elapsed * 1024)  
print(f"\rV: {fps:.2f} FPS | T: {kbps:.2f} KB/s | Frames: {count}", end="")  
  
prev_hash = curr_hash  
except: continue  
'  

### 3. Zündung (Terminal 2)

Wechsle in ein zweites Terminal und starte den aktualisierten Runner:

Bash

python3 ~/workspace/k501/runtime/ingest_runner.py  

**Was passiert dann?**

Der Runner wird kurz die 200 MB im Ledger scannen, deine saubere Schnittkante bei Chunk **15765** erkennen und sofort bei **15766** nahtlos mit 60 FPS weiterarbeiten. Der Monitor im anderen Fenster sollte fast sofort anspringen und dir die Live-Geschwindigkeit anzeigen.

**Bist du bereit? Sende mir einfach den ersten Output deines Monitors (die V: ... FPS Zeile), sobald er anläuft, damit wir prüfen können, ob der T520 den Takt sauber hält!**