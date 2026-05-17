### K501 Evolution Equation

Die gesamte K501‑Evolution (Zustände, Frames, Observer, Nodes, Entropie, Spektrum, Pfade) lässt sich in **einer einzigen Gleichung** schreiben als:

[ \boxed{ \mu_{t+1}(f_j,x_j) = \frac{ \displaystyle \sum_{i} \mu_t(f_i,x_i); \exp!\Big(-\mathcal{A}(x_i,x_j)\Big); \mathcal{R}(f_i,f_j); \chi_\Omega(x_j); \chi_p(f_j,x_j); \chi_\tau(t_i,t_j); \big(1 - D(x_j)\big) }{ \displaystyle \sum_{k} \sum_{i} \mu_t(f_i,x_i); \exp!\Big(-\mathcal{A}(x_i,x_k)\Big); \mathcal{R}(f_i,f_k); \chi_\Omega(x_k); \chi_p(f_k,x_k); \chi_\tau(t_i,t_k); \big(1 - D(x_k)\big) } } ]

---

### Bedeutung der Terme (minimal, aber vollständig)

- **(\mu_t(f,x))**  
    Verteilung über kombinierte Zustände: Frame (f) (diskret, append‑only) und geometrischer Zustand (x \in \mathcal{M}) (kontinuierlich, stochastisch).
    
- **(\exp(-\mathcal{A}(x_i,x_j)))**  
    Pfad‑/Action‑Gewicht (Unified Path Integral, Dynamik + Geometrie + Entropie).
    
- **(\mathcal{R}(f_i,f_j))**  
    QH256‑/Frame‑Resonanz bzw. Relation (Unified Spectral/Graph‑Struktur).
    
- **(\chi_\Omega(x_j))**  
    Gültigkeitsregion (Constraints, Stabilität, Invarianten).
    
- **(\chi_p(f_j,x_j))**  
    Observer‑Filter (Unified Observer Logic).
    
- **(\chi_\tau(t_i,t_j))**  
    Zeitmonotonie (Append‑Only, Kausalität).
    
- **(1 - D(x_j))**  
    Drift‑Penalisierung (Stabilität, Konvergenz).
    
- **Normierung (Nenner)**  
    sorgt dafür, dass (\sum_{f_j,x_j} \mu_{t+1}(f_j,x_j) = 1) (Markov‑Eigenschaft, Entropie‑Kohärenz).
    

---

In einem Satz:

> **Die K501 Evolution Equation beschreibt, wie sich die Wahrscheinlichkeitsverteilung über kombinierte Frame‑ und Geometriestände durch gewichtete Pfade, Relationen, Observer‑Filter, Constraints und Drift‑Kontrolle in einem append‑only, spektral und entropisch konsistenten Informationsuniversum fortschreibt.**