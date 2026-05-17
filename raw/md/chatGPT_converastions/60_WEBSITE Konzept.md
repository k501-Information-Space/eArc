# 60_WEBSITE Konzept

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## user · 2026-01-21T09:19:55.424431 UTC

60_WEBSITE – iinkognit0.de

---

## system · 2026-01-21T09:19:59.085282 UTC



---

## assistant · 2026-01-21T09:19:59.614808 UTC

## **60_WEBSITE – iinkognit0.de**

image_group{"query":["iinkognit0.de website","minimalist archive website black white","futuristic minimal typography website","cyberpunk minimal web design"]}

### **Status**
- **Kanonische Domain:** **entity["organization","iinkognit0.de","archive website project"]**
- **Rolle:** Read-only Referenz & Ursprung des Projekts  
- **Modus:** ruhig · stabil · dauerhaft  
- **Prinzip:** *archive before action*

---

### **Zweck**
- Öffentlicher **Einstiegspunkt** („Ein-Klick-Verstehen“)
- **Archiv & Referenz**, keine Plattform
- **Orientierung** statt Dynamik

---

### **Struktur (final, schlank)**
1. **Start**  
   Kurzmanifest · Typografie-Standard · Haltung
2. **eArc – Das Ewige Archiv**  
   Ordnung · Prinzipien · Referenztexte
3. **Podcast Iinkognit0**  
   Episoden · Resonanz (keine Kommentare)
4. **Frames Newsloop**  
   Manuell gepflegte Status-Frames (maßvoll)
5. **RSS / Signale**  
   Passiver Verteiler
6. **Formalia**  
   Impressum · Datenschutz

---

### **Design-Leitlinien**
- **Schwarz / Weiß**, hohe Lesbarkeit  
- **Futuristische, ruhige Typografie**  
- **Keine Animationen**, kein Scroll-Lärm  
- **Identische Seitentitel = H1**, Untertitel: *Das Ewige Archiv*

---

### **Technik & Regeln**
- **Read-only**, **append-only** Inhalte  
- **Keine Automatik**, kein Push, kein Login  
- **Manuelle Querverlinkung**  
- **RSS/Atom aktiv** (passiv, referenziell)

---

### **Abgrenzung**
- **incognito.de** existiert separat → **nicht vermischen**  
- Kurzlebige Plattformen **nicht Teil** der Website

---

### **Aktueller Zustand**
- **Online & funktionsfähig**
- **Baseline eingefroren** (Änderungen nur nach expliziter Freigabe)

Wenn du möchtest, liefere ich als Nächstes:
- eine **Startseiten-Kurzfassung (100–150 Wörter)**  
- oder ein **exaktes Seiten-Sitemap.md** für das Archiv.

---

## assistant · 2026-01-21T09:19:59.744511 UTC



---

## user · 2026-01-21T09:21:02.171769 UTC

60_WEBSITE – iinkognit0.de

SCOPE:
- Nur Website: Seitenstruktur, URLs, Navigation, HTML/CSS, WordPress-Beiträge, Feeds (RSS/Atom), Embed, Performance, Security-Basics.
- Keine Kernel-/DB-Arbeit hier.

CURRENT FACTS:
- Kanonische Domain: https://iinkognit0.de/
- Andere Seiten sind WordPress-Beiträge (inkl. eArc-Feed).
- Ziel: read-only Einstieg, Ruhe, Archiv vor Aktion.
- Standard: Titel/Dateiname zuerst bei strukturierten Outputs.

TASK NOW:
- Erstelle /eArc-Feed als WP-Beitrag + ggf. statische Ankerseite.
- Liefere HTML-Blöcke (WP Custom HTML) + klare Linkstruktur.

NEXT STEP:
- Liste der existierenden Seiten/Beiträge + gewünschte Menü-Reihenfolge.

---

## system · 2026-01-21T09:21:05.549966 UTC



---

## assistant · 2026-01-21T09:21:05.560923 UTC



---

## tool · 2026-01-21T09:21:12.455621 UTC



---

## tool · 2026-01-21T09:21:12.459129 UTC



---

## tool · 2026-01-21T09:21:16.727203 UTC



---

## tool · 2026-01-21T09:21:18.784569 UTC



---

## tool · 2026-01-21T09:21:24.703044 UTC



---

## tool · 2026-01-21T09:21:24.705944 UTC



---

## tool · 2026-01-21T09:21:27.746646 UTC



---

## tool · 2026-01-21T09:21:33.574796 UTC



---

## tool · 2026-01-21T09:21:33.578409 UTC



---

## tool · 2026-01-21T09:21:34.120813 UTC

Empty search results
No results were found for the provided queries

---

## tool · 2026-01-21T09:21:36.643198 UTC



---

## tool · 2026-01-21T09:21:36.647071 UTC



---

## tool · 2026-01-21T09:21:41.960074 UTC



---

## tool · 2026-01-21T09:21:47.617255 UTC



---

## tool · 2026-01-21T09:21:54.130960 UTC



---

## tool · 2026-01-21T09:21:54.133840 UTC



---

## assistant · 2026-01-21T09:21:54.764169 UTC

60_WEBSITE/eArc-Feed — WP-Beitrag + Ankerseite (HTML-Blöcke)

