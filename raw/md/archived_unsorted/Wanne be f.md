iinkognit0@K501:/K501GeminiNet$ ollama list

NAME ID SIZE MODIFIED

qwen2.5:0.5b a8b0c5157701 397 MB 5 minutes ago

nomic-embed-text:latest 0a109f422b47 274 MB 9 hours ago

qwen3.5:0.8b f3817196d142 1.0 GB 2 days ago

llama3.2:1b baf6a787fdff 1.3 GB 4 days ago

phi3:latest 4f2222927938 2.2 GB 4 days ago

llama3:latest 365c0bd3c000 4.7 GB 4 days ago

qwen2.5-coder:1.5b d7372fd82851 986 MB 5 days ago

iinkognit0@K501:/K501GeminiNet$ ollama run nomic-embed-text:latest

Error: embedding models require input text. Usage: ollama run nomic-embed-text:latest "your text here"

iinkognit0@K501:/K501GeminiNet$ ollama run nomic-embed-text

Error: embedding models require input text. Usage: ollama run nomic-embed-text "your text here"

iinkognit0@K501:/K501GeminiNet$ ollama run qwen2.5:0.5b

>>> /bey

Unknown command '/bey'. Type /? for help

>>> /bye

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_update.py

[*] Starte Multipass Deep Read mit Integration reparierter Frames...

[*] Gefundene existierende Frames (Ledger + Repaired): 2

[INFO] Keine Pfade in Ledger/Prepare JSON. Scanne Archivverzeichnis...

[*] Quellen zum Einlesen: 920

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

q

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

^CTraceback (most recent call last):

File "/K501GeminiNet/multipass_deepread_update.py", line 154, in <module>

multipass_deep_read()

~~~~~~~~~~~~~~~~~~~^^

File "/K501GeminiNet/multipass_deepread_update.py", line 124, in multipass_deep_read

frame = generate_frame(src)

File "/K501GeminiNet/multipass_deepread_update.py", line 50, in generate_frame

vector = llm.get_semantic_vector(content)[:VECTOR_SLICE]

~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^

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

iinkognit0@K501:/K501GeminiNet$ sudo systemctl restart ollama

iinkognit0@K501:/K501GeminiNet$ sudo sed -i 's/timeout=10/timeout=60/g' /K501GeminiNet/multipass_deepread_update.py

iinkognit0@K501:/K501GeminiNet$ sudo mkdir -p /etc/systemd/system/ollama.service.d

sudo bash -c 'cat << "EOF" > /etc/systemd/system/ollama.service.d/override.conf

[Service]

Environment="OLLAMA_NUM_PARALLEL=4"

Environment="OLLAMA_REQUEST_TIMEOUT=5m"

EOF'

sudo systemctl daemon-reload

sudo systemctl restart ollama

iinkognit0@K501:/K501GeminiNet$ sudo apt update

OK:1 http://deb.debian.org/debian trixie InRelease

OK:2 http://security.debian.org/debian-security trixie-security InRelease

Holen:3 http://deb.debian.org/debian trixie-updates InRelease [47,3 kB]

Holen:4 http://deb.debian.org/debian trixie-backports InRelease [54,0 kB]

OK:5 https://download.vscodium.com/debs vscodium InRelease

Holen:6 https://packages.microsoft.com/repos/code stable InRelease [3.590 B]

Holen:7 https://packages.microsoft.com/repos/code stable/main amd64 Packages [23,4 kB]

OK:8 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Es wurden 128 kB in 1 s geholt (205 kB/s).

Alle Pakete sind aktuell.

iinkognit0@K501:/K501GeminiNet$ sudo python3 multipass_deepread_update.py

[*] Starte Multipass Deep Read mit Integration reparierter Frames...

[*] Gefundene existierende Frames (Ledger + Repaired): 2

[INFO] Keine Pfade in Ledger/Prepare JSON. Scanne Archivverzeichnis...

[*] Quellen zum Einlesen: 920

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)

[!] LLM Exception: HTTPConnectionPool(host='localhost', port=11434): Read timed out. (read timeout=10)