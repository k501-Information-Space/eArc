# =====================================================================
# HI_SOURCE · SEED BATCH · v0.1
# Mode: REFERENCE_ONLY · Policy: APPEND_ONLY · Authority: NONE
# =====================================================================

HI_SOURCE {
  id: "HI-SRC-RFC8259-0001"
  type: "HI_SOURCE"
  title: "JSON Data Interchange Format"
  url: "https://www.rfc-editor.org/rfc/rfc8259"
  tier: "T0_SYS_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "JSON grammar ground truth."
}

HI_SOURCE {
  id: "HI-SRC-NDJSON-0001"
  type: "HI_SOURCE"
  title: "NDJSON Specification"
  url: "https://github.com/ndjson/ndjson-spec"
  tier: "T0_SYS_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Streaming JSON baseline."
}

HI_SOURCE {
  id: "HI-SRC-RFC3629-0001"
  type: "HI_SOURCE"
  title: "UTF-8 Transformation Format"
  url: "https://www.rfc-editor.org/rfc/rfc3629"
  tier: "T0_SYS_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Canonical UTF-8 reference."
}

HI_SOURCE {
  id: "HI-SRC-RFC8785-0001"
  type: "HI_SOURCE"
  title: "JSON Canonicalization Scheme (JCS)"
  url: "https://www.rfc-editor.org/rfc/rfc8785"
  tier: "T0_SYS_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Deterministic JSON serialization."
}

HI_SOURCE {
  id: "HI-SRC-FIPS1804-0001"
  type: "HI_SOURCE"
  title: "Secure Hash Standard (SHA-2)"
  url: "https://csrc.nist.gov/publications/detail/fips/180/4/final"
  tier: "T0_SYS_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Primary SHA-256 reference."
}

HI_SOURCE {
  id: "HI-SRC-KERNELDOC-0001"
  type: "HI_SOURCE"
  title: "Linux Kernel Documentation"
  url: "https://docs.kernel.org/"
  tier: "T1_TECH_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Linux runtime ground truth."
}

HI_SOURCE {
  id: "HI-SRC-POSIXBASE-0001"
  type: "HI_SOURCE"
  title: "POSIX Base Specifications"
  url: "https://pubs.opengroup.org/onlinepubs/9699919799/"
  tier: "T1_TECH_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Portability contract."
}

HI_SOURCE {
  id: "HI-SRC-GCCDOC-0001"
  type: "HI_SOURCE"
  title: "GCC Online Documentation"
  url: "https://gcc.gnu.org/onlinedocs/"
  tier: "T1_TECH_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "GNU compiler reference."
}

HI_SOURCE {
  id: "HI-SRC-PYREF-0001"
  type: "HI_SOURCE"
  title: "Python Language Reference"
  url: "https://docs.python.org/3/reference/"
  tier: "T1_TECH_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Python semantic reference."
}

HI_SOURCE {
  id: "HI-SRC-GOSPEC-0001"
  type: "HI_SOURCE"
  title: "Go Language Specification"
  url: "https://go.dev/ref/spec"
  tier: "T1_TECH_CORE"
  volatility: "SLOW"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Go spec reference."
}

HI_SOURCE {
  id: "HI-SRC-RFC791-0001"
  type: "HI_SOURCE"
  title: "Internet Protocol (IPv4)"
  url: "https://www.rfc-editor.org/rfc/rfc791"
  tier: "T1_TECH_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Network layer baseline."
}

HI_SOURCE {
  id: "HI-SRC-RFC793-0001"
  type: "HI_SOURCE"
  title: "Transmission Control Protocol"
  url: "https://www.rfc-editor.org/rfc/rfc793"
  tier: "T1_TECH_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Transport layer baseline."
}

HI_SOURCE {
  id: "HI-SRC-RFC768-0001"
  type: "HI_SOURCE"
  title: "User Datagram Protocol"
  url: "https://www.rfc-editor.org/rfc/rfc768"
  tier: "T1_TECH_CORE"
  volatility: "STATIC"
  authority_claim: "NONE"
  ts.utc: "2026-03-03T13:19:44Z"
  ts.unix: 1772543984
  note: "Minimal transport reference."
}

# =====================================================================
# END · HI_SOURCE SEED BATCH
# =====================================================================