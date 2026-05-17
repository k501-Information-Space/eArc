iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_autoscale.py

[sudo] Passwort für iinkognit0:

[*] Ollama Self-Healing Routine gestartet

[!] Port 11434 blockiert, Prozess killen...

[*] Killing process 2938 on port 11434

[*] Start Ollama Service...

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 1

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 2

^CTraceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 147, in <module>

if not self_healing():

~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 77, in self_healing

time.sleep(5)

~~~~~~~~~~^^^

KeyboardInterrupt

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_autoscale.py

[*] Ollama Self-Healing Routine gestartet

[!] Port 11434 blockiert, Prozess killen...

[*] Killing process 3395 on port 11434

[*] Start Ollama Service...

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 1

^CTraceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 147, in <module>

if not self_healing():

~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 77, in self_healing

time.sleep(5)

~~~~~~~~~~^^^

KeyboardInterrupt

iinkognit0@K501:/K501GeminiNet$ sudo python3 deepread_multipass.py

[*] Starte Deep-Read Multipass...

[*] Fertig. Deep-Read Multipass abgeschlossen.

[*] Deep-Read Ledger gespeichert unter: /K501GeminiNet/Node01/vault/ledger/frames_deepread.ndjson

[*] Frames verarbeitet: 0

iinkognit0@K501:/K501GeminiNet$ multipass_deepread_update.py

bash: multipass_deepread_update.py: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_update.py

[*] Starte Multipass Deep Read mit Integration reparierter Frames...

[*] Gefundene existierende Frames (Ledger + Repaired): 5

[*] Quellen zum Einlesen: 920

