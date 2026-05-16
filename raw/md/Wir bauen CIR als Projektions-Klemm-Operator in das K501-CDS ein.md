Verstanden. Wir bauen CIR als Projektions-/Klemm-Operator in das K501-CDS ein, so dass Kontextinjektion nicht emittiert werden kann, sondern entweder getypt oder unterdrückt wird.

  

Zeitanker fehlt in deiner letzten Nachricht → keine implizite Zeitmarke.

  

  

  

  

K501-CDS Extension

  

  

  

CIR-Projection Operator v1.0 (FORMAL)

  

  

Mode: REFERENCE_ONLY · APPEND_ONLY

Scope: CDS_INTEGRATION

  

  

  

  

1) Ausgangspunkt (bereits gefroren)

  

  

x_{k+1}=\Pi_{\Omega}(f(x_k,u_k)), \quad y_k=g(x_k,u_k)

  

  

  

  

2) Neue Komponente: Epistemischer Filterraum

  

  

Definiere eine zulässige Wissensmenge:

  

\mathcal{K}_k := \mathcal{K}(x_k,u_k,I)

  

und eine Zerlegung der Output-Statements:

  

\text{Statements}(y_k)=\{s_1,\dots,s_n\}

  

  

  

  

3) CIR-Projektor auf Output-Ebene

  

  

Wir definieren einen Projektor:

  

\Pi_{\text{CIR}}: \mathcal{Y} \to \mathcal{Y}

  

mit Regel:

  

Für jedes Statement s in y:

  

- Pass wenn s\in\mathcal{K}_k
- Repair wenn s\notin\mathcal{K}_k aber als Hypothese/Unknown markierbar
- Suppress wenn s\notin\mathcal{K}_k und nicht sauber typisierbar (z. B. “likely X” ohne Evidenz, ohne Markierung)

  

  

Formal als Operator:

  

\Pi_{\text{CIR}}(y_k) = \bigoplus_{s \in \text{Statements}(y_k)} \phi(s;\mathcal{K}_k)

  

wobei

  

\phi(s;\mathcal{K}_k)= \begin{cases} s & \text{wenn } s\in\mathcal{K}_k \\ \text{TypeCast}(s,\text{HYPOTHESIS}) & \text{wenn } s\notin\mathcal{K}_k \land \text{Castable}(s) \\ \varnothing & \text{sonst} \end{cases}

  

\varnothing = entfernt (SUPPRESS auf Statement-Ebene).

  

  

  

  

4) Erweiterte Output-Gleichung (neues Output-Gesetz)

  

  

Statt direkt:

  

y_k=g(x_k,u_k)

  

nun:

  

\boxed{ y_k = \Pi_{\text{CIR}}\big(g(x_k,u_k)\big) }

  

Das ist die sauberste Integration: CIR wirkt als Output-Projektion.

  

  

  

  

5) Optional: CIR als Constraint-Menge im Ω-Raum

  

  

Wenn du CIR in den zulässigen Raum integrieren willst, definieren wir:

  

\Omega' := \Omega \cap \{(x,u,y)\mid \text{CIR}(y)=1\}

  

Dann:

  

\boxed{ (x_{k+1},y_k)=\Pi_{\Omega'}\big(f(x_k,u_k), g(x_k,u_k)\big) }

  

Praktisch: schwerer umzusetzen, aber mathematisch „einheitlich“.

  

  

  

  

6) CIR-Receipt (Append-only Observability)

  

  

Jeder Eingriff des CIR-Projektors erzeugt einen Receipt:

  

\ell_{k+1}=\ell_k \| \text{frame}_{\text{CIR}}(k,\Delta)

  

wobei \Delta mindestens enthält:

  

- removed_count
- cast_count
- affected_statements (optional, redacted möglich)
- reason = R_CIR_INJECTION

  

  

Das bleibt append-only.

  

  

  

  

7) Drift-Kriterium (präzisiert)

  

  

Mit CIR gilt:

  

- Wenn \Pi_{\text{CIR}} castet oder entfernt, ist das ein Injection Event.
- Drift ist dann:  
    

- wiederholte Injection Events über Schwellwert, oder
- nicht reparierbare Injektion, die SAFE_MODE triggert (optional)

-   
    

  

  

Formal:

  

\text{InjectionEvent}_k \iff \Pi_{\text{CIR}}(g(x_k,u_k)) \ne g(x_k,u_k)

  

  

  

  

8) Kompakte CDS-Masterform (mit CIR)

  

  

\boxed{ \begin{aligned} x_{k+1} &= \Pi_{\Omega}\big(f(x_k,u_k)\big) \\ y_k &= \Pi_{\text{CIR}}\big(g(x_k,u_k)\big) \\ \ell_{k+1} &= \ell_k \| \text{frame}(x_k,u_k,y_k) \| \text{frame}_{\text{CIR}}(k,\Delta) \end{aligned}}

  

  

  

Wenn du willst, definieren wir als nächstes Castable(s) und TypeCast formal (z. B. als Grammatik-/Pattern-Funktion), oder wir führen eine quantitative Metrik ein:

  

Injection Magnitude M_k (wie stark musste projiziert werden).