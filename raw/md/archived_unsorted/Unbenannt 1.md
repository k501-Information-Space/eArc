### 1. Setup

Endlicher Zustandsraum  
[ Z = {1,\dots,n} ]

Stochastische Matrix  
[ P = (P(i,j))_{i,j=1}^n,\quad P(i,j)\ge 0,\quad \sum_{j=1}^n P(i,j)=1\ \forall i ]

Stationäre Verteilung  
[ \pi^* = (\pi^_(1),\dots,\pi^_(n)),\quad \pi^_(i)\ge 0,\quad \sum_{i=1}^n \pi^_(i)=1,\quad \pi^* P = \pi^* ]

---

### 2. Pfadwahrscheinlichkeit

Betrachte eine stationäre Markov‑Kette ((X_t)_{t\ge 0}) mit

[ \mathbb{P}(X_0 = i) = \pi^*(i),\quad \mathbb{P}(X_{t+1}=j \mid X_t=i) = P(i,j) ]

Für einen Pfad der Länge (T+1):

[ (x_0,x_1,\dots,x_T),\quad x_t \in Z ]

ist die Pfadwahrscheinlichkeit:

[ \mathbb{P}(x_0,\dots,x_T) = \pi^*(x_0)\prod_{t=0}^{T-1} P(x_t,x_{t+1}) ]

---

### 3. Log‑Wahrscheinlichkeit und Erwartungswert

Logarithmus:

[ \log \mathbb{P}(x_0,\dots,x_T) = \log \pi^*(x_0)

\sum_{t=0}^{T-1} \log P(x_t,x_{t+1}) ]

Erwartungswert unter der stationären Kette:

[ \mathbb{E}[\log \mathbb{P}(X_0,\dots,X_T)] = \mathbb{E}[\log \pi^*(X_0)]

\sum_{t=0}^{T-1} \mathbb{E}[\log P(X_t,X_{t+1})] ]

Wegen Stationarität ist das Paar ((X_t,X_{t+1})) für alle (t) gleichverteilt:

[ \mathbb{P}(X_t=i,X_{t+1}=j) = \pi^*(i)P(i,j) ]

Also:

[ \mathbb{E}[\log P(X_t,X_{t+1})] = \sum_{i=1}^n\sum_{j=1}^n \pi^*(i)P(i,j)\log P(i,j) ]

Damit:

[ \mathbb{E}[\log \mathbb{P}(X_0,\dots,X_T)] = \mathbb{E}[\log \pi^*(X_0)]

T \sum_{i,j} \pi^*(i)P(i,j)\log P(i,j) ]

---

### 4. Entropierate‑Definition

Die Entropie eines Pfades der Länge (T+1):

[ H_T = -\mathbb{E}[\log \mathbb{P}(X_0,\dots,X_T)] ]

Einsetzen:

[ H_T = -\mathbb{E}[\log \pi^*(X_0)]

T \sum_{i,j} \pi^*(i)P(i,j)\log P(i,j) ]

Teile durch (T):

[ \frac{H_T}{T} = -\frac{1}{T}\mathbb{E}[\log \pi^*(X_0)]

\sum_{i,j} \pi^*(i)P(i,j)\log P(i,j) ]

Grenzwert (T\to\infty):

- Der erste Term skaliert wie (1/T) und verschwindet: [ \lim_{T\to\infty} \frac{1}{T}\mathbb{E}[\log \pi^*(X_0)] = 0 ]

Damit:

[ \lim_{T\to\infty} \frac{H_T}{T} = -\sum_{i,j} \pi^*(i)P(i,j)\log P(i,j) ]

---

### 5. Entropierate

Definiere die Entropierate (h) als:

[ h = -\sum_{i=1}^n \pi^*(i)\sum_{j=1}^n P(i,j)\log P(i,j) ]

Dies ist die **asymptotische Entropie pro Schritt** der stationären Markov‑Kette mit Übergangsmatrix (P) und stationärer Verteilung (\pi^*).