DeepRead Multipass: 0%| | 0/920 [00:00<?, ?Frame/s][!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

DeepRead Multipass: 0%| | 0/920 [00:10<?, ?Frame/s]

Traceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_update.py", line 130, in <module>

multipass_deep_read()

~~~~~~~~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_update.py", line 117, in multipass_deep_read

out_f.write(json.dumps(frame) + "\n")

~~~~~~~~~~^^^^^^^

File "/usr/lib/python3.13/json/__init__.py", line 231, in dumps

return _default_encoder.encode(obj)

~~~~~~~~~~~~~~~~~~~~~~~^^^^^

File "/usr/lib/python3.13/json/encoder.py", line 200, in encode

chunks = self.iterencode(o, _one_shot=True)

File "/usr/lib/python3.13/json/encoder.py", line 261, in iterencode

return _iterencode(o, 0)

File "/usr/lib/python3.13/json/encoder.py", line 180, in default

raise TypeError(f'Object of type {o.__class__.__name__} '

f'is not JSON serializable')

TypeError: Object of type ndarray is not JSON serializable

iinkognit0@K501:/K501GeminiNet$ sudo python3 archive_ingest.py

[*] Safe-Ingest: Verarbeite 915 Dateien...

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

^CTraceback (most recent call last):

File "/K501GeminiNet/archive_ingest.py", line 43, in <module>

run_safe_ingest()

~~~~~~~~~~~~~~~^^

File "/K501GeminiNet/archive_ingest.py", line 29, in run_safe_ingest

vector = llm.get_semantic_vector(content_sample)

File "/K501GeminiNet/modules/QH256_LLM/launch_llm.py", line 21, in get_semantic_vector

response = requests.post(self.base_url, json=payload, timeout=10)

File "/usr/lib/python3/dist-packages/requests/api.py", line 115, in post

return request("post", url, data=data, json=json, **kwargs)

File "/usr/lib/python3/dist-packages/requests/api.py", line 59, in request

return session.request(method=method, url=url, **kwargs)

~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

File "/usr/lib/python3/dist-packages/requests/sessions.py", line 589, in request

resp = self.send(prep, **send_kwargs)

File "/usr/lib/python3/dist-packages/requests/sessions.py", line 703, in send

r = adapter.send(request, **kwargs)

File "/usr/lib/python3/dist-packages/requests/adapters.py", line 667, in send

resp = conn.urlopen(

method=request.method,

...<9 lines>...

chunked=chunked,

)

File "/usr/lib/python3/dist-packages/urllib3/connectionpool.py", line 787, in urlopen

response = self._make_request(

conn,

...<10 lines>...

**response_kw,

)

File "/usr/lib/python3/dist-packages/urllib3/connectionpool.py", line 534, in _make_request

response = conn.getresponse()

File "/usr/lib/python3/dist-packages/urllib3/connection.py", line 516, in getresponse

httplib_response = super().getresponse()

File "/usr/lib/python3.13/http/client.py", line 1430, in getresponse

response.begin()

~~~~~~~~~~~~~~^^

File "/usr/lib/python3.13/http/client.py", line 331, in begin

version, status, reason = self._read_status()

~~~~~~~~~~~~~~~~~^^

File "/usr/lib/python3.13/http/client.py", line 292, in _read_status

line = str(self.fp.readline(_MAXLINE + 1), "iso-8859-1")

~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^

File "/usr/lib/python3.13/socket.py", line 719, in readinto

return self._sock.recv_into(b)

~~~~~~~~~~~~~~~~~~~~^^^

KeyboardInterrupt

iinkognit0@K501:/K501GeminiNet$ sudo python3 ingest_genesis.py

[*] Initialisiere QH256 Core...

[*] Erzeuge 32-dim Signatur (Deterministic Dummy)...

[*] Generiere Frame...

[*] Committe in den Ledger...

[SUCCESS] State manifestiert!

Frame-ID: 730e5da0cf54d28f61693b2338ef7d15d6207d454f6eb2d2a5eb4ade2613b546

Ledger-Pfad: /K501GeminiNet/Node01/vault/ledger/frames.ndjson

iinkognit0@K501:/K501GeminiNet$ sudo python3 ingest_semantic.py

[*] Initialisiere K501 Komponenten...

[!] Keine Quelldatei gefunden.

iinkognit0@K501:/K501GeminiNet$ sudo python3 parallel_ingest.py

=== [K501 MASS INGEST: STARTING HARVEST] ===

[*] 920 Dateien identifiziert.

[*] Starte Parallel-Vektorisierung (Worker: 4)...

[>] 50/920 Frames manifestiert...

[>] 100/920 Frames manifestiert...

[>] 150/920 Frames manifestiert...

[>] 200/920 Frames manifestiert...

[>] 250/920 Frames manifestiert...

[>] 300/920 Frames manifestiert...

[>] 350/920 Frames manifestiert...

[>] 400/920 Frames manifestiert...

[>] 450/920 Frames manifestiert...

[>] 500/920 Frames manifestiert...

[>] 550/920 Frames manifestiert...

[>] 600/920 Frames manifestiert...

[>] 650/920 Frames manifestiert...

[>] 700/920 Frames manifestiert...

[>] 750/920 Frames manifestiert...

[>] 800/920 Frames manifestiert...

[>] 850/920 Frames manifestiert...

[>] 900/920 Frames manifestiert...

--- [HARVEST COMPLETED] ---

[*] Frames manifestiert: 920

[*] Gesamtzeit: 23.24s (Schnitt: 0.03s pro Frame)

[*] Performance: 39.58 f/s

iinkognit0@K501:/K501GeminiNet$ sudo python3 search.py

Usage: search.py "suchbegriff"

iinkognit0@K501:/K501GeminiNet$ sudo python3 search.py test

[*] STARTE SEMANTISCHE RESONANZ-ANALYSE

[*] Query: "test"

--- [ERGEBNISSE AUS DEM GITTER] ---

Resonanz: 0.6700 | ID: e8c4a28451

Inhalt: K501 Sentinel-Test Fragment

---------------------------

Timestamp: Fr 13. Mär 15:39:15 CET 2026

Node: NODE_K501_T520_01

...

----------------------------------------

Resonanz: 0.6528 | ID: 5d619de2d5

Inhalt: K501 System-Axiom: Die Hardware ist der Anker, die Logik ist die Kette.

...

----------------------------------------

Resonanz: 0.0805 | ID: 730e5da0cf

Inhalt: K501 Genesis: ThinkPad T520 AVX-Saturated State....

----------------------------------------

iinkognit0@K501:/K501GeminiNet$ sudo python3 search.py kanon

[*] STARTE SEMANTISCHE RESONANZ-ANALYSE

[*] Query: "kanon"

--- [ERGEBNISSE AUS DEM GITTER] ---

Resonanz: 0.6816 | ID: 5d619de2d5

Inhalt: K501 System-Axiom: Die Hardware ist der Anker, die Logik ist die Kette.

...

----------------------------------------

Resonanz: 0.6281 | ID: e8c4a28451

Inhalt: K501 Sentinel-Test Fragment

---------------------------

Timestamp: Fr 13. Mär 15:39:15 CET 2026

Node: NODE_K501_T520_01

...

----------------------------------------

Resonanz: 0.2001 | ID: 730e5da0cf

Inhalt: K501 Genesis: ThinkPad T520 AVX-Saturated State....

----------------------------------------

iinkognit0@K501:/K501GeminiNet$ sudo python3 search.py k501

[*] STARTE SEMANTISCHE RESONANZ-ANALYSE

[*] Query: "k501"

--- [ERGEBNISSE AUS DEM GITTER] ---

Resonanz: 0.6208 | ID: 5d619de2d5

Inhalt: K501 System-Axiom: Die Hardware ist der Anker, die Logik ist die Kette.

...

----------------------------------------

Resonanz: 0.5981 | ID: e8c4a28451

Inhalt: K501 Sentinel-Test Fragment

---------------------------

Timestamp: Fr 13. Mär 15:39:15 CET 2026

Node: NODE_K501_T520_01

...

----------------------------------------

Resonanz: 0.1263 | ID: 730e5da0cf

Inhalt: K501 Genesis: ThinkPad T520 AVX-Saturated State....

----------------------------------------

iinkognit0@K501:/K501GeminiNet$ sudo python3 verify_drift.py

Speicherzugriffsfehler

iinkognit0@K501:/K501GeminiNet$ sudo python3 deepread_prepare.py

[*] Starte Pfad-Integritäts- und Deep-Read-Vorbereitung...

[*] Fertig. Frames geprüft: 2

[*] Fehlende Dateien: 0

[*] Deep-Read-ready Frames: 0

[*] Report gespeichert unter: /K501GeminiNet/Node01/vault/ledger/deepread_prepare_report.json

iinkognit0@K501:/K501GeminiNet$ sudo python3 compare_resonance.py

═════════════════════════════════════════════

RESODATA: 5d619de2 <---> e8c4a284

SCORE: 0.8758

═════════════════════════════════════════════

[STATUS] Starke semantische Kopplung erkannt.

iinkognit0@K501:/K501GeminiNet$ sudo python3 broadcast_test.py

[*] Lade letzten Frame für Broadcast...

[*] Sende Signal für Frame 730e5da0...

═════════════════════════════════════════════

[SUCCESS] SIGNAL INS GITTER EMITTIERT!

═════════════════════════════════════════════

Prüfe jetzt dein Mastodon-Profil im Browser.

iinkognit0@K501:/K501GeminiNet$ sudo python3 ingest_semantic.py

[*] Initialisiere K501 Komponenten...

[!] Keine Quelldatei gefunden.

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_update.py

[*] Starte Multipass Deep Read mit Integration reparierter Frames...

[*] Gefundene existierende Frames (Ledger + Repaired): 6

[*] Quellen zum Einlesen: 920

DeepRead Multipass: 0%| | 0/920 [00:00<?, ?Frame/s][!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

DeepRead Multipass: 0%| | 0/920 [00:10<?, ?Frame/s]

Traceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_update.py", line 130, in <module>

multipass_deep_read()

~~~~~~~~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_update.py", line 117, in multipass_deep_read

out_f.write(json.dumps(frame) + "\n")

~~~~~~~~~~^^^^^^^

File "/usr/lib/python3.13/json/__init__.py", line 231, in dumps

return _default_encoder.encode(obj)

~~~~~~~~~~~~~~~~~~~~~~~^^^^^

File "/usr/lib/python3.13/json/encoder.py", line 200, in encode

chunks = self.iterencode(o, _one_shot=True)

File "/usr/lib/python3.13/json/encoder.py", line 261, in iterencode

return _iterencode(o, 0)

File "/usr/lib/python3.13/json/encoder.py", line 180, in default

raise TypeError(f'Object of type {o.__class__.__name__} '

f'is not JSON serializable')

TypeError: Object of type ndarray is not JSON serializable

iinkognit0@K501:/K501GeminiNet$ sudo python3 deepread_multipass.py

[*] Starte Deep-Read Multipass...

[*] Fertig. Deep-Read Multipass abgeschlossen.

[*] Deep-Read Ledger gespeichert unter: /K501GeminiNet/Node01/vault/ledger/frames_deepread.ndjson

[*] Frames verarbeitet: 0

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_autoscale.py

[*] Ollama Self-Healing Routine gestartet

[!] Port 11434 blockiert, Prozess killen...

[*] Killing process 3610 on port 11434

[*] Start Ollama Service...

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 1

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 2

[!] Embedding-Test fehlgeschlagen, Neustart Versuch 3

^CTraceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 147, in <module>

if not self_healing():

~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_autoscale.py", line 77, in self_healing

time.sleep(5)

~~~~~~~~~~^^^

KeyboardInterrupt

iinkognit0@K501:/K501GeminiNet$ sudo python3 diagnose_k501.py

[*] Starte K501 GeminiNet Diagnose...

[*] Scanne Dateisystem...

[*] Analysiere Ledger...

[*] Diagnose abgeschlossen. Report geschrieben: /K501GeminiNet/diagnose_report.json

iinkognit0@K501:/K501GeminiNet$