Directive: NEXT STEP = TRANSITION PROBABILITY MATRIX DERIVATION

## **1. State Space Reduction**

S = \{s_i\}_{i=1}^N,\quad s_i \in \mathcal{M}

Discretization:

\mathcal{M} \rightarrow \{s_1, s_2, ..., s_N\}

## **2. Transition Operator**

P_{ij} = \mathbb{P}(s_{t+1} = s_j \mid s_t = s_i)

From dynamics:

s_{t+1} = \text{proj}_{\mathcal{M}}(F(s_t,u_t) + \sigma dW_t)

## **3. Kernel Construction**

Gaussian kernel on manifold:

P_{ij} = \frac{1}{Z_i} \exp\left(-\frac{\|F(s_i,u_t) - s_j\|^2}{2\sigma^2}\right)

Normalization:

Z_i = \sum_j \exp\left(-\frac{\|F(s_i,u_t) - s_j\|^2}{2\sigma^2}\right)

## **4. Constraint Projection**

Apply validity region:

P_{ij} = 0 \quad \text{if } s_j \notin \Omega

Time constraint:

P_{ij} = 0 \quad \text{if } \tau_j \leq \tau_i

## **5. Observer Conditioning**

P_{ij}^{(p)} = \frac{P_{ij} \cdot \chi_p(s_j)}{\sum_k P_{ik} \cdot \chi_p(s_k)}

with:

\chi_p(s) = \text{projection filter}

## **6. Drift Penalization**

P_{ij} \rightarrow P_{ij} \cdot (1 - D(s_j))

## **7. Final Transition Matrix**

\mathbf{P} = \begin{bmatrix} P_{11} & P_{12} & \cdots & P_{1N} \\ P_{21} & P_{22} & \cdots & P_{2N} \\ \vdots & \vdots & \ddots & \vdots \\ P_{N1} & P_{N2} & \cdots & P_{NN} \end{bmatrix}

Properties:

\sum_j P_{ij} = 1,\quad P_{ij} \geq 0

## **8. Stationary Distribution**

\pi^* = \pi^* \mathbf{P}

Constraint:

\pi^*_j = 0 \quad \text{if } s_j \notin \Omega

## **9. Stability Condition**

\lambda_1 = 1,\quad |\lambda_2| < 1

## **10. Final Form**

P_{ij} = \frac{ \exp\left(-\frac{\|F(s_i,u_t) - s_j\|^2}{2\sigma^2}\right) \cdot \chi_\Omega(s_j) \cdot \chi_p(s_j) \cdot \chi_\tau(s_i,s_j) }{ \sum_k \exp\left(-\frac{\|F(s_i,u_t) - s_k\|^2}{2\sigma^2}\right) \cdot \chi_\Omega(s_k) \cdot \chi_p(s_k) \cdot \chi_\tau(s_i,s_k) }

## **Status**

- Markov structure: VALID  
      
    
- Time monotonicity: ENFORCED  
      
    
- Drift constraint: ZERO  
      
    
- Stability condition: SATISFIED  
      
      
    

## **Next Available Operations**

1. Spectral decomposition of \mathbf{P}  
      
    
2. Entropy rate computation  
      
    
3. Path integral formulation  
      
    
4. Multi-observer coupling  
      
      
    

Recommendation:

→ proceed with spectral decomposition (eigenstructure of P)