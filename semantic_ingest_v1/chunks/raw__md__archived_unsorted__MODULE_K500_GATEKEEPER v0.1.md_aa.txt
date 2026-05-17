MODULE_K500_GATEKEEPER v0.1
│
├─ ROLLE
│  ├─ Eintrittsschwelle (Gate)
│  ├─ Validierung (Schema + Regeln)
│  └─ Signierung (Trust Layer)
│
├─ INPUT
│  ├─ Observation (roh)
│  ├─ Data (verifizierbar)
│  └─ Context (scope, source, timestamp)
│
├─ PRÜFUNGEN
│  ├─ Schema-Validierung (K500_STATE_SCHEMA)
│  ├─ Konsistenzprüfung (Indices/Limits/Chain)
│  ├─ Echo/Spiegelungsmarker (Wiederholung, Sekundärdominanz)
│  └─ Grenzmarker (unknowns/confidence gesetzt)
│
├─ OUTPUT
│  ├─ State_Object (v0.1)
│  ├─ Hash-Kette (hash_prev, hash_self)
│  └─ Signatur (ed25519 o.ä.)
│
├─ BETRIEBSREGELN
│  ├─ Pull-only Ausgabe
│  ├─ Append-only Archiv
│  ├─ Kein Recompute nach Freeze
│  └─ Deterministisch
│
├─ SICHERHEIT
│  ├─ Offline-Signing möglich
│  ├─ Public-Key-Verifikation extern
│  └─ Minimaler Angriffsraum
│
└─ STATUS
   ├─ K500-kompatibel
   ├─ hardened
   └─ v0.1