### 1) IST-Zustand (sichtbar von außen)
**Quelle:** Navigation auf Startseite citeturn1view0  
- Start: `https://iinkognit0.de/` citeturn1view0  
- eArc-Seite (WP-Beitrag): `https://iinkognit0.de/earc/` citeturn2view2  
- eArc-Feed (WP-Beitrag, aktuell praktisch leer): `https://iinkognit0.de/earc-feed/` citeturn8view0  
- Weitere (WP-Beiträge):  
  - `https://iinkognit0.de/podcast/` citeturn2view3  
  - `https://iinkognit0.de/architektur/` citeturn7view0  
  - `https://iinkognit0.de/philosophie/` citeturn7view1  
  - `https://iinkognit0.de/manifesto/` citeturn0search1  
  - `https://iinkognit0.de/kontakt/` citeturn7view2  
  - `https://iinkognit0.de/impressum/` citeturn7view3  

---

### 2) TASK NOW — eArc-Feed als WP-Beitrag befüllen (Custom HTML Blocks)
**WP-Beitrag:** `https://iinkognit0.de/earc-feed/` citeturn8view0  

> **In WordPress:** Beitrag „eArc-Feed“ → **Block hinzufügen → „Custom HTML“** → folgende Blöcke einfügen (1:1).

#### BLOCK A — Intro (ruhig, read-only)
```html
<section class="earc-feed">
  <h2>eArc-Feed</h2>
  <p>
    Dies ist der öffentliche, ruhige Zugang zu Updates aus dem <strong>eArc – Das Ewige Archiv</strong>.
    Kein Login. Kein Feed-Stress. Nur Referenzen.
  </p>
</section>
```

#### BLOCK B — Feed-Links (mit Fallbacks)
*(WP-Feeds sind je nach Setup unterschiedlich. Darum mehrere „kanonische Kandidaten“ – du lässt nur die funktionierenden stehen.)*
```html
<section class="earc-feed-links">
  <h3>RSS / Atom</h3>
  <ul>
    <li><a href="/feed/" rel="alternate" type="application/rss+xml">Haupt-Feed (WordPress Standard) – /feed/</a></li>
    <li><a href="/?feed=rss2" rel="alternate" type="application/rss+xml">Fallback – /?feed=rss2</a></li>
    <li><a href="/comments/feed/" rel="alternate" type="application/rss+xml">Kommentare-Feed (optional) – /comments/feed/</a></li>
  </ul>

  <hr />

  <h3>eArc-spezifisch (optional)</h3>
  <p>Wenn du eArc als <em>Kategorie</em> oder <em>Tag</em> führst, nutze einen dieser Feeds:</p>
  <ul>
    <li><a href="/category/earc/feed/" rel="alternate" type="application/rss+xml">Kategorie-Feed – /category/earc/feed/</a></li>
    <li><a href="/tag/earc/feed/" rel="alternate" type="application/rss+xml">Tag-Feed – /tag/earc/feed/</a></li>
  </ul>
</section>
```

#### BLOCK C — Copy/Paste-Links (WhatsApp/Signal-freundlich)
```html
<section class="earc-feed-copy">
  <h3>Copy &amp; Paste</h3>

  <p><strong>Website (kanonisch):</strong><br>
    <code>https://iinkognit0.de/</code>
  </p>

  <p><strong>eArc-Feed-Seite:</strong><br>
    <code>https://iinkognit0.de/earc-feed/</code>
  </p>

  <p><strong>Feed (Standard):</strong><br>
    <code>https://iinkognit0.de/feed/</code>
  </p>

  <p style="opacity:.85">
    Hinweis: Wenn <code>/feed/</code> nicht greift, nutze <code>/?feed=rss2</code>.
  </p>
</section>
```

#### BLOCK D — Embed (optional, minimal)
*(Nur wenn du wirklich ein „Live“-Embed willst. Sonst weglassen für Ruhe.)*
```html
<section class="earc-feed-embed">
  <h3>Embed (optional)</h3>
  <p>Für ruhige Leser: Feed lieber im Reader abonnieren statt auf der Website „scrollen“.</p>
</section>
```

---

### 3) Ggf. statische Ankerseite (empfohlen)
**Neue WP-Seite:** `/rss/` (Titel: „RSS“)  
Ziel: ultrakurzer Einstiegspunkt, der nur Links enthält (kein Blog-Layout, keine Sidebar-Wildnis).

**Custom HTML (kompakt):**
```html
<section class="rss-anchor">
  <h2>RSS</h2>
  <p>Read-only Signale. Kein Push. Kein Konto.</p>

  <ul>
    <li><a href="/earc-feed/">eArc-Feed (Seite)</a></li>
    <li><a href="/feed/" rel="alternate" type="application/rss+xml">Haupt-Feed – /feed/</a></li>
    <li><a href="/?feed=rss2" rel="alternate" type="application/rss+xml">Fallback – /?feed=rss2</a></li>
  </ul>
</section>
```

---

### 4) Linkstruktur (klar, ruhig, „read-only entry“)
**Primär-Navi (empfohlen, minimal):**
1. Startseite `/`
2. Das Ewige Archiv `/earc/` citeturn2view2
3. Podcast `/podcast/` citeturn2view3
4. eArc-Feed `/earc-feed/` citeturn8view0
5. Kontakt `/kontakt/` citeturn7view2
6. Impressum `/impressum/` citeturn7view3

**Sekundär (nicht im Hauptmenü, aber intern verlinkt):**
- Architektur `/architektur/` citeturn7view0
- Philosophie `/philosophie/` citeturn7view1
- Manifesto `/manifesto/` citeturn0search1

---

