import streamlit as st
import numpy as np
import plotly.graph_objects as go

# -----------------------------
# Minimal K501FullNode Mock
# -----------------------------
class K501FullNode:
    def __init__(self, config: dict):
        self.config = config or {}
        self.pack_meta = (self.config.get("pack_meta") or {})
        self.integrity_hash = self.pack_meta.get("integrity_hash", "UNSET")

    @staticmethod
    def _normalize(p):
        p = np.asarray(p, dtype=float)
        s = p.sum()
        if s <= 0:
            # fallback to uniform
            return np.ones_like(p) / len(p)
        return p / s

    def calculate_delta(self, p_a, p_b, metric: str = "l2"):
        """Dispersion δ between two observer profiles."""
        a = self._normalize(p_a)
        b = self._normalize(p_b)

        if metric == "l2":
            return float(np.linalg.norm(a - b))

        if metric == "jsd":
            # Jensen-Shannon distance (bounded, symmetric)
            m = 0.5 * (a + b)

            def kl(p, q):
                eps = 1e-12
                p = np.clip(p, eps, 1.0)
                q = np.clip(q, eps, 1.0)
                return np.sum(p * np.log2(p / q))

            js_div = 0.5 * kl(a, m) + 0.5 * kl(b, m)
            # distance = sqrt(divergence)
            return float(np.sqrt(js_div))

        raise ValueError("Unknown metric. Use 'l2' or 'jsd'.")

    def get_entropy_mu(self, p):
        """Shannon entropy μ in bits."""
        p = self._normalize(p)
        eps = 1e-12
        p = np.clip(p, eps, 1.0)
        return float(-np.sum(p * np.log2(p)))

# -----------------------------
# Page Setup
# -----------------------------
st.set_page_config(page_title="K501 Control Center", page_icon="💹", layout="wide")

st.markdown(
    """
    <style>
      .stMetric { background-color: #f0f2f6; padding: 15px; border-radius: 10px; }
    </style>
    """,
    unsafe_allow_html=True,
)

st.title("💹 K501 Epistemic Control Center")
st.caption("Verifizierter Full-Node Status: ACTIVE | Integrity: PROTECTED")

# Initialize Engine
@st.cache_resource
def get_engine():
    return K501FullNode({"pack_meta": {"integrity_hash": "693cebfc..."}})

engine = get_engine()

# --- Sidebar ---
st.sidebar.header("🛡️ Integrity Audit")
st.sidebar.success("Pack-01..04: VALID")
st.sidebar.code(f"HASH: {engine.integrity_hash}")
epsilon = st.sidebar.select_slider("Privacy Budget (ε)", options=[0.001, 0.01, 0.1], value=0.01)
metric = st.sidebar.selectbox("Dispersion metric", ["l2", "jsd"], index=0)

# --- Main Interaction ---
col_in, col_viz = st.columns([1, 1])

with col_in:
    st.subheader("Observer Profiles")

    st.write("**Observer A (Innovation/Efficiency)**")
    a1 = st.slider("A: Autonomy (ω1)", 0.0, 1.0, 0.85, key="a1")
    a2 = st.slider("A: Alignment (ω2)", 0.0, 1.0 - a1, 0.10, key="a2")
    a3 = max(0.0, 1.0 - (a1 + a2))
    st.caption(f"A: Silence (ω3) = {a3:.3f} (auto)")

    st.divider()

    st.write("**Observer B (Safety/Regulation)**")
    b1 = st.slider("B: Autonomy (ω1)", 0.0, 1.0, 0.15, key="b1")
    b2 = st.slider("B: Alignment (ω2)", 0.0, 1.0 - b1, 0.70, key="b2")
    b3 = max(0.0, 1.0 - (b1 + b2))
    st.caption(f"B: Silence (ω3) = {b3:.3f} (auto)")

p_a = [a1, a2, a3]
p_b = [b1, b2, b3]

# --- Calculation ---
# epsilon ist hier (noch) UI-seitig; später kannst du es in die Engine geben (DP/noise etc.)
delta = engine.calculate_delta(p_a, p_b, metric=metric)
mu_a = engine.get_entropy_mu(p_a)
mu_b = engine.get_entropy_mu(p_b)

# --- Visualization ---
with col_viz:
    st.subheader("Semantic Geometry (Ω-Space)")

    categories = ["Autonomy (ω1)", "Alignment (ω2)", "Silence (ω3)"]
    fig = go.Figure()

    fig.add_trace(go.Scatterpolar(r=p_a, theta=categories, fill="toself", name="Observer A"))
    fig.add_trace(go.Scatterpolar(r=p_b, theta=categories, fill="toself", name="Observer B"))

    fig.update_layout(
        polar=dict(radialaxis=dict(visible=True, range=[0, 1])),
        showlegend=True,
    )
    st.plotly_chart(fig, use_container_width=True)

# --- Final Metrics ---
st.divider()
m1, m2, m3 = st.columns(3)

with m1:
    st.metric("Dispersion (δ)", f"{delta:.4f}")
    if delta > 0.15:
        st.error("Status: DIVERGENT")
    else:
        st.success("Status: ALIGNED")

with m2:
    st.metric("Density Observer A (μ)", f"{mu_a:.2f} bits")

with m3:
    st.metric("Density Observer B (μ)", f"{mu_b:.2f} bits")