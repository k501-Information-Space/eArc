### 1. Grundobjekte

Sei (Z) eine endliche Indexmenge: [ Z = {1,\dots,n} ]

Jeder Zustand: [ z_i = (f_i,x_i),\quad i\in Z ]

- (f_i): Frame
- (x_i): geometrischer Zustand

Wahrscheinlichkeitsverteilung: [ \mu_t : Z \to [0,1],\quad \mu_t(i)\ge 0,\quad \sum_{i\in Z}\mu_t(i)=1 ]

---

### 2. Gewichtsfunktion

Definiere für alle (i,j\in Z) die Gewichtsfunktion [ W(i,j) = \exp!\big(-\mathcal{A}(x_i,x_j)\big); \mathcal{R}(f_i,f_j); \chi_\Omega(x_j); \chi_p(f_j,x_j); \chi_\tau(t_i,t_j); \big(1 - D(x_j)\big) ]

mit Axiomen:

1. (\mathcal{A}(x_i,x_j)\in\mathbb{R})
2. (\mathcal{R}(f_i,f_j)\ge 0)
3. (\chi_\Omega,\chi_p,\chi_\tau \in {0,1})
4. (D(x_j)\in[0,1])

Daraus folgt: [ W(i,j)\ge 0\quad \forall i,j ]

---

### 3. Normierungskonstante

[ Z_W = \sum_{k\in Z}\sum_{i\in Z} W(i,k) ]

Axiom: [ Z_W > 0 ]

---

### 4. K501 Evolution Equation

Die Evolutionsabbildung (\mu_t \mapsto \mu_{t+1}) ist definiert durch: [ \boxed{ \mu_{t+1}(j) = \frac{ \displaystyle \sum_{i\in Z} \mu_t(i),W(i,j) }{ \displaystyle \sum_{k\in Z}\sum_{i\in Z} \mu_t(i),W(i,k) } } \quad\forall j\in Z ]

---

### 5. Axiome der Evolution

1. **Nichtnegativität**  
    [ \mu_{t+1}(j)\ge 0\quad \forall j ]
    
2. **Normierung**  
    [ \sum_{j\in Z}\mu_{t+1}(j)=1 ]
    
3. **Markov‑Struktur**  
    Definiere [ P(i,j) = \frac{W(i,j)}{\sum_{k\in Z}W(i,k)} \quad\text{falls }\sum_k W(i,k)>0 ] Dann [ \mu_{t+1} = \mu_t P ]
    
4. **Stationarität**  
    Eine Verteilung (\mu^_) ist stationär, falls [ \mu^_ = \mu^* P,\quad \sum_{i\in Z}\mu^_(i)=1,\quad \mu^_(i)\ge 0 ]
    

---

### 6. Entropierate

Für stationäre (\mu^_) und (P): [ h = -\sum_{i\in Z}\mu^_(i)\sum_{j\in Z}P(i,j)\log P(i,j) ]

---

**K501 System (axiomatisch verdichtet):**

- Zustandsraum: (Z)
- Verteilung: (\mu_t)
- Gewicht: (W(i,j))
- Operator: (P) aus (W)
- Evolution: (\mu_{t+1} = \mu_t P)
- Stationarität: (\mu^* = \mu^* P)
- Entropierate: (h) wie oben.