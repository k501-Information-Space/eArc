# PATH: 00_Grundsaetze/web/earc-website-konzept.yaml
# KANONISCHER KONZEPT-OUTPUT — iInkognit0 / eArc Website
# Stand: 2026-01-06
# Status: aktiv (Konzept), Umsetzung iterativ

project:
  name: "iInkognit0"
  system: "eArc – Das Ewige Archiv"
  principle: "Ordnung vor Inhalt · Archiv vor Aktion"
  style:
    palette: "black_on_white"
    shapes: "square_only"
    borders: "thin_black"
    motion: "allowed_for_ticker_and_manifest_only"
    no_rgb: true
    no_glow: true
    no_glass: true
    no_rounding: true

domains:
  origin:
    url: "https://iinkognit0.de/"
    role: "Ursprung (Referenz, Quelle)"
  key_pages:
    earc:
      url: "https://iinkognit0.de/earc/"
      role: "eArc-Seite (Archiv-Kernseite)"
    podcast:
      url: "https://iinkognit0.de/podcast/"
      role: "Podcast-Seite (Stimme auf der Website)"

external_channels:
  substack:
    url: "https://iinkognit0.substack.com"
    rss: "https://iinkognit0.substack.com/feed"
    role: "Schrift / öffentliches Gedächtnis"
  podcast_distribution:
    hub:
      url: "https://pod.link/1862625280"
      role: "Plattform-Hub (Verteilerlink)"
    master_rss:
      url: "https://anchor.fm/s/10d156d24/podcast/rss"
      role: "Stimme-Ursprung (kanonischer Podcast-Feed)"

rss:
  earc_canonical:
    url: "https://iinkognit0.de/rss"
    name: "eArc RSS"
    status: "kanonisch"
    purpose: "Single Source of Truth für Website-Ticker + externe Syndikation"
    contains_layers_in_order:
      - layer: "frames_news_loop"
        description: "Website/Archiv-Nachrichten (Frames) als oberste Items"
        source_policy: "origin_first"
      - layer: "substack"
        description: "Substack-Posts (Schrift)"
        source_policy: "syndicated"
      - layer: "podcast_master"
        description: "Podcast Master RSS (Anchor/Spotify for Podcasters)"
        source_policy: "syndicated"
    notes:
      - "Apple/Spotify/Amazon sind Verteiler, keine Primärquellen."
      - "Ticker-Content soll aus eArc RSS stammen (automatisch), Animation bleibt CSS."
      - "RSS-Autoupdate (Frames) ist späterer Schritt; erst Struktur, dann Automatik."

website_startpage:
  type: "one_page"
  url: "https://iinkognit0.de/"
  modules_order:
    - id: "header"
      name: "eArc Header Module"
      position: "top_sticky"
      visible_brand: "eArc_only"
      nav:
        items:
          - label: "eArc"
            href: "https://iinkognit0.de/earc/"
        mobile: "must_work"
      rules:
        - "Kein Frames-Label im Header"
        - "Kein RGB/Gradient"
        - "Schwarze, eckige, schmale Linien"
    - id: "newsloop"
      name: "Frames Newsloop (Ticker)"
      position: "top_section"
      layout: "label_left + ticker_right"
      animation: "horizontal_infinite_loop"
      content_source:
        primary: "https://iinkognit0.de/rss"
        filter: "frames_news_loop_only (future)"
      fallback_text: "allowed"
      rules:
        - "Ticker ist nicht Deko; er ist Live-Ansicht des eArc RSS."
        - "Animation via CSS; Inhalte später automatisch via RSS."
    - id: "identity"
      name: "Projekt-Identität"
      content:
        h1: "iInkognit0"
        h2: "Das Ewige Archiv"
        short_statement: "Ein ruhiger Ursprung. Ordnung vor Inhalt. Archiv vor Aktion."
    - id: "manifest_scroll"
      name: "Manifest Bottom-to-Top"
      position: "center_section"
      animation: "vertical_infinite_rise"
      content: "FULL_MANIFEST_TEXT (unchanged, duplicated for seamless loop)"
      rules:
        - "Vollständiges Manifest, keine Kürzung."
        - "Loop durch Duplikat-Block (nahtlos)."
        - "prefers-reduced-motion respektieren."
    - id: "links"
      name: "Trägerliste (Links)"
      items:
        - label: "eArc · Das Ewige Archiv"
          href: "https://iinkognit0.de/earc/"
        - label: "Podcast"
          href: "https://iinkognit0.de/podcast/"
        - label: "Podcast (alle Plattformen via Pod.link)"
          href: "https://pod.link/1862625280"
        - label: "Substack (Schrift / Archiv)"
          href: "https://iinkognit0.substack.com"
    - id: "rss_links"
      name: "RSS Links"
      items:
        - label: "eArc RSS (eigener Feed)"
          href: "https://iinkognit0.de/rss"
        - label: "Substack RSS"
          href: "https://iinkognit0.substack.com/feed"
        - label: "Podcast RSS (Master / Anchor)"
          href: "https://anchor.fm/s/10d156d24/podcast/rss"

implementation_notes:
  wordpress:
    integration_mode: "Custom HTML Block on Startpage"
    css: "inline in block or theme customizer"
    menu: "Theme menu contains only 'eArc' (Primary)"
  accessibility:
    reduced_motion: true
    contrast: "black_on_white"
  invariants:
    - "One-page Start bleibt minimal."
    - "Header zeigt nur eArc."
    - "Kein RGB, kein Glow, keine runden Ecken."
    - "RSS ist Quelle; Ticker ist Ansicht."