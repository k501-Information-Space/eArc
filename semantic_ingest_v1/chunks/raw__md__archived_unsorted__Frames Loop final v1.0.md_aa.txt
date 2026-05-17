<!-- =================================================================================================
     eArc · BLOCK · FramesNewsLooP · V1.0 · FINAL
     id: eArc-000-BOOT-0002
     Zweck: Cyberpunk-Style News-Ticker (Schwarz/Weiß), modulbasiert, SEO-/A11y-sauber
     Hinweis: CSS kommt aus dem Modul-CSS (FramesNewsLooP_Module.css) oder globalem CSS-Fundament.
================================================================================================== -->

<!-- ===================================== [ START: FramesNewsLooP BLOCK ] ===================================== -->

<section class="earc-frame newsloop" aria-label="FramesNewsLooP">
  <div class="newsloop__label" aria-label="FramesNewsLooP Label">FramesNewsLooP</div>

  <div class="ticker" aria-label="FramesNewsLooP Ticker">
    <div class="ticker__track" role="marquee" aria-live="off">
      <!-- STRIP A -->
      <div class="ticker__strip" aria-label="FramesNewsLooP Items">
        <span class="ticker__item">eArc · Ordnung vor Inhalt •</span>
        <span class="ticker__item">Frames · Bedeutung mit Kontext •</span>
        <span class="ticker__item">RSS · eArc Feed aktiv •</span>
        <span class="ticker__item">Podcast · neue Folge im Loop •</span>
        <span class="ticker__item">Philosophie · Licht Zeit Raum •</span>
        <span class="ticker__item">Gaia-Loop · Rückkopplung •</span>
        <span class="ticker__item">Stille · Ruhe · Dauer •</span>
      </div>

      <!-- STRIP B (Duplikat für Endlos-Loop) -->
      <div class="ticker__strip" aria-hidden="true">
        <span class="ticker__item">eArc · Ordnung vor Inhalt •</span>
        <span class="ticker__item">Frames · Bedeutung mit Kontext •</span>
        <span class="ticker__item">RSS · eArc Feed aktiv •</span>
        <span class="ticker__item">Podcast · neue Folge im Loop •</span>
        <span class="ticker__item">Philosophie · Licht Zeit Raum •</span>
        <span class="ticker__item">Gaia-Loop · Rückkopplung •</span>
        <span class="ticker__item">Stille · Ruhe · Dauer •</span>
      </div>
    </div>
  </div>
</section>

<!-- ====================================== [ END: FramesNewsLooP BLOCK ] ====================================== -->

<!-- =================================================================================================
     OPTIONAL (nur falls du KEIN Modul-CSS lädst):
     -> Dann den CSS-Block aus FramesNewsLooP_Module.css hier INLINE einfügen (nicht empfohlen),
        weil "Globales CSS = Fundament" bleiben soll.
================================================================================================== -->