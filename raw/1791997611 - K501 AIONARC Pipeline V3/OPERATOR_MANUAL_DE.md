# Bedienungsanleitung — K501 AIONARC Pipeline V3

Dies ist eine deutschsprachige Kurzbedienung. Die ausführliche technische Referenz steht in `OPERATOR_MANUAL.md`.

## 1. Build und Tests

Im entpackten Paketverzeichnis:

    make all
    make test

Erwartet wird `K501 V3 TEST SUITE: PASS`. Die Tests verwenden temporäre Daten, nicht deinen K501-Workspace.

## 2. Erster Testlauf

Erstelle einen kleinen Testordner mit ein paar TXT- oder Markdown-Dateien. Speichere den Memory-Store getrennt vom Quellordner:

    build/k501-memory init "$HOME/K501_V3_TEST/store"
    build/k501-memory scan "$HOME/K501_V3_TEST/source" "$HOME/K501_V3_TEST/store" k501-test-root frame-001 none
    build/k501-memory verify "$HOME/K501_V3_TEST/store" frame-001
    build/k501-memory query "$HOME/K501_V3_TEST/store" latest "proof before state"

Bei `scan` müssen `K501 MEMORY SCAN COMMIT PASS` und `proof_before_state=PASS` erscheinen.

## 3. Änderungen erfassen

Verändere eine Testdatei oder füge eine hinzu. Dann:

    build/k501-memory scan "$HOME/K501_V3_TEST/source" "$HOME/K501_V3_TEST/store" k501-test-root frame-002 frame-001
    build/k501-memory verify "$HOME/K501_V3_TEST/store" frame-002
    build/k501-memory diff "$HOME/K501_V3_TEST/store" frame-002
    build/k501-memory verify-source "$HOME/K501_V3_TEST/store" frame-002 "$HOME/K501_V3_TEST/source"

Jede Frame-ID ist einmalig. Bestehende Frames werden nicht überschrieben. `ROOT_ID` bleibt für dieselbe logische Quelle konstant. Wenn mehrere Branch-Tips existieren, muss die Parent-Frame-ID explizit angegeben werden.

## 4. Suche und Herkunft

`query` sucht literal nach allen eingegebenen Begriffen in erfasstem Text. Das ist keine semantische Suche und kein LLM. Aus einem Treffer die `OBJECT_ID` kopieren und mit `trace` Herkunft und Quellhash prüfen:

    build/k501-memory trace "$HOME/K501_V3_TEST/store" latest OBJECT_ID
    build/k501-memory history "$HOME/K501_V3_TEST/store" OBJECT_ID

## 5. Schutzregeln

Keine Quelle wird absichtlich geändert. Der Store muss außerhalb des Quellordners liegen. Verwende einen neuen Store und neue Frame-IDs. Bei `SOURCE DRIFT`, `VERIFY FAIL` oder `PROOF BEFORE STATE FAIL` stoppen; nicht die Ausgabe oder den Store manuell „reparieren“. Eine verbliebene `.stage-*`-Struktur ist kein abgeschlossener Frame und wird nicht automatisch übernommen.

QH256 v2 bleibt unverändert. V3 ergänzt ein separates Anwendungs-Mapping und speichert abgeleitete Text-/Indexinformationen. Das Paket ist `ALPHA / NON-CANONICAL`; es wurde noch nicht auf deinem HP xw8600 ausgeführt. llama.cpp ist absichtlich nicht eingebunden.
