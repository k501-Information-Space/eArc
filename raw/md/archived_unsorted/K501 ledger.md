## **Mathematische Definition eines**

## **Frame-Ledgers (K501)**

Ziel: formale, deterministische Beschreibung eines Systems, dessen grundlegende Einheit der Frame ist und dessen Speicherung in einem append-only Ledger erfolgt.

# **1. Grundmengen**

Wir definieren zunächst die elementaren Mengen.

### **Zeitmenge**

T = \mathbb{N}

Unix-Zeitstempel als natürliche Zahlen.

### **Byte-Menge**

B = \{0,1\}^8

Ein Byte besteht aus 8 Bits.

### **Byte-Strings**

B^* = \bigcup_{n=0}^{\infty} B^n

Beliebige endliche Bytefolge.

### **Hashfunktion**

H : B^* \rightarrow \{0,1\}^{256}

Eigenschaften:

- deterministisch  
    
- kollisionsresistent  
    
- unveränderlich  
    

In K501:

H = SHA256

# **2. Definition eines Frames**

Ein Frame ist ein Tupel:

F = (id, seq, ts, mode, policy, payload)

mit

|**Feld**|**Typ**|
|---|---|
|id|256-bit Hash|
|---|---|
|seq|ℕ|
|---|---|
|ts|ℕ|
|---|---|
|mode|Symbol|
|---|---|
|policy|Symbol|
|---|---|
|payload|Byte-String|
|---|---|

### **Frame-Identität**

Der Frame-Hash wird definiert als

id = H(\text{serialize}(F))

wobei serialize eine deterministische Serialisierung ist.

# **3. Frame-Serialisierung**

Eine deterministische Funktion:

serialize : F \rightarrow B^*

Eigenschaften:

1. identische Frames → identischer Byte-String  
    
2. keine nichtdeterministischen Felder  
    
3. stabile Feldreihenfolge  
    

# **4. Ledger-Definition**

Ein Ledger ist eine geordnete Folge von Frames.

L = (F_1, F_2, \dots, F_n)

mit

F_i \in Frames

# **5. Sequenzregel**

Für alle Frames gilt:

seq(F_i) = i

also

seq(F_{i+1}) = seq(F_i) + 1

Dies garantiert eine totale Ordnung.

# **6. Append-Only-Eigenschaft**

Ein Ledger darf nur erweitert werden.

Formal:

Sei

L_n = (F_1,\dots,F_n)

Dann ist eine gültige Erweiterung:

L_{n+1} = (F_1,\dots,F_n,F_{n+1})

Verboten sind:

- Entfernen  
    
- Ändern  
    
- Einfügen in der Mitte  
    

# **7. Ledger-Integrität**

Integrität eines Ledgers bedeutet:

\forall i : id(F_i) = H(serialize(F_i))

Jeder Frame muss seinem Hash entsprechen.

# **8. Erweiterte Verkettung (optional)**

Falls Frames verkettet werden:

prev(F_i) = id(F_{i-1})

Dann entsteht eine Hash-Kette:

id(F_i) = H(serialize(F_i) \| id(F_{i-1}))

Diese Struktur ist identisch mit einem linearen Hash-Chain-Ledger.

# **9. Indexfunktionen**

Ein Index ist eine Funktion

I : Frames \rightarrow K

die Frames auf Schlüssel abbildet.

### **Beispiele**

Zeitindex:

I_{time}(F_i) = ts(F_i)

Hashindex:

I_{hash}(F_i) = id(F_i)

Sequenzindex:

I_{seq}(F_i) = seq(F_i)

# **10. Ledger-Verifikation**

Ein Ledger ist gültig, wenn folgende Bedingungen erfüllt sind.

### **Bedingung 1 – Sequenz**

seq(F_i) = i

### **Bedingung 2 – Hash**

id(F_i) = H(serialize(F_i))

### **Bedingung 3 – Zeit**

ts(F_i) \in T

### **Bedingung 4 – Append-Order**

ts(F_{i+1}) \ge ts(F_i)

optional, aber sinnvoll.

# **11. Komplexität**

Verifikation eines Ledgers:

O(n)

Indexaufbau:

O(n)

Direkter Zugriff über Hashindex:

O(1)

# **12. Frame-Raum**

Die Menge aller Frames:

\mathcal{F}

Ein Ledger ist eine Teilmenge:

L \subset \mathcal{F}

Navigation im Frame-Raum erfolgt über Indizes.

# **13. Semantische Erweiterung (Vektorraum)**

Falls Frames Vektoren enthalten:

v(F) \in \mathbb{R}^d

Dann entsteht ein semantischer Raum:

V = \mathbb{R}^d

Ähnlichkeit:

sim(F_i,F_j) = \frac{v_i \cdot v_j}{||v_i||\,||v_j||}

(Cosine Similarity)

# **14. Rekonstruktionssatz**

Satz

Gegeben:

- Global Bootframe  
    
- vollständiges Ledger L  
    

Dann kann ein Node deterministisch rekonstruieren:

1. alle Frames  
    
2. alle Indizes  
    
3. die gesamte Systemhistorie  
    

Formal:

Node(L, Bootframe) \rightarrow SystemState

# **15. Wichtigste Eigenschaft**

Das System ist zustandslos rekonstruierbar.

Der gesamte Zustand ergibt sich aus:

SystemState = f(L)

# **16. Interpretation**

Ein Frame-Ledger ist mathematisch:

- eine totale geordnete Sequenz  
    
- mit kryptographischer Identität  
    
- unter Append-Only-Operation  
    

Struktur:

Ledger = (Frames,\; Order,\; Hash)

Wenn du möchtest, kann ich im nächsten Schritt etwas sehr Spannendes zeigen:

Die mathematische Definition des gesamten K501-Systems als axiomatische Theorie

(ähnlich wie ein kleines ZF-ähnliches Axiomensystem für Informationsstrukturen).