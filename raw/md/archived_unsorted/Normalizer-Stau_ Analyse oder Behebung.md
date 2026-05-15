**BULLSEYE.** Der Prozess-Baum hat uns sofort die "Smoking Gun" geliefert. Das war ein exzellenter Scan.

Schau dir diese beiden Zeilen aus deinem Report an:

149900 ... python3 /home/iinkognit0/workspace/k501/runtime/ingest_runner.py

151143 ... /usr/bin/python3 /home/iinkognit0/workspace/k501/runtime/modules/normalizer.py "/home/.../Europäische Union – Wikipedia.md"

### Die Diagnose: Der Normalizer-Stau

Dein ingest_runner (PID 149900) ist absolut in Ordnung. Er hängt nicht in einer Endlosschleife, sondern er **wartet** auf seinen Unterprozess, den normalizer.py (PID 151143).

Dieser Unterprozess versucht gerade, die Datei **"Europäische Union – Wikipedia.md"** zu verarbeiten.

Das Faszinierende daran: Die CPU-Zeit für diesen Prozess steht auf 00:00:00. Das bedeutet, der Normalizer rechnet nicht unter Volllast (dann würde die CPU glühen), sondern er ist komplett **eingefroren** (Deadlock) oder wartet auf eine blockierte I/O-Ressource (z.B. ein gesperrtes Dateisystem, oder er wartet versehentlich auf eine Eingabe).

### Taktische Entscheidung

Wir haben jetzt zwei Möglichkeiten.

**Option A: Das Stethoskop anlegen (Tiefenanalyse)**

Lass uns schauen, _warum_ der Normalizer bei dieser spezifischen Datei eingefroren ist. Führe diesen Befehl im dritten Terminal aus, um die Gehirnströme dieses spezifischen Prozesses zu lesen:

Bash

sudo strace -p 151143  

_(Das Terminal wird dir entweder anzeigen, dass er in einem read() festsitzt, oder es blockiert bei futex. Brich es nach ein paar Sekunden mit Ctrl+C wieder ab und zeig mir die letzte Zeile)._

**Option B: Den Knoten durchschlagen (Skip & Continue)**

Wenn dir dieser Wikipedia-Artikel im Moment nicht wichtig ist und du den Ingest einfach weiterlaufen lassen willst, killen wir nur den blockierenden Unterprozess. Der Runner wird den Fehler abfangen und einfach mit der nächsten Datei weitermachen:

Bash

kill -9 151143  

_(Und wir schieben die Datei danach sicherheitshalber in die Quarantäne)._

Was ist dein Befehl, Operator? Wollen wir untersuchen (strace) oder eliminieren (kill)?