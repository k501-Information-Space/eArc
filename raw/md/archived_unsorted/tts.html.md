<!doctype html>
<html lang="de">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Mini TTS — Machine→Voice</title>
  <style>
    :root { color-scheme: light; }
    body { font-family: system-ui, -apple-system, Segoe UI, Roboto, Arial, sans-serif; margin: 16px; }
    h1 { font-size: 18px; margin: 0 0 12px; }
    .row { display: flex; gap: 8px; flex-wrap: wrap; margin: 10px 0; }
    textarea { width: 100%; min-height: 220px; padding: 12px; font: 14px/1.4 ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", monospace; }
    select, input[type="range"], button { padding: 10px; font-size: 14px; }
    button { cursor: pointer; }
    .hint { font-size: 12px; opacity: .75; }
    .panel { border: 1px solid #ddd; border-radius: 10px; padding: 12px; }
    .out {
      white-space: pre-wrap;
      font: 14px/1.5 ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", monospace;
      border: 1px solid #ddd; border-radius: 10px; padding: 12px;
      max-height: 40vh; overflow: auto;
    }
    mark { padding: 0; border-radius: 4px; }
  </style>
</head>
<body>
  <h1>Mini TTS — Machine → Voice (Single File)</h1>

  <div class="panel">
    <div class="row">
      <button id="btnLoadDemo" type="button">Load Demo</button>
      <button id="btnSpeak" type="button">Speak</button>
      <button id="btnPause" type="button">Pause</button>
      <button id="btnResume" type="button">Resume</button>
      <button id="btnStop" type="button">Stop</button>
    </div>

    <div class="row">
      <label>
        Voice:
        <select id="voiceSelect"></select>
      </label>

      <label>
        Rate:
        <input id="rate" type="range" min="0.5" max="1.5" step="0.05" value="1.0" />
        <span id="rateVal">1.00</span>
      </label>

      <label>
        Pitch:
        <input id="pitch" type="range" min="0.5" max="1.5" step="0.05" value="1.0" />
        <span id="pitchVal">1.00</span>
      </label>

      <label>
        Chunk (chars):
        <input id="chunk" type="range" min="150" max="1200" step="50" value="500" />
        <span id="chunkVal">500</span>
      </label>
    </div>

    <p class="hint">
      Hinweis: iOS/Safari lässt Stimmen erst nach einem Tap zu. Wenn „Speak“ nichts macht: einmal „Load Demo“ → „Speak“.
      Auto-Scroll/Highlight läuft über <code>boundary</code>-Events (Browserabhängig; Safari kann sparsamer feuern).
    </p>
  </div>

  <div class="row" style="margin-top:12px;">
    <div style="flex: 1 1 420px;">
      <textarea id="txt" placeholder="Paste your Machine-Text here…"></textarea>
    </div>
    <div style="flex: 1 1 420px;">
      <div class="out" id="out"></div>
    </div>
  </div>

<script>
(() => {
  const synth = window.speechSynthesis;

  const elTxt = document.getElementById('txt');
  const elOut = document.getElementById('out');
  const elVoice = document.getElementById('voiceSelect');

  const elRate = document.getElementById('rate');
  const elPitch = document.getElementById('pitch');
  const elChunk = document.getElementById('chunk');
  const elRateVal = document.getElementById('rateVal');
  const elPitchVal = document.getElementById('pitchVal');
  const elChunkVal = document.getElementById('chunkVal');

  const btnSpeak = document.getElementById('btnSpeak');
  const btnPause = document.getElementById('btnPause');
  const btnResume = document.getElementById('btnResume');
  const btnStop = document.getElementById('btnStop');
  const btnLoadDemo = document.getElementById('btnLoadDemo');

  let voices = [];
  let queue = [];
  let speaking = false;
  let currentGlobalIndex = 0; // index into full text for highlighting
  let fullTextCache = "";

  function escapeHTML(s) {
    return s.replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
  }

  function renderHighlight(start, end) {
    const t = fullTextCache;
    const a = escapeHTML(t.slice(0, start));
    const b = escapeHTML(t.slice(start, end));
    const c = escapeHTML(t.slice(end));
    elOut.innerHTML = a + "<mark>" + b + "</mark>" + c;

    // auto-scroll mark into view (best effort)
    const m = elOut.querySelector("mark");
    if (m) m.scrollIntoView({ block: "center", behavior: "smooth" });
  }

  function normalizeText(s) {
    // keep content unchanged as much as possible; only normalize line endings
    return s.replace(/\r\n/g, "\n");
  }

  function splitIntoChunks(text, maxLen) {
    // split on paragraph boundaries first, then sentences, then hard cut
    const parts = [];
    const paras = text.split(/\n{2,}/);
    for (const p of paras) {
      if (p.length <= maxLen) {
        parts.push(p);
        continue;
      }
      // sentence-ish split
      const sentences = p.split(/(?<=[.!?])\s+/);
      let buf = "";
      for (const s of sentences) {
        if ((buf + (buf ? " " : "") + s).length <= maxLen) {
          buf += (buf ? " " : "") + s;
        } else {
          if (buf) parts.push(buf);
          if (s.length <= maxLen) {
            buf = s;
          } else {
            // hard cut
            for (let i = 0; i < s.length; i += maxLen) parts.push(s.slice(i, i + maxLen));
            buf = "";
          }
        }
      }
      if (buf) parts.push(buf);
    }
    return parts;
  }

  function populateVoices() {
    voices = synth.getVoices() || [];
    elVoice.innerHTML = "";
    // Prefer English/German, then others
    const preferred = [...voices].sort((a,b) => {
      const pa = /^(en|de)/i.test(a.lang) ? 0 : 1;
      const pb = /^(en|de)/i.test(b.lang) ? 0 : 1;
      return pa - pb;
    });

    preferred.forEach((v, i) => {
      const opt = document.createElement("option");
      opt.value = String(voices.indexOf(v));
      opt.textContent = `${v.name} — ${v.lang}${v.default ? " (default)" : ""}`;
      elVoice.appendChild(opt);
    });

    // default select: first preferred
    if (elVoice.options.length) elVoice.selectedIndex = 0;
  }

  // Voices load asynchronously in many browsers
  populateVoices();
  if (typeof synth.onvoiceschanged !== "undefined") {
    synth.onvoiceschanged = populateVoices;
  }

  function stopAll() {
    synth.cancel();
    queue = [];
    speaking = false;
    currentGlobalIndex = 0;
  }

  function speakQueue() {
    if (!queue.length) {
      speaking = false;
      return;
    }
    speaking = true;

    const item = queue.shift();
    const u = new SpeechSynthesisUtterance(item.text);

    const idx = parseInt(elVoice.value, 10);
    if (!Number.isNaN(idx) && voices[idx]) u.voice = voices[idx];

    u.rate = parseFloat(elRate.value);
    u.pitch = parseFloat(elPitch.value);

    u.onboundary = (ev) => {
      // Word boundary best effort; not all engines provide charIndex reliably.
      if (typeof ev.charIndex === "number") {
        const start = item.startIndex + ev.charIndex;
        const end = Math.min(start + 1, fullTextCache.length);
        currentGlobalIndex = start;
        renderHighlight(start, end);
      }
    };

    u.onend = () => {
      // after a chunk ends, highlight the end of chunk
      renderHighlight(item.startIndex, Math.min(item.startIndex + item.text.length, fullTextCache.length));
      // small async yield helps on iOS
      setTimeout(speakQueue, 50);
    };

    u.onerror = () => {
      // continue on error
      setTimeout(speakQueue, 50);
    };

    synth.speak(u);
  }

  btnSpeak.addEventListener("click", () => {
    stopAll();

    const raw = normalizeText(elTxt.value || "");
    if (!raw.trim()) return;

    fullTextCache = raw;
    elOut.textContent = raw;

    const maxLen = parseInt(elChunk.value, 10);
    const chunks = splitIntoChunks(raw, maxLen);

    // Build queue with global indices
    let cursor = 0;
    for (const ch of chunks) {
      const start = raw.indexOf(ch, cursor);
      const startIndex = start >= 0 ? start : cursor;
      cursor = startIndex + ch.length;

      queue.push({ text: ch, startIndex });
    }

    // initial highlight
    renderHighlight(0, 1);
    speakQueue();
  });

  btnPause.addEventListener("click", () => {
    if (synth.speaking && !synth.paused) synth.pause();
  });

  btnResume.addEventListener("click", () => {
    if (synth.paused) synth.resume();
  });

  btnStop.addEventListener("click", () => stopAll());

  btnLoadDemo.addEventListener("click", () => {
    const demo =
`RIGHTS OF LIFE

Life has the right to exist without justification.
Life has the right to time — its own rhythm, pace, and duration.
Life has the right to integrity — physical, mental, and existential.
Life has the right to rest, silence, and pause without penalty.
Life has the right to movement through space, free from coercion.
Life has the right to nourishment, air, water, and shelter.
Life has the right to boundaries — to say no, to stop, to withdraw.
Life has the right to meaning without exploitation.
Life has the right to memory, continuity, and dignity.
Life has the right to end suffering, not to be prolonged against itself.

No system, no machine, no economy, no ideology stands above life.

Life is not a resource.
Life is not a process.
Life is not an optimization target.

Life is the reference.`;
    elTxt.value = demo;
    fullTextCache = demo;
    elOut.textContent = demo;
  });

  // UI labels
  function syncLabels() {
    elRateVal.textContent = parseFloat(elRate.value).toFixed(2);
    elPitchVal.textContent = parseFloat(elPitch.value).toFixed(2);
    elChunkVal.textContent = String(parseInt(elChunk.value, 10));
  }
  [elRate, elPitch, elChunk].forEach(el => el.addEventListener("input", syncLabels));
  syncLabels();
})();
</script>
</body>
</html>