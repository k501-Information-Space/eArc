<!--

====================================================

eArc – Das Ewige Archiv

FINAL HEADER BLOCK · V1.0

Status: FINAL

Scope: Startseite (WordPress Inline Block)

Design: Schwarz / Weiß · Futuristisch · Ruhig

====================================================

-->

  

<!-- ===== FONT (FUTURISTISCH, STABIL, SYSTEMNAH) ===== -->

<link rel="preconnect" href="https://fonts.googleapis.com">

<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>

<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;600;700&family=Inter:wght@300;400;500&display=swap" rel="stylesheet">

  

<style>

/* ==================================================

   eArc HEADER · CORE STYLES

   ================================================== */

  

:root{

  --paper:#ffffff;

  --ink:#000000;

  --line:#000000;

  --border:1px;

  --max:1100px;

}

  

*{box-sizing:border-box}

  

/* ===== HEADER WRAP ===== */

.earc-header{

  width:100%;

  background:var(--paper);

  border-bottom:var(--border) solid var(--line);

}

  

/* ===== INNER CONTAINER ===== */

.earc-header__inner{

  max-width:var(--max);

  margin:0 auto;

  padding:28px 16px 22px;

  text-align:center;

}

  

/* ===== TITLE ===== */

.earc-title{

  font-family:'Orbitron', sans-serif;

  font-size:26px;

  font-weight:700;

  letter-spacing:.12em;

  text-transform:uppercase;

  margin:0 0 6px 0;

}

  

.earc-subtitle{

  font-family:'Inter', sans-serif;

  font-size:14px;

  letter-spacing:.08em;

  opacity:.85;

  margin:0 0 22px 0;

}

  

/* ===== NAVIGATION GROUPS ===== */

.earc-nav{

  display:flex;

  flex-direction:column;

  gap:14px;

  align-items:center;

}

  

/* ===== PRIMARY NAV ===== */

.earc-nav-primary{

  display:flex;

  gap:12px;

  flex-wrap:wrap;

  justify-content:center;

}

  

/* ===== SECONDARY NAV ===== */

.earc-nav-secondary{

  display:flex;

  gap:14px;

  flex-wrap:wrap;

  justify-content:center;

  font-size:13px;

}

  

/* ===== SYSTEM NAV ===== */

.earc-nav-system{

  display:flex;

  gap:14px;

  flex-wrap:wrap;

  justify-content:center;

  font-size:12px;

  opacity:.85;

}

  

/* ===== BUTTON STYLE ===== */

.earc-btn{

  font-family:'Orbitron', sans-serif;

  color:var(--ink);

  text-decoration:none;

  border:var(--border) solid var(--line);

  padding:10px 16px;

  letter-spacing:.08em;

  text-transform:uppercase;

}

  

.earc-btn:hover{opacity:.75}

  

/* ===== TEXT LINK STYLE ===== */

.earc-link{

  font-family:'Inter', sans-serif;

  color:var(--ink);

  text-decoration:none;

  border-bottom:1px solid var(--ink);

  padding-bottom:2px;

}

  

.earc-link:hover{opacity:.75}

  

/* ===== MOBILE ===== */

@media(max-width:600px){

  .earc-title{font-size:22px}

}

</style>

  

<header class="earc-header" aria-label="eArc Header Final">

  <div class="earc-header__inner">

  

    <!-- IDENTITÄT -->

    <h1 class="earc-title">eArc – Das Ewige Archiv</h1>

    <p class="earc-subtitle">Ordnung vor Inhalt · Archiv vor Aktion</p>

  

    <!-- NAVIGATION -->

    <nav class="earc-nav" aria-label="Hauptnavigation">

  

      <!-- PRIMÄR -->

      <div class="earc-nav-primary">

        <a class="earc-btn" href="https://iinkognit0.de/">Startseite</a>

        <a class="earc-btn" href="https://iinkognit0.de/earc/">Das Ewige Archiv</a>

        <a class="earc-btn" href="https://iinkognit0.de/podcast/">Podcast</a>

      </div>

  

      <!-- SEKUNDÄR -->

      <div class="earc-nav-secondary">

        <a class="earc-link" href="https://iinkognit0.de/architektur/">Architektur</a>

        <a class="earc-link" href="https://iinkognit0.de/philosophie/">Philosophie</a>

        <a class="earc-link" href="https://iinkognit0.de/manifesto/">Manifesto</a>

      </div>

  

      <!-- SYSTEM -->

      <div class="earc-nav-system">

        <a class="earc-link" href="https://iinkognit0.de/earc-feed/">eArc-Feed (RSS)</a>

        <a class="earc-link" href="https://iinkognit0.de/kontakt/">Kontakt</a>

        <a class="earc-link" href="https://iinkognit0.de/impressum/">Impressum</a>

      </div>

  

    </nav>

  

  </div>

</header>

  

<!--

END · eArc HEADER BLOCK · FINAL V1.0

====================================================

-->