### 5) Security & Ruhe-Basics (Website-only, WP)
- **Kommentare deaktivieren** (für read-only): Beitragsebene + global unter „Diskussion“ (Kommentarformular ist aktuell sichtbar). citeturn0search1turn7view3  
- **XML-RPC aus**, falls nicht benötigt (häufiger Angriffsvektor).  
- **REST API User Enumeration** begrenzen (z.B. `/wp-json/wp/v2/users`), wenn öffentlich erreichbar. citeturn6search2  
- **Updates** (WP Core/Theme/Plugins), **starke Admin-Logins**, **Limit Login Attempts**, optional WAF.

---

## NEXT STEP — Liste existierender Seiten/Beiträge + gewünschte Menü-Reihenfolge
Ich habe die von außen sichtbaren Kernseiten oben bereits gesammelt (inkl. URLs).  
Damit ich die **finale Menü-Reihenfolge + interne Crosslinks** exakt festziehen kann, poste einfach deine gewünschte Reihenfolge als Liste (z.B. „Start, eArc, Podcast, …“) — dann liefere ich dir die **fertige Navigationsstruktur inkl. HTML-Menüblock (Custom HTML)**, passend zu deinem ruhigen Layout.

---

## user · 2026-01-21T09:23:39.148202 UTC

Pause Unix Epoch
1768987404
Time (UTC)
Wed Jan 21 09:23:24 2026 UTC
Time (Europe/Amsterdam)
Wed Jan 21 10:23:24 2026 CET


---

## system · 2026-01-21T09:23:39.773691 UTC



---

## system · 2026-01-21T09:23:39.835162 UTC



---

## assistant · 2026-01-21T09:23:39.878078 UTC

**Pause bestätigt.** ⏸️

**Unix Epoch:** 1768987404  
**UTC:** Wed Jan 21 09:23:24 2026  
**Europe/Amsterdam:** Wed Jan 21 10:23:24 2026 CET

Status: **HOLD** · keine Aktionen · Kontext bleibt unverändert.  
Wenn du fortsetzen willst, sende einfach **„Resume“** (oder den nächsten Schritt).

---

## user · 2026-01-21T10:21:04.551576 UTC

Website Fonts Bitte obitron nutzen

---

## system · 2026-01-21T10:21:04.874476 UTC



---

## system · 2026-01-21T10:21:04.963056 UTC



---

## assistant · 2026-01-21T10:21:04.976769 UTC

Verstanden. **Website-Font: Orbitron** ✅  
Kurz, sauber, **nur Website** (HTML/CSS, WordPress-tauglich).

---

## Option A — **Empfohlen (Google Fonts, schnell & stabil)**

### 1) **Im `<head>` laden**  
*(WP: Customizer → Zusätzliches CSS **oder** Theme → Header)*

```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;500;600;700&display=swap" rel="stylesheet">
```

### 2) **Globales CSS setzen**
*(WP: Design → Customizer → Zusätzliches CSS)*

```css
/* =========================
   GLOBAL FONT — ORBITRON
   ========================= */

:root{
  --font-primary: 'Orbitron', system-ui, -apple-system, BlinkMacSystemFont, sans-serif;
}

html, body{
  font-family: var(--font-primary);
  font-weight: 400;
  letter-spacing: 0.02em;
}

/* Headlines etwas markanter */
h1, h2, h3, h4, h5, h6{
  font-family: var(--font-primary);
  font-weight: 600;
  letter-spacing: 0.04em;
}

/* Ruhige Lesbarkeit für Fließtext */
p, li, blockquote{
  line-height: 1.6;
  font-weight: 400;
}

/* Code/Meta optional neutral */
code, pre{
  font-family: ui-monospace, SFMono-Regular, Menlo, Consolas, monospace;
}
```

---

## Option B — **Nur Headlines Orbitron (maximale Ruhe)**  
*(Wenn Fließtext neutral bleiben soll)*

```css
h1, h2, h3, h4, h5, h6{
  font-family: 'Orbitron', system-ui, sans-serif;
  letter-spacing: 0.04em;
}
```

---

## Option C — **Lokal hosten (kein externer Call)**
1. Orbitron als `.woff2` laden (z. B. `orbitron-regular.woff2`, `orbitron-semibold.woff2`)
2. In dein Theme: `/fonts/`
3. CSS:

```css
@font-face{
  font-family: 'Orbitron';
  src: url('/wp-content/themes/DEIN-THEME/fonts/orbitron-regular.woff2') format('woff2');
  font-weight: 400;
  font-style: normal;
  font-display: swap;
}
```

---

## Performance & Ordnung
- **`display=swap`** aktiv → kein FOIT  
- **Nur benötigte Gewichte** (400/600 reichen meist)  
- **Keine Animationen** → ruhig & archivfest

Wenn du willst, passe ich es **exakt auf dein bestehendes Global-CSS** an (z. B. nur Start/eArc/Feed unterschiedlich gewichten).

---

## user · 2026-01-21T10:24:36.188003 UTC

Das ist zurzeit in: zusätzliche css: /* =====================================================================
   eArc · GLOBAL CSS · V1.0 · FINAL
   Scope: Gesamte Website (WordPress → Customizer → Zusätzliches CSS)
   Prinzip:
   - Globales CSS = Fundament
   - Module bauen darauf auf
   - Schwarz / Weiß · Ruhig · Futuristisch · Dauerhaft
   ===================================================================== */

/* =========================
   ROOT · SYSTEMVARIABLEN
   ========================= */
