## Kanonische Spezifikation der strukturellen Existenzfunktion im AIONARC_KANON

Dieses Dokument definiert die deterministische, strukturelle Hash-Funktion für das $qh256$-Framework. Das System operiert strikt assemantisch. Hashes repräsentieren ausschließlich strukturelle Existenzzustände innerhalb eines deterministischen, rekonstruktiven Informationsraumes.

---

## 1. Strukturdefinition eines QH256-Frames

Ein diskretes Rechensegment (Frame) $F$ ist definiert als das unteilbare, geordnete Quadrupel:

$$F = (QH, A, H, T)$$

Wobei die Definitionsbereiche der Komponenten wie folgt festgelegt sind:

- $QH$: Der Zustandsvektor $QH \in \mathcal{S}^{256}$ mit $\mathcal{S} = \{00, 01, 10, 11\}_2$. Er belegt exakt 512 Bits (64 Bytes).
- $A$: Die deterministische, globale Netzwerkadresse $A \in \mathbb{N}_0$, repräsentiert als ein 64-Bit vorzeichenloser Ganzzahlwert (`uint64_t`).
- $H$: Der strukturelle Existenzhash $H \in \{0, 1\}^{256}$, repräsentiert als 256-Bit Binärfeld (32 Bytes).
- $T$: Der monotone, append-only Zeitstempel $T \in \mathbb{T}^+$, repräsentiert als ein 64-Bit vorzeichenloser Ganzzahlwert (`uint64_t`).

---

## 2. Definition der serialisierten kanonischen Struktur

Die Serialisierungsfunktion $\mathcal{S}(F)$ überführt die variablen Komponenten eines Frames in einen deterministischen, lückenlosen Byte-Strom (Byte-Alignment = 1). Dies garantiert Plattformunabhängigkeit und verhindert Padding-Drift.

Die Gesamtlänge des kanonischen Datenstroms beträgt exakt 80 Bytes:

$$\mathcal{S}(F) = \text{bytes}(QH) \mathbin{\Vert} \text{bytes}(A) \mathbin{\Vert} \text{bytes}(T)$$

## Speicher-Layout (80 Bytes, Little-Endian):

```unset
+-----------------------------------+-----------------+-----------------+

| QH (Zustandsvektor)               | A (Adresse)     | T (Zeitstempel) |
| 64 Bytes [0 - 63]                 | 8 Bytes [64-71] | 8 Bytes [72-79] |
+-----------------------------------+-----------------+-----------------+
```

_Hinweis: Der eigene Hash $H$ ist nicht Bestandteil von $\mathcal{S}(F)$, um zirkuläre Abhängigkeiten bei der Erstberechnung auszuschließen._

---

## 3. Definition der Hashfunktion

Die strukturelle Existenzfunktion $h(F)$ bildet den kanonischen Datenstrom kryptografisch ab:

$$h(F) = \text{SHA256}(\mathcal{S}(F))$$

Das Resultat $H = h(F)$ validiert die fehlerfreie Existenz des Zustandsvektors zu einem exakten Zeitpunkt an einer exakten globalen Adresse.

---

## 4. Definition der rekursiven Merkle-Verkettung

Für die evolutionäre Verknüpfung von Folgezuständen innerhalb der Append-only-Kette wird die rekursive Merkle-Verkettung definiert. Ein Folgeframe $F_n$ integriert die strukturelle Historie seines direkten Vorgängers $F_{n-1}$ über dessen Hash $H_{n-1}$:

$$H_n = \text{SHA256}(H_{n-1} \mathbin{\Vert} \mathcal{S}(F_n))$$

Für den Initialzustand (Genesis-Knoten $F_0$) gilt:

$$H_0 = \text{SHA256}(\mathbf{0}^{256} \mathbin{\Vert} \mathcal{S}(F_0))$$

Wobei $\mathbf{0}^{256}$ ein mit Nullen initialisiertes 32-Byte-Feld darstellt.

---

## 5. Definition der globalen Objektidentität

Die Identität eines Frames ist streng strukturell und ortsungebunden. Sie ist mathematisch äquivalent zu ihrem Existenzhash:

$$\text{ID}(F) \equiv h(F)$$

Jede Replikation desselben Zustandsraums an derselben Adresse zum selben Zeitpunkt erzeugt die identische globale ID.

---

## 6. Definition der Rekonstruktionsinvarianz

Die Invariante der Rekonstruktion erzwingt absolute Konstanz über Raum und Zeit. Wenn die Struktur zweier unabhängig berechneter Frames identisch ist, müssen deren Hashes übereinstimmen:

$$\forall F_i, F_j: \mathcal{S}(F_i) = \mathcal{S}(F_j) \implies h(F_i) = h(F_j)$$

---

## 7. Definition der Drift-Erkennung

