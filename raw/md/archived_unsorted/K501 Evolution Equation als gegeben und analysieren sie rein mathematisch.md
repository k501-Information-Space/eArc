Wir gehen in **strikten Rechenmodus** und nehmen die **K501 Evolution Equation** als gegeben und analysieren sie rein mathematisch.

---

### 1. Definition der Größen

Wir betrachten eine endliche oder abzählbare Menge kombinierter Zustände [ Z = {z_k}_{k\in K},\quad z_k = (f_k,x_k) ]

Eine **Wahrscheinlichkeitsverteilung** auf (Z) zum Zeitpunkt (t) sei [ \mu_t : Z \to [0,1],\quad \sum_{k\in K} \mu_t(z_k) = 1 ]

Wir schreiben kurz (\mu_t(k) := \mu_t(z_k)).

---

### 2. Gewichtsfunktion

Definiere eine **nichtnegative Gewichtsfunktion** (W_t(i,j)) für Übergänge von (z_i) nach (z_j):

[ W_t(i,j) = \mu_t(i); \exp!\big(-\mathcal{A}(x_i,x_j)\big); \mathcal{R}(f_i,f_j); \chi_\Omega(x_j); \chi_p(f_j,x_j); \chi_\tau(t_i,t_j); \big(1 - D(x_j)\big) ]

Annahmen:

1. (\mathcal{A}(x_i,x_j) \in \mathbb{R})  
    ⇒ (\exp(-\mathcal{A}) > 0)
    
2. (\mathcal{R}(f_i,f_j) \ge 0)
    
3. (\chi_\Omega,\chi_p,\chi_\tau \in {0,1})
    
4. (D(x_j) \in [0,1])  
    ⇒ (1 - D(x_j) \in [0,1])
    

Damit gilt für alle (i,j): [ W_t(i,j) \ge 0 ]

---

### 3. Normierungskonstante

Definiere die **Normierungskonstante** (Z_t) als:

[ Z_t = \sum_{k\in K} \sum_{i\in K} W_t(i,k) ]

Da alle (W_t(i,k) \ge 0), gilt:

- (Z_t \ge 0)
- Falls es mindestens ein Paar ((i,k)) mit (W_t(i,k) > 0) gibt, dann (Z_t > 0).

Wir setzen voraus, dass (Z_t > 0) (sonst wäre keine Evolution definiert).

---

### 4. Definition von (\mu_{t+1})

Die K501 Evolution Equation lautet dann:

[ \mu_{t+1}(j) = \frac{ \displaystyle \sum_{i\in K} W_t(i,j) }{ \displaystyle Z_t } ]

Das ist exakt die kompakte Form der vorherigen „langen“ Gleichung.

---

### 5. Nichtnegativität von (\mu_{t+1})

Für jedes (j\in K):

- Zähler: (\sum_i W_t(i,j) \ge 0)
- Nenner: (Z_t > 0)

Daraus folgt:

[ \mu_{t+1}(j) \ge 0 ]

---

### 6. Normierung von (\mu_{t+1})

Wir berechnen die Summe über alle (j\in K):

[ \sum_{j\in K} \mu_{t+1}(j) = \sum_{j\in K} \frac{ \sum_{i\in K} W_t(i,j) }{ Z_t } = \frac{ \sum_{j\in K} \sum_{i\in K} W_t(i,j) }{ Z_t } ]

Vertauschen der Summen:

[ \sum_{j\in K} \sum_{i\in K} W_t(i,j) = \sum_{i\in K} \sum_{j\in K} W_t(i,j) ]

Per Definition von (Z_t):

[ \sum_{j\in K} \sum_{i\in K} W_t(i,j) = Z_t ]

Also:

[ \sum_{j\in K} \mu_{t+1}(j) = \frac{Z_t}{Z_t} = 1 ]

Damit ist (\mu_{t+1}) wieder eine **Wahrscheinlichkeitsverteilung**.

---

### 7. Markov‑Struktur (explizit)

Definiere einen **effektiven Übergangsoperator** (P_t(i,j)) durch:

[ P_t(i,j) = \frac{ W_t(i,j) }{ \sum_{k\in K} W_t(i,k) } \quad\text{falls } \sum_{k} W_t(i,k) > 0 ]

Dann gilt:

1. (P_t(i,j) \ge 0)
2. (\sum_{j} P_t(i,j) = 1) für alle (i) mit (\sum_k W_t(i,k) > 0)

Schreibe:

[ \mu_{t+1}(j) = \frac{ \sum_i \mu_t(i),\tilde{W}_t(i,j) }{ Z_t } ]

mit (\tilde{W}_t(i,j) = W_t(i,j)/\mu_t(i)) (für (\mu_t(i)>0)).  
Alternativ, wenn wir (Z_t) in die Definition von (P_t) einbauen, können wir formal schreiben:

[ \mu_{t+1}(j) = \sum_{i} \mu_t(i),P_t(i,j) ]

wobei (P_t) aus den gewichteten Termen (Action, Relation, Filter, Drift) konstruiert ist.

Damit ist die K501 Evolution Equation **formal ein (zeitabhängiger) Markov‑Update** auf dem Zustandsraum (Z).

---

### 8. Stationäre Verteilung (rein formal)

Eine Verteilung (\mu^*) heißt stationär, falls:

[ \mu^_(j) = \sum_i \mu^_(i),P_t(i,j) ]

Falls (P_t) zeitunabhängig ist (z.B. alle Terme ohne explizites (t)), schreiben wir (P) und suchen (\mu^*) mit:

[ \mu^* = \mu^* P,\quad \sum_j \mu^_(j) = 1,\quad \mu^_(j) \ge 0 ]

Das ist exakt das Eigenvektorproblem:

[ \mu^* P = \mu^*,\quad \lambda_1 = 1 ]

---

Wenn du willst, können wir als nächsten Schritt **konkret**:

- das **Eigenwertproblem** für einen endlichen Zustandsraum (Z) durchrechnen, oder
- die **Entropierate** (h(\mu_t,P_t)) explizit herleiten, oder
- eine **konkrete Form von (\mathcal{A}) und (\mathcal{R})** annehmen und dann die Struktur von (P_t) analysieren.