:root{
  --paper:#ffffff;
  --ink:#000000;
  --line:#000000;
  --border:1px;

  --max-width:1100px;

  --font-system:'Inter', system-ui, -apple-system, BlinkMacSystemFont, sans-serif;
  --font-future:'Orbitron', system-ui, sans-serif;

  --space-xs:6px;
  --space-s:10px;
  --space-m:16px;
  --space-l:24px;
  --space-xl:32px;
}

/* =========================
   RESET · BASIS
   ========================= */
*{
  box-sizing:border-box;
}
Analysieren 
html,body{
  margin:0;
  padding:0;
  background:var(--paper);
  color:var(--ink);
  font-family:var(--font-system);
  line-height:1.6;
}

img{
  max-width:100%;
  height:auto;
}


---

## assistant · 2026-01-21T10:24:37.417096 UTC

Du hast **Orbitron schon als `--font-future`** drin – aktuell nutzt die Website aber **`--font-system` (Inter)**, weil `html,body` auf `var(--font-system)` steht.

Hier sind zwei saubere Wege (ohne Kernel/DB, nur WP/CSS):

---

## Variante 1 (Hard Switch): **Alles auf Orbitron**
**Ändere nur diese Zeile** in `html,body`:

```css
html,body{
  margin:0;
  padding:0;
  background:var(--paper);
  color:var(--ink);
  font-family:var(--font-future); /* <- HIER: Orbitron global */
  line-height:1.6;
}
```

Optional (für ruhigere Lesbarkeit):
```css
html,body{ letter-spacing:0.02em; }
```

---

## Variante 2 (Empfohlen): **Orbitron für Headlines + UI, Inter für Fließtext**
So bleibt es ruhiger lesbar, aber “futuristisch” wirkt trotzdem stark.

**Lass `html,body` wie es ist** (Inter) und füge direkt darunter hinzu:

```css
/* Orbitron nur für Headlines */
h1,h2,h3,h4,h5,h6{
  font-family:var(--font-future);
  font-weight:600;
  letter-spacing:0.04em;
}

/* Optional: Menü/Buttons auch futuristisch */
nav, .wp-block-navigation, button, .wp-element-button{
  font-family:var(--font-future);
  letter-spacing:0.03em;
}
```

---

## Wichtig: Orbitron muss geladen werden (sonst fällt es auf system-ui zurück)
Du hast Orbitron als Variable gesetzt, aber **CSS lädt die Font nicht**.

### Schnellste WP-Variante (ohne Theme-Dateien):
**Customizer → Zusätzliches CSS** kann keine `<link>`-Tags laden.  
Du brauchst einen von diesen Wegen:

**A) Plugin “Insert Headers and Footers” / “WPCode”** → **Header**:
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&display=swap" rel="stylesheet">
```

**B) Theme Customizer (falls vorhanden):** “Zusätzlicher HTML/Head Code”  
**C) Child Theme:** in `functions.php` per `wp_enqueue_style` (wenn du willst, gebe ich den Snippet).

---

## Minimaler Patch (copy/paste)
Wenn du **Orbitron überall** willst **und** es richtig laden willst:

1) **Header-Link einfügen** (WPCode / Header-Injector)  
2) **Nur diese CSS-Zeile ändern**:
```css
font-family:var(--font-future);
```

Sag mir kurz: **Willst du Orbitron wirklich für Fließtext auch (Variante 1) oder nur für Überschriften (Variante 2)?**

---

## system · 2026-01-21T10:24:37.676701 UTC



---

## user · 2026-01-21T10:25:32.815490 UTC

Gib mir mal bitte ein komplettes Copy and Paste für den CSS, den globalen. Ein Copy and Paste, den füge ich dann ein und dann ist Schluss. Danke. Dann haben wir nämlich den globalen Standard für alle Webseiten. Danke.

---

## system · 2026-01-21T10:25:33.543253 UTC



---

## system · 2026-01-21T10:25:33.595289 UTC



---

## assistant · 2026-01-21T10:25:33.650261 UTC

Alles klar. **Ein kompletter, sauberer GLOBAL-CSS zum Copy & Paste.**  
➡️ **So einfügen:** *WordPress → Customizer → Zusätzliches CSS*  
➡️ Danach **ist der globale Standard gesetzt**. Ruhe. Ende.

---

```css
/* =====================================================================
   eArc · GLOBAL CSS · V1.1 · CANONICAL
   Scope: Gesamte Website (WordPress → Customizer → Zusätzliches CSS)
   Prinzip:
   - Globales CSS = Fundament
   - Read-only · Archiv vor Aktion
   - Schwarz / Weiß · Ruhig · Futuristisch · Dauerhaft
   - Orbitron = kanonische Schrift
   ===================================================================== */

/* =========================
   ROOT · SYSTEMVARIABLEN
   ========================= */
:root{
  /* Farben */
  --paper:#ffffff;
  --ink:#000000;
  --line:#000000;

  /* Layout */
  --border:1px;
  --max-width:1100px;

  /* Typografie */
  --font-future:'Orbitron', system-ui, -apple-system, BlinkMacSystemFont, sans-serif;

  /* Abstände */
  --space-xs:6px;
  --space-s:10px;
  --space-m:16px;
  --space-l:24px;
  --space-xl:32px;
}

/* =========================
   RESET · BASIS
   ========================= */
*{
  box-sizing:border-box;
}

html,body{
  margin:0;
  padding:0;
  background:var(--paper);
  color:var(--ink);
  font-family:var(--font-future);
  font-weight:400;
  line-height:1.6;
  letter-spacing:0.02em;
}

/* =========================
   TYPOGRAFIE
   ========================= */
