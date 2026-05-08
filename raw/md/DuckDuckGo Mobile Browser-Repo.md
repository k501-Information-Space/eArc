Unten ist ein rundes, logisch geschlossenes Fork-Konzept auf Basis der DuckDuckGo Mobile Browser-Repos (Android + Apple), mit sauberen API-Schnittstellen für K501, klarer Modultrennung, Privacy-Defaults und einem realistischen Upstream-Sync-Workflow.

  

Quellenbasis (OSS-Träger): DuckDuckGo Android App ist Apache-2.0  , DuckDuckGo iOS/macOS Browser + Shared Libraries liegen im apple-browsers Repo (ebenfalls Apache-2.0)  . DuckDuckGo erklärt außerdem, dass Apps/Extensions stark auf FOSS basieren  .

  

  

  

  

0) Zielbild in einem Satz

  

  

Ein DuckDuckGo-Fork, der als privacy-orientierter Browser erhalten bleibt, aber um einen deterministischen, lokal-first K501-Layer ergänzt wird (Append-only Frames, Export-only, optional HMRI-Gating).

  

  

  

  

1) Fork-Strategie: „Minimal invasive“ + Upstream-freundlich

  

  

  

1.1 Repos (2-Träger + 1-Core)

  

  

- Fork A: DuckDuckGo Android App (Träger)  
- Fork B: DuckDuckGo Apple Browsers (iOS/macOS) (Träger)  
- Neu: k501-core (plattformspezifische Bindings + gemeinsame Spezifikation)  
    

- Ziel: K501 nie „in“ die Browserlogik hineinfräsen, sondern als separaten Kernel halten.

-   
    

  

  

  

1.2 Grundprinzip

  

  

- Upstream-Code bleibt so unangetastet wie möglich.
- Integration über:  
    

- Events (Telemetry/State/Gate)
- Policies (Gate-Entscheidung)
- Storage (append-only)
- Export (user-initiated)

-   
    

  

  

Dadurch bleibt Merge-Konfliktfläche klein und Wartbarkeit hoch.

  

  

  

  

2) Architektur: klare Schichten, klare Zuständigkeiten

  

  

  

2.1 Layer-Diagramm (konzeptionell)

  

┌───────────────────────────────────────────────┐

│                 UI Layer                      │

│  Browser UI + K501 Screens (optional)          │

└───────────────────────┬───────────────────────┘

                        │

┌───────────────────────▼───────────────────────┐

│             Integration Facade                 │

│  (Platform Adapter: Android/iOS)               │

│  - emits Events                                │

│  - queries Gate Policy                         │

│  - triggers Export                             │

└───────────────────────┬───────────────────────┘

                        │

┌───────────────────────▼───────────────────────┐

│                   K501 Core                    │

│  - Frame schema + deterministic serialization   │

│  - append-only writer                           │

│  - index snapshots (lightweight)                │

│  - HMRI: state estimator + gate policy          │

└───────────────────────┬───────────────────────┘

                        │

┌───────────────────────▼───────────────────────┐

│                 Local Storage                  │

│  NDJSON (+ manifest/hash optional), export-only │

└───────────────────────────────────────────────┘

  

2.2 K501-Module (v0.1)

  

  

- k501-frame (Schema + Serializer)
- k501-store (append-only writer + rotation)
- k501-index (Presence/Type/Time minimal)
- k501-hmri (State Estimator + Gate Policy)
- k501-export (user-initiated export, sign optional)

  

  

  

  

  

3) API-Schnittstellen: sauber, klein, deterministisch

  

  

  

3.1 Event API (vom Browser → K501)

  

  

Ziel: Browser emittiert Events; K501 schreibt Frames.

  

Beispiel-Eventtypen (v0.1):

  

- FRAME_VISIT (URL/Domain, timestamp, tab-id)
- FRAME_VIEW (page visible, duration bucket)
- FRAME_CLICK (UI element id, destination class)
- HMRI_STATE (CALM/FOCUSED/OVERLOADED + scores)
- GATE_DECISION (PASS/BUFFER/SUPPRESS + reason code)
- EXPORT_ACTION (user initiated, format)

  

  

Contract:

  

- Alle Felder strikt typisiert.
- Keine PII by default.
- Deterministische Serialisierung (Canonical JSON / dein K501-Standard).

  

  

  

3.2 Gate Policy API (K501 → Browser)

  

  

Browser fragt vor „interruptiven“ Dingen:

  

- Notification anzeigen?
- Badge erhöhen?
- Banner einblenden?
- New-tab content inject?

  

  

Call:

  

- Input: Context { state, priority, channel, urgency, user_override }
- Output: Decision { PASS|BUFFER|SUPPRESS, next_check_at, reason }

  

  

  

3.3 Storage API (K501 intern)

  

  

- append(frame) garantiert:  
    

