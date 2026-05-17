<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <meta name="color-scheme" content="dark" />
  <title>K501 · eArc Gateway · Alpha-1</title>

  <!-- Core Gateway Style -->
  <link rel="stylesheet" href="/css/gateway.css?v=alpha1" />

  <!-- Optional Cyberpunk Enhancement (activated in step 6) -->
  <!-- <link rel="stylesheet" href="/css/cyberpunk.css?v=alpha1" /> -->
</head>

<body class="k501">
  <header class="header">
    <div class="brand">
      <div class="logo">K501</div>
      <div class="subtitle">
        eArc Gateway · read-only · minimal telemetry · Alpha-1
      </div>
    </div>

    <div class="right">
      <span id="statusBadge" class="badge busy">INIT</span>
    </div>
  </header>

  <main class="layout">

    <!-- STATUS PANEL -->
    <section class="panel">
      <h2>Status</h2>

      <div class="counters">
        <div class="counter">
          <div class="label">Visits</div>
          <div id="visitsVal" class="value">—</div>
        </div>
        <div class="counter">
          <div class="label">Views</div>
          <div id="viewsVal" class="value">—</div>
        </div>
        <div class="counter">
          <div class="label">Clicks</div>
          <div id="clicksVal" class="value">—</div>
        </div>
      </div>

      <div class="meta">
        <div>Path: <span id="pathVal" class="dim">—</span></div>
        <div>Last: <span id="lastVal" class="dim">—</span></div>
        <div class="dim">
          Minimal telemetry is enabled (VISIT / VIEW / CLICK).
          No IP/UA is stored by the API in Alpha-1.
        </div>
      </div>
    </section>

    <!-- LINKS PANEL -->
    <section class="panel">
      <h2>Links</h2>

      <div class="links">
        <a class="link" href="https://orcid.org/0009-0005-5125-9711" data-track="orcid">ORCID</a>
        <a class="link" href="https://github.com/Iinkognit0" data-track="github">GitHub</a>
        <a class="link" href="https://github.com/Iinkognit0/K501-Frames-Gateway" data-track="gh-k501-gateway">Gateway Repo</a>
      </div>

      <div class="hint dim">
        BootBlock source (optional): <code>/bootblocks/bootblock.ini</code>
      </div>
    </section>

    <!-- DOI PANEL -->
    <section class="panel">
      <h2>Canonical DOIs</h2>

      <div class="list">
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18632667" data-track="doi-18632667">
            Structural Gateway & Repository Navigation v1.0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18615438" data-track="doi-18615438">
            Combined Formal Statement v1.0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18615245" data-track="doi-18615245">
            Structural Integration Specification v1.0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18599148" data-track="doi-18599148">
            Die Formel v1.0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18521607" data-track="doi-18521607">
            Flow v1.0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18511614" data-track="doi-18511614">
            AZ-Epoch 0
          </a>
        </div>
        <div class="item">
          <a class="link" href="https://doi.org/10.5281/zenodo.18511613" data-track="doi-18511613">
            Concept DOI (all versions)
          </a>
        </div>
      </div>
    </section>

    <!-- FRAMES PANEL -->
    <section class="panel">
      <h2>Last 10 Frames (read-only)</h2>

      <div id="framesFeed" class="feed" aria-live="polite">
        <div class="frame dim">—</div>
      </div>

      <div class="hint dim">
        Direct access to <code>/frames/</code> is server-blocked.
      </div>
    </section>

    <!-- OPTIONAL BOOTFRAME -->
    <section class="panel">
      <h2>Optional BootFrame</h2>

      <div class="links">
        <a class="link" href="/bootframe/" data-track="bootframe">Open BootFrame</a>
        <a class="link" href="/" data-track="root">Open Root</a>
      </div>

      <div class="hint dim">
        K501 · eArc Gateway · Alpha-1 · append-only logging · read-only UI
      </div>
    </section>

  </main>

  <footer class="footer">
    <div class="dim">
      K501-GW-ALPHA-1 · FREEZE · minimal telemetry · public domain context
    </div>
  </footer>

  <script src="/js/gateway.js?v=alpha1" defer></script>
</body>
</html>