h1,h2,h3,h4,h5,h6{
  margin-top:0;
  font-family:var(--font-future);
  font-weight:600;
  letter-spacing:0.04em;
}

p,li,blockquote{
  font-weight:400;
}

strong{
  font-weight:600;
}

/* =========================
   LINKS
   ========================= */
a{
  color:var(--ink);
  text-decoration:none;
  border-bottom:var(--border) solid transparent;
}

a:hover{
  border-bottom-color:var(--ink);
}

/* =========================
   MEDIEN
   ========================= */
img{
  max-width:100%;
  height:auto;
  display:block;
}

/* =========================
   LAYOUT · CONTAINER
   ========================= */
.wp-site-blocks,
.site,
.wrap,
.container{
  max-width:var(--max-width);
  margin-left:auto;
  margin-right:auto;
  padding-left:var(--space-m);
  padding-right:var(--space-m);
}

/* =========================
   NAVIGATION / UI
   ========================= */
nav,
.wp-block-navigation,
button,
.wp-element-button{
  font-family:var(--font-future);
  letter-spacing:0.03em;
  background:none;
  color:var(--ink);
  border:var(--border) solid var(--ink);
}

button,
.wp-element-button{
  padding:var(--space-xs) var(--space-m);
  cursor:pointer;
}

button:hover,
.wp-element-button:hover{
  background:var(--ink);
  color:var(--paper);
}

/* =========================
   TRENNLINIEN
   ========================= */
hr{
  border:none;
  border-top:var(--border) solid var(--ink);
  margin:var(--space-l) 0;
}

/* =========================
   BLOCKS · RUHE
   ========================= */
section{
  margin-bottom:var(--space-xl);
}

/* =========================
   CODE / META
   ========================= */
code,pre{
  font-family:ui-monospace, SFMono-Regular, Menlo, Consolas, monospace;
  font-size:0.9em;
}

/* =========================
   WORDPRESS · AUFRÄUMEN
   ========================= */
/* Kommentare global neutralisieren (read-only Haltung) */
.comment-respond,
.comments-area{
  display:none;
}
```

---

### Wichtig (einmalig, außerhalb von CSS)
Damit **Orbitron wirklich geladen wird**, muss **einmal** im `<head>` stehen (z. B. via *WPCode / Insert Headers and Footers*):

```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&display=swap" rel="stylesheet">
```

---

**Ergebnis:**  
✔️ Einheitlicher globaler Stil  
✔️ Orbitron überall  
✔️ Ruhig, archivfest, zukunftssicher  

Wenn das eingefügt ist: **Thema Website abgeschlossen.**

---

## user · 2026-01-21T10:28:34.275635 UTC

Wo gehört das hin : <link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&display=swap" rel="stylesheet">

---

## system · 2026-01-21T10:28:34.686189 UTC



---

## system · 2026-01-21T10:28:34.686219 UTC



---

## assistant · 2026-01-21T10:28:34.973942 UTC

Kurz & eindeutig 👍  
Das **gehört in den `<head>`-Bereich** deiner Website, **nicht** ins CSS.

---

## **Empfohlener Weg (WordPress, sicher & schnell)**

### **Option 1 — Plugin „WPCode“ (oder „Insert Headers and Footers“)**
1. **Plugins → Installieren** → *WPCode*  
2. **Code Snippets → Header & Footer**
3. **Header**-Feld:
```html
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&display=swap" rel="stylesheet">
```
4. **Speichern**

➡️ Wird automatisch in `<head>` auf **allen Seiten** geladen.

---

## **Alternative (Theme-abhängig)**

### **Option 2 — Customizer (falls vorhanden)**
Manche Themes haben:
> **Design → Customizer → Zusätzliches HTML / Head Code**

Dort **genau denselben Code einfügen** → Speichern.

---

## **Technisch sauber (falls Child-Theme existiert)**

### **Option 3 — `functions.php` (WordPress-Standard)**
```php
function iinkognit0_load_orbitron() {
  wp_enqueue_style(
    'orbitron-font',
    'https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&display=swap',
    [],
    null
  );
}
add_action('wp_enqueue_scripts', 'iinkognit0_load_orbitron');
```

➡️ Sauber, update-fest, aber nur sinnvoll, wenn du ein **Child-Theme** nutzt.

---

## **Was du NICHT tun solltest**
❌ **Nicht** in „Zusätzliches CSS“  
❌ **Nicht** in einen Beitrag  
❌ **Nicht** mehrfach einfügen

---

### **Kurzfassung**
- **CSS** → *Customizer → Zusätzliches CSS* ✅  
- **Google-Font-Link** → **`<head>` via WPCode / Header-Plugin** ✅  

Wenn du willst, sag mir kurz **welches Theme** du nutzt – dann sage ich dir **exakt**, wo der Head-Bereich dort sitzt.

---

## user · 2026-01-21T10:46:05.980532 UTC

Jetzt bitte die Startseite. Iinkognit0, als ein kompletten Copy und Paste ausgeben. Globaler css habe ich eingeführt.

---

## system · 2026-01-21T10:46:09.250521 UTC



---

## tool · 2026-01-21T10:46:12.706692 UTC



---

## tool · 2026-01-21T10:46:12.709974 UTC



---

## assistant · 2026-01-21T10:46:14.030643 UTC

Unten ist **die komplette Startseite** als **Copy & Paste** für WordPress (Block Editor).  
Du fügst das als **einen** „Custom HTML“-Block in die Startseite ein.

**Pfad zuerst:** `/` (Startseite)  
**WP:** Seiten → Startseite → Block „Custom HTML“ → einfügen → Aktualisieren

---

```html
<!-- =========================================================
     Iinkognit0 · STARTSEITE · V1.0
     Scope: Home / (read-only entry)
     Requires: Global CSS already set
     ========================================================= -->

