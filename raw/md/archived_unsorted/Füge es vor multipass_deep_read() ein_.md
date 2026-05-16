import os

import json

# Pfad zur prepare_paths.json

PREPARE_FILE = "/K501GeminiNet/Node01/vault/prepare_paths.json"

# Prüfen, ob die Datei existiert

if not os.path.exists(PREPARE_FILE):

print(f"[INFO] {PREPARE_FILE} existiert nicht. Erstelle leeres JSON...")

# Stelle sicher, dass das Verzeichnis existiert

os.makedirs(os.path.dirname(PREPARE_FILE), exist_ok=True)

# Leere JSON-Datei erzeugen

with open(PREPARE_FILE, "w") as f:

json.dump({}, f, indent=4)

print(f"[INFO] {PREPARE_FILE} wurde erstellt.")

else:

print(f"[INFO] {PREPARE_FILE} existiert bereits. Weiter geht's...")