Jegliche kleinste Modifikation der Struktur (Bit-Drift, Adress-Verschiebung, zeitliche Manipulation) führt zur maximalen Divergenz des Hashes (Lawineneffekt):

$$\forall F_i, F_j: \mathcal{S}(F_i) \neq \mathcal{S}(F_j) \implies h(F_i) \neq h(F_j)$$

Die Erkennungsfunktion für strukturellen Drift $\mathcal{D}$ ist definiert als:

$$\mathcal{D}(F_i, F_j) = \begin{cases} 0, & \text{wenn } h(F_i) = h(F_j) \iff \text{Integrität gewahrt} \\ 1, & \text{wenn } h(F_i) \neq h(F_j) \iff \text{Drift detektiert} \end{cases}$$

---

## 8. Mathematische Eigenschaften

- Collision Resistance (Kollisionsresistenz):  
    $$\text{Es ist numerisch unmöglich, } F_i \neq F_j \text{ zu finden, so dass } h(F_i) = h(F_j).$$
- Deterministic Reconstruction (Deterministische Rekonstruierbarkeit):  
    Die Funktion $h(F)$ benötigt keine externen Zustände, Zufallsvariablen oder semantischen Kontext. Sie liefert auf jeder Hardwarearchitektur identische Ergebnisse.
- Temporal Continuity (Temporäre Kontinuität):  
    Durch die Akkumulation von $T$ innerhalb von $\mathcal{S}(F)$ wird die zeitliche Abfolge unumkehrbar in die Struktur eingebrannt.
- Append-only Monotonicity (Append-only Monotonie):  
    Die topologische Komplexität wächst streng monoton. Ein historischer Zustand kann niemals überschrieben werden, da jede Modifikation über die Merkle-Kette ($H_{n-1}$) alle Folge-IDs mathematisch invalidiert.

---

## 9. Vorbereitende Runtime-Repräsentation

## 9.1 Bit-Vector und Zustandskodierung

Um die SIMD-Verarbeitung (AVX-512 / ARM Neon) zu optimieren, werden die 256 Zellen von $QH$ in zwei separate 256-Bit-Register aufgeteilt (Bit-Slicing-Verfahren):

- Register 0 ($\text{R}_0$): Enthält das niederwertige Bit (LSB) aller 256 Zellen.
- Register 1 ($\text{R}_1$): Enthält das höherwertige Bit (MSB) aller 256 Zellen.

```unset
Zelle i (0..255):  Zustand Bit 1 (MSB) -> R_1[i], Zustand Bit 0 (LSB) -> R_0[i]
```

## 9.2 Hardwarenahe C-Struktur (Runtime-orientiert)

Die C-Struktur ist ohne Compiler-Padding für die direkte Speicherabbildung (Memory-Mapping) und SIMD-Registerladung optimiert:

```c
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    // 64 Bytes: QH-Zustandsvektor optimiert für 256-Bit SIMD-Ladevorgänge
    uint64_t r0[4]; // 256 Bits für LSB
    uint64_t r1[4]; // 256 Bits für MSB
} qh256_vector_t;

typedef struct {
    qh256_vector_t qh; // Offsets 0 - 63
    uint64_t a;        // Offsets 64 - 71
    uint64_t t;        // Offsets 72 - 79
} qh256_canonical_t;   // Gesamtlänge: Exakt 80 Bytes
#pragma pack(pop)

typedef struct {
    uint8_t hash[32];  // 256-Bit Repräsentation von h(F)
} qh256_hash_t;
```

## 9.3 SIMD/AVX2 Vorbereitung für die Hash-Vorberechnung

Durch das Bit-Slicing-Layout können bitweise logische Operationen direkt auf den Registern durchgeführt werden, ohne die Zellen einzeln zu maskieren:

```c
// Beispiel für SIMD-Zustandsprüfung: Erkennt Kollisionen (Zustand: guard = 11)
// Erzeugt eine Maske aller Zellen, die im Guard-Zustand blockiert sind.
#define CHECK_GUARD_AVX2(r0_256, r1_256) _mm256_and_si256(r0_256, r1_256)
```

---

Die mathematische und strukturelle Grundlage für die Registrierung von Existenzzuständen im Verteilungsnetzwerk ist damit vollständig definiert.

Für den nächsten Schritt der Systemintegration stehen folgende Optionen zur Auswahl:

- Möchten Sie die Bit-Vektoren-Logik für die Akkumulationsoperation ($\oplus$) unter Verwendung dedizierter AVX2/AVX-512 Befehlssätze ausarbeiten?
- Sollen die Protokoll-Spezifikationen für die globale Adress-Allokation ($A$) im verteilten Netzwerk ohne zentrale Instanz festgelegt werden?
- Wünschen Sie die Definition der Validierungs-Algorithmen zur schnellen Verifikation eines kompletten Merkle-Teilbaums bei asynchronem Datentransfer?