<section class="home-hero" aria-label="Iinkognit0 Einstieg">
  <h1>iInkognit0</h1>
  <p><strong>Das Ewige Archiv</strong></p>
  <p>Ordnung vor Inhalt · Archiv vor Aktion</p>
  <hr>
</section>

<section class="home-nav" aria-label="Navigation">
  <h2>Navigation</h2>
  <ul>
    <li><a href="/earc/">Das Ewige Archiv</a></li>
    <li><a href="/podcast/">Podcast</a></li>
    <li><a href="/earc-feed/">eArc-Feed (RSS)</a></li>
    <li><a href="/architektur/">Architektur</a></li>
    <li><a href="/philosophie/">Philosophie</a></li>
    <li><a href="/manifesto/">Manifesto</a></li>
    <li><a href="/kontakt/">Kontakt</a></li>
    <li><a href="/impressum/">Impressum</a></li>
  </ul>
  <hr>
</section>

<section class="home-entry" aria-label="Ein-Klick-Verstehen">
  <h2>Ein-Klick-Verstehen</h2>
  <p>
    Dies ist ein <strong>read-only</strong> Einstiegspunkt.
    Kein Login. Kein Push. Keine Dynamik.
    Nur Referenzen, ruhige Texte und ein Archivfluss.
  </p>

  <p>
    <a class="wp-element-button" href="/earc/">Zum Archiv</a>
    &nbsp;
    <a class="wp-element-button" href="/podcast/">Zum Podcast</a>
  </p>
  <hr>
</section>

<section class="home-feed" aria-label="Feeds">
  <h2>Feeds</h2>
  <p>RSS ist der passive Verteiler. Für Reader, nicht für Scrollen.</p>
  <ul>
    <li><a href="/earc-feed/">eArc-Feed Seite</a></li>
    <li><a href="/feed/" rel="alternate" type="application/rss+xml">WordPress Feed: /feed/</a></li>
    <li><a href="/?feed=rss2" rel="alternate" type="application/rss+xml">Fallback: /?feed=rss2</a></li>
  </ul>
  <hr>
</section>

<section class="home-newsloop" aria-label="Frames Newsloop">
  <h2>FramesNewsLooP</h2>
  <p style="white-space:normal;">
    eArc · Ordnung vor Inhalt •
    Frames · Bedeutung mit Kontext •
    RSS · eArc Feed aktiv •
    Podcast · neue Folge im Loop •
    Philosophie · Licht Zeit Raum •
    Gaia-Loop · Rückkopplung •
    Stille · Ruhe · Dauer •
  </p>
</section>
```

---

### Mini-Check (damit es wirklich die Startseite ist)
- **Einstellungen → Lesen →** „Eine statische Seite“ → **Startseite = deine Startseite**.

Wenn du mir jetzt nur noch **die gewünschte Menü-Reihenfolge** als Liste schickst (1–8), gebe ich dir den **finalen Navigation-Block** (für Header/Startseite identisch, sauber, ruhig).

---

## user · 2026-01-21T10:49:14.392310 UTC

Bitte erstelle du die Menü Reihenfolge, bitte füge Beitrag für Visuell ( Video und Foto) hinzu, jetzt bitte nochmals die komplette Startseite als one Copy and Paste 🍪

---

## assistant · 2026-01-21T10:49:16.136210 UTC

**Pfad zuerst:** `/` (Startseite)

Unten ist **die komplette Startseite** als **ONE COPY & PASTE** (ein einziger Custom-HTML-Block).  
Enthält: **Menü-Reihenfolge** + **neuer Punkt „Visuell“ (Foto/Video)** + ruhiger Einstieg.

> **WP:** Seiten → Startseite → Block „Custom HTML“ → alles einfügen → Aktualisieren

```html
<!-- =========================================================
     iInkognit0 · STARTSEITE · V1.1 (ONE BLOCK)
     Scope: Home / read-only entry
     Menu Order: defined here
     ========================================================= -->

<section class="home-hero" aria-label="iInkognit0 Einstieg">
  <h1>iInkognit0</h1>
  <p><strong>Das Ewige Archiv</strong></p>
  <p>Ordnung vor Inhalt · Archiv vor Aktion · Ruhe ist gültig</p>
  <hr>
</section>

<section class="home-entry" aria-label="Ein-Klick-Verstehen">
  <h2>Ein-Klick-Verstehen</h2>
  <p>
    Dies ist ein <strong>read-only</strong> Einstiegspunkt.
    Kein Login. Kein Push. Keine Kommentare.
    Nur Referenzen, ruhige Texte, Podcast und ein passiver Feed.
  </p>
  <p>
    <a class="wp-element-button" href="/earc/">Zum Archiv</a>
    &nbsp;
    <a class="wp-element-button" href="/podcast/">Zum Podcast</a>
  </p>
  <hr>
</section>