- monotone time anchors (UTC+Unix)
- append-only sequence
- optional chain hash (later phase)

-   
    

  

  

  

3.4 Export API (User-only)

  

  

- Export ist ausschließlich:  
    

- manuell über UI
- oder lokal in „share sheet“ (iOS) / „share intent“ (Android)

-   
    
- Exportformate (v0.1):  
    

- frames.ndjson
- manifest.json (counts + range + optional hash placeholders)

-   
    

  

  

  

  

  

4) UI-Konzept: minimal, aber „rund“

  

  

  

4.1 K501 Entry Points (v0.1)

  

  

- Settings → „K501 / Local Archive“  
    

- Toggle: ON/OFF
- Storage: size, retention window (z. B. 7/30/90 Tage)
- Export: „Export last 24h / 7d / all“

-   
    
- Optional Quick Panel:  
    

- HMRI State (CALM/FOCUSED/OVERLOADED)
- Buffered items count
- „Peek Batch“

-   
    

  

  

  

4.2 Nicht verhandelbar (UX/Trust)

  

  

- „OFF means OFF“ (keine verdeckte Speicherung)
- „Delete local archive“ ist sichtbar und final (mit klarer Warnung)
- Kein Cloud-Sync in v0.1 (sonst eskaliert Trust & Threat Model)

  

  

  

  

  

5) Privacy- & Threat-Model Defaults

  

  

  

5.1 Default: Local-only, Export-only

  

  

- Frames bleiben auf dem Gerät.
- Keine automatischen Uploads.
- Keine Background-Telemetrie nach außen.

  

  

  

5.2 Datenminimierung

  

  

- URLs standardmäßig auf Domain + path class reduzieren (oder hashen, optional)
- Keine Inhalte, keine Texteingaben
- Zeitanker ja, aber keine Geo-Daten

  

  

  

5.3 „Staat“-Kontext (dein Satz)

  

  

Wenn du „Symbiose für den Staat“ meinst: Für institutionelle Nutzung brauchst du:

  

- Auditierbarkeit (OSS + deterministische Logs)
- Policy-Profiles (z. B. „Agency Mode“: strengere Defaults)
- klare Export/Import-Prozeduren

  

  

Das ist machbar, aber erst nach v0.1.

  

  

  

  

6) Plattform-spezifische Integration (praktisch)

  

  

  

Android (DuckDuckGo Android Fork)  

  

  

  

- Hook Points:  
    

- Browser events (tabs, page load, visibility)
- Notification handling (Batching)
- Optional: App Tracking Protection (nur beachten: nutzt VPN-Slot; Integration muss konfliktfrei bleiben)  

-   
    

  

  

  

iOS/macOS (apple-browsers Fork)  

  

  

  

- Hook Points:  
    

- Navigation lifecycle
- UI layer for K501 settings/export
- Shared libs nutzen (Repo enthält shared libraries)  

-   
    

  

  

  

  

  

7) Upstream-Sync & Wartbarkeit

  

  

  

7.1 Patch-Set statt „Big Rewrite“

  

  

- K501 Integration als klar abgegrenzte Commits:  
    

1. Add k501-core dependency
2. Add Event Facade
3. Add minimal UI
4. Add export
5. Add HMRI gating (optional feature flag)

-   
    

  

  

  

7.2 Release Engineering (v0.1)

  

  

- Versioning: v0.1.x
- Changelog:  
    

- Upstream base revision
- K501 module version

-   
    
- CI:  
    

- build + tests
- deterministic serialization tests (golden files)

-   
    

  

  

  

  

  

8) Rechtliches/Branding (kurz, aber wichtig)

  

  

Der Code ist Apache-2.0 offen  , aber Marken/Branding sind ein separater Layer.

Heißt praktisch: Fork braucht i. d. R. eigenes Branding (Name/Icon), selbst wenn Code legal forkbar ist.

  

  

  

  

9) Konkreter v0.1 Scope (damit es „rund läuft“)

  

  

v0.1 muss liefern:

  

1. K501 ON/OFF
2. append-only local frames (VISIT/VIEW/CLICK)
3. Export (NDJSON + manifest)
4. Optional: HMRI State Estimator (nur lokal)
5. Optional: Gate für Notifications (Batching)

  

  

v0.1 muss NICHT liefern:

  

- Cloud, Sync, AI, multi-device, komplexe Hash-Chains

  

  

  

  

  

10) Nächster Schritt

  

  

Wenn du willst, mache ich dir jetzt als Folgeoutput ein Blueprint-Dokument (Copy/Paste-fähig) mit:

  

- Event-Schema (JSON fields)
- Gate decision table (Priority × State → Action)
- Storage layout (files, rotation)
- UI string list (Settings + Panels)
- v0.1 Testplan (Determinismus + Privacy)

  

  

Sag nur: „Blueprint jetzt“ oder „erst Event-Schema“.