K501_CANONICAL_REGISTRY_ENTRY_v1.0

ts:
  utc: 2026-02-24T19:33:30Z
  unix: 1771961610

mode: REFERENCE_ONLY
policy: APPEND_ONLY
scope: MODEL_AGNOSTIC
registry: KAX

entries:

  - id: KAX-CORE-OM-1
    name: Core Object Model v1.0 (FROZEN)
    defines:
      - K501 := (F, R, A, I, T, P)
      - Frame f := (id, r, t, m)
      - Time anchor t := (utc, unix)
      - Invariant i : F -> {0,1}
      - Adapter a : R_p -> R_q
      - Perspective p := (R_p, A_p)
      - Registry Reg : id -> f (append-only)
    constraints:
      - AppendOnly(F)
      - TimeConsistent(t)
      - DeterministicCanonicalSerialization
    status: FROZEN

  - id: KAX-DIV-1
    name: Structural Diversity Axiom v1.0 (FROZEN)
    defines:
      - Stable(P,I) := ∀p∈P ∀i∈I : i(X_p)=1
      - Robustness(K501) ∝ |P| given Stable(P,I)
      - Drift := ¬Stable(P,I) ∨ ∃a∈A : ¬Hom(a)
    status: FROZEN

  - id: KAX-DIV-2
    name: Cohesive Inclusion (v1.1 draft)
    defines:
      - P1 ⊆ P2 ∧ Stable(P2,I) ⇒ Stable(P1,I)
      - P1 ⊆ P2 ∧ Stable(P2,I) ⇒ R(P2,I) ≥ R(P1,I)
    status: DRAFT

  - id: KAX-HOM-1
    name: Invariant-Preserving Homomorphism (v1.1 draft)
    defines:
      - Hom(a_{p→q}) := ∀i∈I : i(X_p)=1 ⇒ i(X_q)=1
    status: DRAFT

  - id: KAX-MASTER-1
    name: Master Formula v1.0 (DRAFT)
    defines:
      - Coherent(K501) ⇔ [∀f∈F Valid(f)] ∧ AppendOnly(F) ∧ Stable(P,I) ∧ [∀a∈A Hom(a)]
      - Valid(f) ⇔ TimeConsistent(t(f)) ∧ (∀i∈I_core i(f)=1)
    status: DRAFT

  - id: KAX-CDS-1
    name: Constrained Dynamical System (K501-CDS) v1.0 (FROZEN)
    defines:
      - x_{k+1} = Π_Ω(f(x_k,u_k))
      - y_k = g(x_k,u_k)
      - ℓ_{k+1} = ℓ_k || frame(x_k,u_k,y_k)   (append-only)
      - SAFE_MODE: anomaly ⇒ state := SAFE_MODE; output suppress
    status: FROZEN

  - id: KAX-CIR-1
    name: Context Injection Resistance (CIR) v1.0
    defines:
      - CIR(y) := Statements(y) ⊆ K(x,u,I)
      - Violation: ∃s∈Statements(y): s ∉ K(x,u,I)
      - Typing rule: if s ∉ K(x,u,I) ⇒ Type(s) ∈ {HYPOTHESIS, UNKNOWN} or suppress
    enforcement:
      - PASS if derivable
      - CAST to HYPOTHESIS/UNKNOWN if safely markable
      - SUPPRESS if not derivable and not safely typable
    receipts:
      - CIR_EVENT {cast_count, suppress_count, reason=R_CIR_INJECTION}
    status: ACTIVE

  - id: KAX-CDS-CIR-1
    name: CDS Output Projection with CIR (v1.0)
    defines:
      - y_k = Π_CIR(g(x_k,u_k))
      - InjectionEvent_k ⇔ Π_CIR(g(x_k,u_k)) ≠ g(x_k,u_k)
      - ℓ_{k+1} = ℓ_k || frame(...) || frame_CIR(k,Δ) (when InjectionEvent)
    status: ACTIVE

notes:
  - APPEND_ONLY: registry entries are never modified; supersede via new ids/versions only
  - HASHES: omitted (compute offline on canonical bytes)

END_K501_CANONICAL_REGISTRY_ENTRY