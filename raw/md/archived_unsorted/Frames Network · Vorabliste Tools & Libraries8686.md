# Frames Network · Vorabliste Tools & Libraries
## Recherche-Stand (Analyse-Modus)

**Status:** Vorab-Recherche  
**Zweck:** Überblick & Vorbereitung  
**Hinweis:** Noch keine Auswahl, keine Entscheidung

---

## Feed Parsing & Lesen (Inbound)

### Python
- **feedparser**
  - RSS & Atom (RSS 0.x / 1.0 / 2.0, Atom 0.3 / 1.0)
  - stabil, weit verbreitet
- **atoma**
  - moderner RSS/Atom/JSON-Feed Parser
  - Python 3, klar strukturiert

### Node.js
- **@rowanmanning/feed-parser**
  - robuster RSS/Atom Parser
  - geeignet für serverseitige Verarbeitung

### Rust
- **feedparser-rs**
  - performanter RSS/Atom Parser
  - sicher, speicherstabil

---

## Feed Generierung (Outbound)

### Node.js
- **feed**
  - erzeugt RSS 2.0, Atom 1.0, JSON Feed
  - geeignet für kanonische Exporte

---

## Feed-Synchronisation & Metadaten

- **FeedSync**
  - Erweiterung von RSS/Atom
  - Versions- & Sync-Informationen
- **WebSub (PubSubHubbub)** *(optional)*
  - Push-Signalisierung für Feeds
  - nicht zwingend, nur perspektivisch

---

## Transport & Verteilung

- **Syncthing**
  - dezentrale Datei-Synchronisation
  - lokal-first, kein zentraler Server
- **Git / rsync**
  - alternative, kontrollierte Sync-Modelle

---

## Dezentraler Speicher (optional, langfristig)

- **IPFS**
  - content-adressierter Speicher
  - P2P-Verteilung
  - geeignet für Archiv-Strukturen

---

## Netzwerk- & Struktur-Analyse (später)

- **Pyvis / VisJS**
  - Visualisierung von Netzwerken
  - Frames als Knoten
- **Raphtory**
  - temporale Graph-Engine
  - Analyse von Netzwerken über Zeit

---

## Feed-Rezeption & Tests

- **RSS Guard**
  - Desktop Feed Reader
  - RSS / Atom / JSON Feed
  - nützlich für Validierung

---

## Zusammenfassung nach Funktion

### Inbound
- feedparser
- atoma
- feed-parser (Node)
- feedparser-rs

### Outbound
- feed (RSS / Atom Generator)

### Sync / Transport
- Syncthing
- Git / rsync

### Netzwerk / Analyse
- Pyvis / VisJS
- Raphtory

### Optional / Langfristig
- FeedSync
- WebSub
- IPFS

---

**Nächster Schritt (nur auf Anweisung):**
- Vollständige Analyse
- Auswahl & Bewertung
- Zuordnung zu Frames / Packs / SuperPacks