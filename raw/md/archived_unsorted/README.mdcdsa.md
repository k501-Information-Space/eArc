# K500 Gatekeeper (K500G) — Interface-only Reference v0.1

K500G ist ein gehärteter Gatekeeper auf Base-Kernel-Ebene.
Dieses Repository veröffentlicht **nur die Schwelle**:
- Interface / Protokoll
- State-Schema
- Validierungsregeln (konzeptionell)
- Trust-Layer (Hash/Signatur-Prinzip)

## Was das ist
- Ein **referenzieller Standard** für verifizierbare Zustandsobjekte (State Objects)
- Ein **Gate**: validiert, begrenzt, signiert
- Ein **hardened** Minimal-Kern ohne operative Steuerung

## Was das nicht ist
- Keine Referenz-Implementierung
- Keine Runtime, kein Service, kein Daemon
- Kein K1000, kein K5000
- Keine Prognosen, keine Empfehlungen, keine Automatik

## Design-Prinzipien
- Pull-only
- Append-only
- Deterministisch
- Verifizierbar (Hash/Signatur)
- Minimaler Angriffsraum

## Ziel
Wir stellen eine klare Schwelle bereit.
Was darüber entsteht, ist bewusst offen: Implementierungen, Tools, Integrationen, Visualisierungen.

## Dateien
- SPEC/K500G_INTERFACE.md
- SPEC/K500G_STATE_SCHEMA.yaml
- SPEC/K500G_VALIDATION_RULES.md
- SPEC/K500G_TRUST_LAYER.md
- EXAMPLES/state_example_v0.1.json

## Status
v0.1 — Interface-only Reference