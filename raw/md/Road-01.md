# Punkt 1 · Research Ergebnis (Freeze/Thaw Canon+Kernel)

## Befund
- Frozen Versions müssen unveränderlich bleiben; Änderungen erzeugen neue Versionen (persistente Referenzen / Cache).   [oai_citation:11‡RFC-Editor](https://www.rfc-editor.org/rfc/rfc2291.html?utm_source=chatgpt.com)
- Versionierte Releases dürfen nicht nachträglich verändert werden; neue Version statt stiller Modifikation.  [oai_citation:12‡Semantic Versioning](https://semver.org/spec/v2.0.0-rc.2.html?utm_source=chatgpt.com)
- Immutability reduziert Drift; Zustände werden ersetzt statt geändert.  [oai_citation:13‡IBM](https://www.ibm.com/think/topics/immutable-infrastructure?utm_source=chatgpt.com)
- Stufen/Promotion-Prozesse (Standards) nutzen definierte Übergänge + Kriterien.  [oai_citation:14‡IETF Datatracker](https://datatracker.ietf.org/doc/html/rfc2026?utm_source=chatgpt.com)

## Standard: Freeze → Thaw → Freeze
### Definition
- Thaw ist ein explizites, zeitlich begrenztes Änderungsfenster.
- Frozen Zustände werden niemals überschrieben; nur neue Versionen.
- Alle Schritte sind append-only im History-Log.

### Gates
- Änderungen nur wenn canon.mutability=thawed
- Freeze nur wenn manifest+hash vorhanden und Determinismus geprüft

### Versioning (SemVer)
- MAJOR: Contract/Schema breaking
- MINOR: kompatible Erweiterung
- PATCH: Korrektur/Klarstellung ohne Bruch

## Ergebnis
Freeze/Thaw ist verpflichtender Governance-Mechanismus für Drift-Schutz, Reproduzierbarkeit und auditierbare Referenzzustände.