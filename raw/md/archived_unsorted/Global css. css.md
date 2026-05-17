  
/* =====================================================================

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

  

/* =========================

   TYPOGRAFIE

   ========================= */

h1,h2,h3,h4{

  font-family:var(--font-future);

  letter-spacing:.08em;

  margin:0 0 var(--space-s) 0;

}

  

p{

  margin:0 0 var(--space-s) 0;

  letter-spacing:.02em;

}

  

/* =========================

   LINKS

   ========================= */

a{

  color:var(--ink);

  text-decoration:none;

}

  

a:hover{

  opacity:.75;

}

  

/* =========================

   FRAME · GRUNDSTRUKTUR

   ========================= */

.earc-frame{

  border:var(--border) solid var(--line);

  padding:var(--space-m);

  margin-bottom:var(--space-m);

}

  

/* =========================

   FRAMES NEWS LOOP · TICKER

   ========================= */

.newsloop{

  display:flex;

  align-items:center;

  gap:var(--space-m);

}

  

.newsloop__label{

  font-family:var(--font-future);

  font-weight:600;

  letter-spacing:.1em;

  border:var(--border) solid var(--line);

  padding:var(--space-xs) var(--space-s);

  white-space:nowrap;

}

  

/* TICKER CONTAINER */

.ticker{

  position:relative;

  overflow:hidden;

  flex:1;

  border-left:var(--border) solid var(--line);

  padding-left:var(--space-m);

}

  

/* BEWEGTE SPUR */

.ticker__track{

  display:flex;

  width:max-content;

  animation:tickerMove 30s linear infinite;

  will-change:transform;

}

  

/* EIN STREIFEN */

.ticker__strip{

  display:flex;

  align-items:center;

  gap:var(--space-m);

  padding-right:var(--space-m);

}

  

/* EIN ITEM */

.ticker__item{

  font-family:var(--font-future);

  font-size:14px;

  letter-spacing:.08em;

  white-space:nowrap;

  opacity:.85;

}

  

/* =========================

   ANIMATION

   ========================= */

@keyframes tickerMove{

  from{

    transform:translateX(0);

  }

  to{

    transform:translateX(-50%);

  }

}

  

/* =========================

   ACCESSIBILITY

   ========================= */

@media (prefers-reduced-motion: reduce){

  .ticker__track{

    animation:none !important;

  }

}

  

/* =========================

   RESPONSIVE

   ========================= */

@media (max-width:600px){

  .newsloop{

    flex-direction:column;

    align-items:flex-start;

  }

  

  .ticker{

    width:100%;

    padding-left:0;

    border-left:none;

    border-top:var(--border) solid var(--line);

    padding-top:var(--space-s);

  }

}

  

/* =====================================================================

   END · eArc GLOBAL CSS · V1.0

   ===================================================================== */