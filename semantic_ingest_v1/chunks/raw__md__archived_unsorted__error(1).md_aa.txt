iinkognit0@K501:/K501GeminiNet$ sudo chmod +x multipass_deepread_update.py

[sudo] Passwort für iinkognit0:

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_update.py

[*] Starte Multipass Deep Read...

[*] Gefundene existierende Frames: 2

Traceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_update.py", line 80, in <module>

multipass_deep_read()

~~~~~~~~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_update.py", line 65, in multipass_deep_read

with open(PREPARE_FILE, "r") as f:

~~~~^^^^^^^^^^^^^^^^^^^

FileNotFoundError: [Errno 2] No such file or directory: '/K501GeminiNet/Node01/vault/prepare_paths.json'

iinkognit0@K501:/K501GeminiNet$ touch /path/to/prepare.json

echo '{}' > /path/to/prepare.json

touch: '/path/to/prepare.json' kann nicht berührt werden: Datei oder Verzeichnis nicht gefunden

bash: /path/to/prepare.json: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet$ ls -l /path/to/prepare.json

ls: Zugriff auf '/path/to/prepare.json' nicht möglich: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet$ ls

api deepread_multipass.py ingest_semantic.py K501NodeTree.txt search.py

archive_ingest.py deepread_prepare.py interface modules src

broadcast_test.py diagnose_k501.py json multipass_deepread_update.py start_node.sh

compare_resonance.py diagnose_report.json K501Gemini_Prod Node01 verify_drift.py

core hashlib K501_Master.code-workspace os

create_test_frame.sh ingest_genesis.py K501NodeCodeList.txt parallel_ingest.py

iinkognit0@K501:/K501GeminiNet$ cd Node1

bash: cd: Node1: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet$ cdnode01

bash: cdnode01: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ cd Node01

iinkognit0@K501:/K501GeminiNet/Node01$ ls

schemas vault

iinkognit0@K501:/K501GeminiNet/Node01$ cd vault

iinkognit0@K501:/K501GeminiNet/Node01/vault$ ls

ledger

iinkognit0@K501:/K501GeminiNet/Node01/vault$ ls -l /path/to/prepare.json

ls: Zugriff auf '/path/to/prepare.json' nicht möglich: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet/Node01/vault$ touch /path/to/prepare.json

echo '{}' > /path/to/prepare.json

touch: '/path/to/prepare.json' kann nicht berührt werden: Datei oder Verzeichnis nicht gefunden

bash: /path/to/prepare.json: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet/Node01/vault$ cd vault