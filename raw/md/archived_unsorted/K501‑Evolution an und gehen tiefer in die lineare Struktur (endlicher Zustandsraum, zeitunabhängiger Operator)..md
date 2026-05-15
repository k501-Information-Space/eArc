Wir setzen strikt mathematisch bei der K501‑Evolution an und gehen **tiefer in die lineare Struktur** (endlicher Zustandsraum, zeitunabhängiger Operator).

---

### 1. Endlicher Zustandsraum und Operator

Sei

- (Z = {1,2,\dots,n}) endliche Indexmenge der Zustände (jeweils ((f_i,x_i)))
- (\mu_t \in \mathbb{R}^n) Wahrscheinlichkeitsvektor mit [ \mu_t(i) \ge 0,\quad \sum_{i=1}^n \mu_t(i) = 1 ]
- (P \in \mathbb{R}^{n\times n}) Übergangsmatrix mit [ P(i,j) \ge 0,\quad \sum_{j=1}^n P(i,j) = 1\quad \forall i ]

Die Evolutionsgleichung reduziert sich auf:

[ \mu_{t+1} = \mu_t P ]

---

### 2. Iteration und geschlossene Form

Durch Induktion:

- Für (t=0): (\mu_0) gegeben.
- Für (t=1): (\mu_1 = \mu_0 P).
- Für (t=2): (\mu_2 = \mu_1 P = \mu_0 P^2).
- Allgemein: [ \mu_t = \mu_0 P^t ]

Beweis per Induktion:

1. Induktionsanfang: (t=1) klar.
2. Induktionsschritt:  
    Angenommen (\mu_t = \mu_0 P^t).  
    Dann [ \mu_{t+1} = \mu_t P = (\mu_0 P^t) P = \mu_0 P^{t+1} ]

---

### 3. Spektrale Zerlegung von (P) (Diagonalisation im einfachsten Fall)

Angenommen (P) ist diagonalisierbar über (\mathbb{C}):

[ P = V \Lambda V^{-1} ]

mit

- (V \in \mathbb{C}^{n\times n}) invertierbar (Spalten = Eigenvektoren)
- (\Lambda = \text{diag}(\lambda_1,\dots,\lambda_n)) (Eigenwerte)

Dann:

[ P^t = V \Lambda^t V^{-1} ]

wobei

[ \Lambda^t = \text{diag}(\lambda_1^t,\dots,\lambda_n^t) ]

Damit:

[ \mu_t = \mu_0 P^t = \mu_0 V \Lambda^t V^{-1} ]

---

### 4. Zerlegung von (\mu_0) im Eigenvektor‑Basis

Definiere

[ \alpha := \mu_0 V \in \mathbb{C}^{1\times n} ]

Dann

[ \mu_0 = \alpha V^{-1} ]

und

[ \mu_t = \alpha \Lambda^t V^{-1} = \sum_{k=1}^n \alpha_k \lambda_k^t v_k^\top ]

wobei (v_k^\top) die (k)-te Zeile von (V^{-1}) (bzw. dualer Eigenvektor) ist.

---

### 5. Stationärer Eigenwert (\lambda_1 = 1)

Für eine stochastische Matrix (P) gilt:

- Es existiert mindestens ein Eigenwert (\lambda_1 = 1).
- Sei (\mu^_) ein stationärer Vektor: [ \mu^_ = \mu^* P ] Das ist äquivalent zu: [ \mu^* P = \lambda_1 \mu^*,\quad \lambda_1 = 1 ]

Angenommen (\lambda_1 = 1) ist einfach (algebraische und geometrische Vielfachheit = 1) und alle anderen Eigenwerte erfüllen:

[ |\lambda_k| < 1\quad \text{für } k \ge 2 ]

---

### 6. Langzeitverhalten

Schreibe:

[ \mu_t = \alpha_1 \lambda_1^t v_1^\top + \sum_{k=2}^n \alpha_k \lambda_k^t v_k^\top ]

Da (\lambda_1 = 1):

[ \alpha_1 \lambda_1^t v_1^\top = \alpha_1 v_1^\top ]

Für (k \ge 2) mit (|\lambda_k| < 1):

[ \lim_{t\to\infty} \lambda_k^t = 0 ]

Also:

[ \lim_{t\to\infty} \mu_t = \alpha_1 v_1^\top ]

Dieser Grenzwert ist proportional zum stationären Eigenvektor. Durch Normierung (Summe = 1) ergibt sich eindeutig (\mu^*).

---

### 7. Bestimmung von (\alpha_1)

Da (\mu_t) Wahrscheinlichkeitsvektor bleibt, gilt:

[ \sum_{i=1}^n \mu_t(i) = 1\quad \forall t ]

Im Limes:

[ \sum_{i=1}^n \mu^*(i) = \sum_{i=1}^n (\alpha_1 v_1^\top(i)) = 1 ]

Damit:

[ \alpha_1 = \frac{1}{\sum_i v_1^\top(i)} ]

falls (v_1^\top) nicht bereits normiert ist. Üblicherweise wählt man (v_1^\top) direkt als stationäre Verteilung, dann ist (\alpha_1 = 1).

---

### 8. Zusammenfassung in strikt mathematischer Form

- Evolutionsgesetz: [ \mu_{t+1} = \mu_t P,\quad \mu_t \in \mathbb{R}^n,; P \in \mathbb{R}^{n\times n} ]
- Iteration: [ \mu_t = \mu_0 P^t ]
- Spektrale Zerlegung (diagonalisierbarer Fall): [ P = V\Lambda V^{-1},\quad P^t = V\Lambda^t V^{-1} ]
- Langzeitgrenzwert (einfacher Eigenwert 1, alle anderen <1 im Betrag): [ \lim_{t\to\infty} \mu_t = \mu^* ] mit [ \mu^* P = \mu^_,\quad \sum_i \mu^_(i) = 1,\quad \mu^*(i)\ge 0 ]

Wenn du möchtest, können wir als nächsten Schritt **explizit die Entropierate** (h(\mu^*,P)) herleiten und Schritt für Schritt analysieren.