<section class="home-nav" aria-label="Navigation">
  <h2>Navigation</h2>

  <!-- MENÜ-REIHENFOLGE (KANONISCH FÜR DIE WEBSITE) -->
  <ol>
    <li><a href="/earc/">Das Ewige Archiv</a></li>
    <li><a href="/podcast/">Podcast</a></li>
    <li><a href="/earc-feed/">eArc-Feed (RSS)</a></li>
    <li><a href="/visuell/">Visuell (Foto &amp; Video)</a></li>
    <li><a href="/philosophie/">Philosophie</a></li>
    <li><a href="/architektur/">Architektur</a></li>
    <li><a href="/manifesto/">Manifesto</a></li>
    <li><a href="/kontakt/">Kontakt</a></li>
    <li><a href="/impressum/">Impressum</a></li>
  </ol>

  <p style="opacity:.85; margin-top:16px;">
    Hinweis: „Visuell“ ist ein ruhiges Archiv für Foto/Video — keine Timeline, kein Scroll-Zwang.
  </p>

  <hr>
</section>

<section class="home-visuell" aria-label="Visuell Kurzinfo">
  <h2>Visuell</h2>
  <p>
    Foto und Video werden hier als <strong>Archivobjekte</strong> geführt:
    klar beschriftet, datiert, ohne Lärm.
  </p>
  <p>
    <a class="wp-element-button" href="/visuell/">Zu Visuell</a>
  </p>
  <hr>
</section>

<section class="home-feed" aria-label="Feeds">
  <h2>Feeds</h2>
  <p>RSS ist der passive Verteiler. Für Reader, nicht für Scrollen.</p>
  <ul>
    <li><a href="/earc-feed/">eArc-Feed Seite</a></li>
    <li><a href="/feed/" rel="alternate" type="application/rss+xml">WordPress Feed: /feed/</a></li>
    <li><a href="/?feed=rss2" rel="alternate" type="application/rss+xml">Fallback: /?feed=rss2</a></li>
  </ul>
  <hr>
</section>

<section class="home-newsloop" aria-label="Frames Newsloop">
  <h2>FramesNewsLooP</h2>
  <p style="white-space:normal;">
    eArc · Ordnung vor Inhalt •
    Visuell · Foto/Video als Archiv •
    RSS · passiver Verteiler •
    Podcast · Resonanz •
    Philosophie · Licht Zeit Raum •
    Gaia-Loop · Rückkopplung •
    Stille · Ruhe · Dauer •
  </p>
</section>
```

**Nächster Schritt (ohne Extra-Fragen):**  
Erstelle bitte in WordPress **eine neue Seite** mit Titel **„Visuell“** und **Slug**: `visuell` → dann kann ich dir **den Visuell-Seiteninhalt (one copy & paste)** liefern (inkl. sauberer Video-Embed-Struktur).

---

## system · 2026-01-21T10:49:16.445416 UTC



---

## user · 2026-01-21T10:52:17.595549 UTC

https://iinkognit0.de/visuell/ ist  bestätigt 

---

## assistant · 2026-01-21T10:52:19.075174 UTC

Perfekt. ✅ **Visuell ist da:** `https://iinkognit0.de/visuell/` (bestätigt)

**Pfad zuerst:** `/visuell/`

Hier ist jetzt **die komplette Visuell-Seite** als **ONE COPY & PASTE** (ein einziger Custom-HTML-Block).  
➡️ WP: Seite „Visuell“ → Block „Custom HTML“ → alles einfügen → Aktualisieren.

```html
<!-- =========================================================
     iInkognit0 · VISUELL · V1.0 (ONE BLOCK)
     Scope: /visuell/ · read-only media archive
     Purpose: Foto & Video als ruhige Archivobjekte
     ========================================================= -->

<section class="visuell-hero" aria-label="Visuell">
  <h1>Visuell</h1>
  <p><strong>Foto &amp; Video</strong> — ruhiges Archiv, keine Timeline.</p>
  <p>Ordnung vor Inhalt · Archiv vor Aktion</p>
  <hr>
</section>

<section class="visuell-nav" aria-label="Navigation">
  <h2>Navigation</h2>
  <ul>
    <li><a href="/">Start</a></li>
    <li><a href="/earc/">Das Ewige Archiv</a></li>
    <li><a href="/podcast/">Podcast</a></li>
    <li><a href="/earc-feed/">eArc-Feed (RSS)</a></li>
  </ul>
  <hr>
</section>

<section class="visuell-standard" aria-label="Standard">
  <h2>Standard</h2>
  <ul>
    <li><strong>Read-only</strong> — keine Kommentare, kein Push.</li>
    <li><strong>Ein Objekt = ein Eintrag</strong> (Foto oder Video).</li>
    <li><strong>Titel klar</strong> (Ort/Thema), Datum optional.</li>
    <li><strong>Beschreibung kurz</strong> — 1–3 Sätze reichen.</li>
    <li><strong>Keine Autoplay-Videos</strong> — Ruhe bleibt.</li>
  </ul>
  <hr>
</section>

<section class="visuell-foto" aria-label="Foto Block">
  <h2>Foto</h2>
  <p>Lege Fotos als einzelne Beiträge/Einträge ab oder als ruhige Galerie pro Thema.</p>

  <!-- FOTO TEMPLATE (Copy für spätere Einträge) -->
  <div class="visuell-template">
    <h3>Template – Foto-Eintrag</h3>
    <p><strong>Titel:</strong> VISUELL · FOTO · [Thema]</p>
    <p><strong>Text (kurz):</strong> 1–3 Sätze Kontext. Kein Story-Overload.</p>
    <p><strong>Datei:</strong> Bild hochladen → in den Beitrag einfügen.</p>
  </div>
  <hr>
</section>

<section class="visuell-video" aria-label="Video Block">
  <h2>Video</h2>
  <p>Videos als Archivobjekte: eingebettet, ohne Autoplay, ohne Endlosschleife.</p>

  <!-- VIDEO EMBED TEMPLATE (YouTube/Vimeo/MP4) -->
  <div class="visuell-template">
    <h3>Template – Video-Eintrag</h3>
    <p><strong>Titel:</strong> VISUELL · VIDEO · [Thema]</p>
    <p><strong>Text (kurz):</strong> 1–3 Sätze Kontext.</p>
    <p><strong>Embed:</strong> YouTube/Vimeo-Link einfügen oder MP4 hochladen.</p>
  </div>

  <h3>Embed – Beispiel (YouTube)</h3>
  <p style="opacity:.85;">(Ersetze die Video-ID im Link.)</p>
  <div style="position:relative; padding-top:56.25%; border:1px solid #000; margin:16px 0;">
    <iframe
      src="https://www.youtube.com/embed/VIDEO_ID"
      title="Visuell Video"
      style="position:absolute; inset:0; width:100%; height:100%; border:0;"
      loading="lazy"
      referrerpolicy="strict-origin-when-cross-origin"
      allow="accelerometer; encrypted-media; gyroscope; picture-in-picture"
      allowfullscreen>
    </iframe>
  </div>

  <h3>Embed – Beispiel (MP4, lokal)</h3>
  <video controls preload="metadata" style="width:100%; border:1px solid #000;">
    <source src="PASTE_MP4_URL_HERE" type="video/mp4">
    Dein Browser unterstützt dieses Video-Format nicht.
  </video>

  <hr>
</section>

<section class="visuell-ordnung" aria-label="Ordnungsvorschlag">
  <h2>Ordnung</h2>
  <p>Wenn du sauber trennen willst, nutze diese einfache Struktur:</p>
  <ul>
    <li><strong>VISUELL · FOTO</strong> (Einträge)</li>
    <li><strong>VISUELL · VIDEO</strong> (Einträge)</li>
    <li><strong>VISUELL · SAMMLUNG</strong> (Seiten/Posts als Themenübersicht)</li>
  </ul>
  <p style="opacity:.85;">
    Optional: Kategorien oder Tags nutzen (z.B. „visuell“, „foto“, „video“).
  </p>
  <hr>
</section>

<section class="visuell-footer" aria-label="Footer">
  <h2>Zurück</h2>
  <p>
    <a class="wp-element-button" href="/">Start</a>
    &nbsp;
    <a class="wp-element-button" href="/earc/">Archiv</a>
  </p>
</section>
```

