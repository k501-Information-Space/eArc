<!-- /module/superflow_hd/supervisuals/HUD_SUPERFLOW_HD_v0_1.svg -->
<svg xmlns="http://www.w3.org/2000/svg" width="1200" height="180" viewBox="0 0 1200 180">
  <rect x="0" y="0" width="1200" height="180" fill="black" opacity="1"/>

  <!-- soft grid -->
  <g opacity="0.18">
    <path d="M0 30H1200 M0 60H1200 M0 90H1200 M0 120H1200 M0 150H1200" stroke="white" stroke-width="1"/>
    <path d="M100 0V180 M200 0V180 M300 0V180 M400 0V180 M500 0V180 M600 0V180 M700 0V180 M800 0V180 M900 0V180 M1000 0V180 M1100 0V180" stroke="white" stroke-width="1"/>
  </g>

  <!-- header -->
  <text x="24" y="40" font-family="ui-monospace, Menlo, Consolas, monospace" font-size="26" fill="white">
    SUPERFLOW HD · SUPERHUD / SUPERVISUALS / SUPERACOUSTICS
  </text>

  <!-- status chips -->
  <g font-family="ui-monospace, Menlo, Consolas, monospace" font-size="22" fill="white">
    <text x="24"  y="82">MODE: DEV</text>
    <text x="220" y="82">COMM: OFF</text>
    <text x="420" y="82">EXEC: BLOCKED</text>
    <text x="680" y="82">FREEZE: ON</text>
    <text x="900" y="82">STAGE: RUN</text>
  </g>

  <!-- metrics bar -->
  <g font-family="ui-monospace, Menlo, Consolas, monospace" font-size="22" fill="white">
    <text x="24"  y="122">FRAMES:</text>
    <text x="160" y="122">SAVED:</text>
    <text x="320" y="122">IO(in/out/store):</text>
    <text x="640" y="122">LAT(ms):</text>
    <text x="820" y="122">THRU:</text>
    <text x="980" y="122">CONFIRMS:</text>
  </g>

  <!-- placeholders (values) -->
  <g font-family="ui-monospace, Menlo, Consolas, monospace" font-size="22" fill="white" opacity="0.9">
    <text x="110" y="122">?</text>
    <text x="240" y="122">?</text>
    <text x="520" y="122">?/?/?</text>
    <text x="740" y="122">?</text>
    <text x="900" y="122">?</text>
    <text x="1120" y="122">OK</text>
  </g>

  <!-- subtle “pilot markers” -->
  <g opacity="0.55">
    <circle cx="24" cy="150" r="6" fill="white"/>
    <circle cx="44" cy="150" r="6" fill="white" opacity="0.55"/>
    <circle cx="64" cy="150" r="6" fill="white" opacity="0.25"/>
  </g>

  <text x="24" y="174" font-family="ui-monospace, Menlo, Consolas, monospace" font-size="14" fill="white" opacity="0.7">
    Source (canonical): iinkognit0.de · As I State Iinkognit0.
  </text>
</svg>