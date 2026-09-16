Damit ist die letzte technische Unsicherheit vor dem ersten direkten Binding-Proof beseitigt.

**V02-2B — Core Binding Boundary: PASS als Spezifikationsbasis**

Die Implementierung bestätigt exakt die bereits aus Header und Tests abgeleitete Struktur.

Der QH256-Core besitzt nur eine einzige kanonische Byte-Ausgabe:

`qh256_t`  
→ `qh256_serialize()`  
→ 32 Byte

Die Serialisierung ist explizit und unabhängig von der Speicherrepräsentation:

`T[0]` → Bytes `0..7`  
`T[1]` → Bytes `8..15`  
`F[0]` → Bytes `16..23`  
`F[1]` → Bytes `24..31`

jeweils Little Endian.

Das ist für K501 besonders wichtig: `sizeof(qh256_t)==32` wird zwar durch den bestehenden Test geprüft, aber **diese 32 Byte des C-Structs sind nicht die kanonische externe Darstellung**. Kanonisch ist ausschließlich das Ergebnis von `qh256_serialize()`. Damit bleibt die Architektur unabhängig von Padding, ABI und nativer Speicherordnung.

Noch wichtiger: Der Core enthält keinerlei AIONARC-spezifische Semantik. Er kennt nur:

`UNKNOWN / FALSE / TRUE / GUARD`

sowie die QH256-Algebra.

Damit ist die Trennung jetzt formal sauber:

`AIONARC`  
→ bestimmt Evidenz und Propositionen

`QH256 Core`  
→ kodiert und verarbeitet diese Propositionen

`AIONARC State Record`  
→ trägt Zustand plus Provenienz außerhalb der 256 Bit

Das bedeutet auch eine kleine Korrektur am bisherigen Candidate-Adapter. Diese Zeile:

```c
int k501_aionarc_qh256_from_propositions(
    const uint8_t *propositions,
    size_t proposition_count,
    k501_qh256_state_bytes_t *out_state
);
```

sollte **noch nicht** als endgültige öffentliche AIONARC-API gelten. Sie ist derzeit nur ein Platzhalter für die Integrationsgrenze. Denn wir haben noch nicht definiert, was ein `proposition` auf Byte-Ebene ist und wie viele Propositionen tatsächlich auf welche der 128 QH256-Zellen abgebildet werden.

Das ist V02-6, nicht V02-2.

Der nächste Schritt sollte deshalb jetzt ein **isolierter Direct-Core-Binding-Proof** sein, ohne AIONARC-Semantik.

Ziel:

```text
AIONARC integration test
        |
        +---- qh256.h
        |
        +---- qh256.c
        |
        v
known qh256_t
        |
        v
qh256_serialize()
        |
        v
exact 32-byte vector
        |
        v
qh256_deserialize()
        |
        v
qh256_equal()
```

Damit beweisen wir zunächst ausschließlich:

**„Die Pipeline kann den vorhandenen v2.0-Core direkt verwenden, ohne eine zweite QH256-Implementierung und ohne Übersetzungs- oder Serialisierungsdrift.“**

Ich würde dafür jetzt noch **keinen** vollständigen Pipeline-Code schreiben. Zuerst genügt ein kleiner Test unter:

`pipeline/K501_AIONARC_Pipeline_v0.2_Candidate/tests/integration/`

Der Test sollte mindestens exakt den bereits kanonischen `t9`-Vektor wiederholen. Das ist besonders stark, weil wir damit nicht einen neuen Test erfinden, sondern denselben Referenzvektor aus der v2.0-Validierung an der Integrationsgrenze erneut beweisen.

Der erwartete Nachweis lautet dann:

`V02-2B-DIRECT-CORE-BINDING = PASS`

Erst danach kommt:

`V02-3 Binary Object Record`

und anschließend:

`V02-4 Byte-Native Ingest`

Danach erst:

`V02-5 Record Hash`

`V02-6 Proposition Mapping`

`V02-7 vollständige QH256-Integration`

Das hält die Reihenfolge **PROOF_BEFORE_STATE** tatsächlich ein.

Ein weiterer Punkt ist jetzt eindeutig: Der bisherige Generator `K501-AIONARC_QH256_State_Generator_v0.1` darf in diesem v0.2-Pfad nicht heimlich als QH256-Core weiterleben. Er bleibt historische Evidence und Vergleichsmaterial. Der operative v0.2-Core ist ausschließlich die identifizierte v2.0-Implementierung.

**Aktueller Gate-State:**

`V02-1 PASS` — Core identifiziert  
`V02-2A PASS` — API identifiziert  
`V02-2B PASS` — Integrationsgrenze technisch bestimmt  
`V02-2C OPEN` — tatsächlicher Compile-/Runtime-Binding-Proof  
`V02-3 OPEN` — Binary Object Record  
`V02-4 OPEN` — Byte-Native Ingest  
`V02-5 OPEN` — Record Hash  
`V02-6 OPEN` — AIONARC → QH256 Mapping

Als nächsten konkreten Schritt würde ich jetzt den **V02-2C Direct-Core-Binding-Test** erzeugen und anschließend gegen den unveränderten `tests/validation/v2.0/qh256.c` kompilieren.