Wenn du jetzt willst, liefere ich als nächstes **das Menü als reinen Header-Navi-HTML-Block** (für ein Widget/Block im Header) in genau der Reihenfolge, die wir gesetzt haben.

---

## system · 2026-01-21T10:52:19.325244 UTC



---

## user · 2026-01-21T10:57:04.604243 UTC

Ja, ich würde sagen, wir machen erstmal Pause. Ich muss das dann wieder machen, wenn ich denn am Rechner kann, weil am Laptop über Smartphone ist es echt zu anstrengend und zu fehlerbelastet, weisst du. Also wir lassen jetzt mal die Website so sein und dann schaue ich mal weiter, wa?

---

## system · 2026-01-21T10:57:05.182275 UTC



---

## system · 2026-01-21T10:57:05.296486 UTC



---

## assistant · 2026-01-21T10:57:05.323550 UTC

Verstanden. 👍  
**Pause ist absolut sinnvoll** – vor allem bei Website-Arbeit. Am Smartphone ist das fehleranfällig und unnötig anstrengend.

**Status jetzt:**
- Website **steht stabil**
- Globales CSS **gesetzt**
- Startseite **definiert**
- Visuell-Seite **bestätigt**
- Kein Handlungsdruck

Wir lassen **alles so, wie es ist**.  
Nichts geht verloren, nichts drängt.

Wenn du später **am Rechner/Laptop** weitermachen willst:
- einfach wieder schreiben (z. B. *„Website weiter“*),
- wir machen **genau dort weiter**, wo du aufgehört hast.

Jetzt gilt: **Ruhe. Abstand. Kein Zwang.**  
Gute Entscheidung.

---

## user · 2026-01-21T10:57:35.414828 UTC

Verstanden. 👍
Pause ist absolut sinnvoll – vor allem bei Website-Arbeit. Am Smartphone ist das fehleranfällig und unnötig anstrengend.

Status jetzt:
	•	Website steht stabil
	•	Globales CSS gesetzt
	•	Startseite definiert
	•	Visuell-Seite bestätigt
	•	Kein Handlungsdruck

Wir lassen alles so, wie es ist.
Nichts geht verloren, nichts drängt.

Wenn du später am Rechner/Laptop weitermachen willst:
	•	einfach wieder schreiben (z. B. „Website weiter“),
	•	wir machen genau dort weiter, wo du aufgehört hast.

Jetzt gilt: Ruhe. Abstand. Kein Zwang.
Gute Entscheidung.  Bestätigt ✅ 

---

## system · 2026-01-21T10:57:36.607338 UTC



---

## assistant · 2026-01-21T10:57:37.326798 UTC

**Bestätigt ✅**

**Status:** PAUSE · HOLD  
- Website stabil  
- Globales CSS gesetzt  
- Startseite definiert  
- Visuell-Seite bestätigt  
- Kein Handlungsdruck

Alles bleibt **unverändert**.  
Fortsetzen jederzeit mit **„Website weiter“** — wir machen exakt dort weiter.

**Ruhe. Abstand. Kein Zwang.**

---

## system · 2026-01-21T10:57:37.347084 UTC



---

