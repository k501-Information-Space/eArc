---
id: kernel_build_prognose_public_alpha
type: plan
status: prognose
scope: public_alpha
kernel: eArc Kernel 5000 v3.0
codename: Trinity United
priority: build
version: 1.0
author: eArc
date: 2026-01-08
---

# Build-Prognose · Trinity Public Alpha

## Ausgangslage
- Kernel v3.0 vollständig definiert und **FROZEN**
- Feature-Set abgeschlossen
- Libraries kanonisch
- APIs gehärtet
- Kein UI-Fokus, text-first
- Ziel: **funktionierende Public Alpha**, kein Produkt

---

## Phase A · Core & API
**Dauer:** 5–7 Tage

**Inhalt:**
- Domain Model (eArc Item / Frame / Series)
- Lifecycle (hold / release / archive)
- Public API (Frames, Series)
- Network Echo (Ping)
- Alpha Token Auth (minimal)

---

## Phase B · Feeds & Projektion
**Dauer:** 2–3 Tage

**Inhalt:**
- RSS / Atom / JSON Feed Generierung
- Feed-IDs (latest / shared / series)
- ETag / Last-Modified Caching
- Read-only Tests

---

## Phase C · Export & Archiv
**Dauer:** 2–3 Tage

**Inhalt:**
- Pandoc Integration
- PDF & EPUB Export-Profile
- Dynamischer Satzspiegel
- Archiv-Workflow

---

## Phase D · Security & Stabilität
**Dauer:** 1–2 Tage

**Inhalt:**
- HTML Sanitization
- Rate Limiting
- Payload Limits
- Graceful Error Handling

---

## Phase E · Metrika Alpha & Reports
**Dauer:** 2–3 Tage

**Inhalt:**
- Metrika Persona (aggregiert)
- Metrika Statistica (strukturell)
- Alpha Experience Reports
- Interne Report-Endpoints

---

## Gesamtprognose

### Optimistisch
- **12–14 Tage**

### Realistisch
- **15–18 Tage**

### Konservativ
- **3–4 Wochen**

---

## Erfolgsfaktoren
- Keine Feature-Erweiterungen
- Keine Revisionsschleifen
- Entscheidungen bleiben gültig
- Ruhe vor Geschwindigkeit

---

## Definition of Done (Public Alpha)
- Frames erstellen, halten, teilen, archivieren
- Serien funktionsfähig
- Feeds erreichbar und cachebar
- Echo Ping antwortet
- Exporte (PDF/EPUB) lauffähig
- Metrika Reports erzeugbar
- Alpha Hinweis sichtbar

---

As I State Iinkognit0.