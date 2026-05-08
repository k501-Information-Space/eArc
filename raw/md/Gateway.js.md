// /earc/js/gateway.js
// K501-GW-ALPHA-1 · minimal client · offline-friendly · no feature expansion

(function () {
  "use strict";

  // IMPORTANT: /earc/index.html uses root-based paths now.
  // Therefore API endpoints are root-based too:
  const API_COUNTER = "/api/counter.php";
  const API_EMIT = "/api/emit.php";

  function nowIso() {
    return new Date().toISOString();
  }

  function randId() {
    // Non-cryptographic is fine for telemetry IDs (no security meaning).
    return "F-" + Date.now().toString(36) + "-" + Math.random().toString(36).slice(2, 10);
  }

  function setBadge(state) {
    const el = document.getElementById("statusBadge");
    if (!el) return;

    el.classList.remove("ok", "err", "busy");
    if (state === "ok") {
      el.classList.add("ok");
      el.textContent = "OK";
      return;
    }
    if (state === "err") {
      el.classList.add("err");
      el.textContent = "ERR";
      return;
    }
    el.classList.add("busy");
    el.textContent = "INIT";
  }

  function safeText(id, v) {
    const el = document.getElementById(id);
    if (!el) return;
    el.textContent = (v === null || v === undefined || v === "") ? "—" : String(v);
  }

  async function emit(type, payload) {
    try {
      const body = {
        id: randId(),
        t: nowIso(),
        type,
        path: location.pathname,
        payload: payload || {}
      };

      await fetch(API_EMIT, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(body),
        credentials: "omit",
        cache: "no-store",
        keepalive: true
      });
    } catch (_) {
      // offline-friendly: ignore
    }
  }

  function escapeHtml(s) {
    return String(s)
      .replaceAll("&", "&amp;")
      .replaceAll("<", "&lt;")
      .replaceAll(">", "&gt;")
      .replaceAll('"', "&quot;")
      .replaceAll("'", "&#39;");
  }

  function renderFrames(list) {
    const feed = document.getElementById("framesFeed");
    if (!feed) return;

    feed.innerHTML = "";
    if (!Array.isArray(list) || list.length === 0) {
      const d = document.createElement("div");
      d.className = "frame dim";
      d.textContent = "—";
      feed.appendChild(d);
      return;
    }

    for (const f of list) {
      const row = document.createElement("div");
      row.className = "frame";

      const type = (f && f.type) ? String(f.type) : "—";
      const t = (f && f.t) ? String(f.t) : "—";
      const path = (f && f.path) ? String(f.path) : "—";

      row.innerHTML =
        '<span class="k">type</span>: <span class="v">' + escapeHtml(type) + '</span>' +
        ' · <span class="k">t</span>: <span class="v">' + escapeHtml(t) + '</span>' +
        ' · <span class="k">path</span>: <span class="v">' + escapeHtml(path) + '</span>';

      feed.appendChild(row);
    }
  }

  async function refresh() {
    try {
      const url = API_COUNTER + "?t=" + Date.now();
      const res = await fetch(url, { cache: "no-store", credentials: "omit" });
      if (!res.ok) throw new Error("counter_http_" + res.status);

      const data = await res.json();

      const counts = data && data.counts ? data.counts : {};
      safeText("visitsVal", counts.visits);
      safeText("viewsVal", counts.views);
      safeText("clicksVal", counts.clicks);

      safeText("pathVal", location.pathname);

      const last = data && data.last ? data.last : null;
      if (last && typeof last === "object") {
        const lastStr = (last.type || "—") + " · " + (last.t || "—") + " · " + (last.path || "—");
        safeText("lastVal", lastStr);
      } else {
        safeText("lastVal", "—");
      }

      renderFrames(data && data.lastFrames ? data.lastFrames : []);
      setBadge("ok");
    } catch (_) {
      setBadge("err");
      // Keep UI stable even when offline / API unavailable
    }
  }

  function wireClickTracking() {
    document.addEventListener("click", function (ev) {
      const a = ev.target && ev.target.closest ? ev.target.closest("a") : null;
      if (!a) return;

      // Only track intentional links (data-track) to keep surface minimal and predictable.
      const label = a.getAttribute("data-track");
      if (!label) return;

      const href = a.getAttribute("href") || "";
      emit("FRAME_CLICK", { label, href });
    }, { passive: true });
  }

  function emitVisitOnce() {
    const key = "k501_visit_" + location.pathname;
    if (sessionStorage.getItem(key) === "1") return;
    sessionStorage.setItem(key, "1");
    emit("FRAME_VISIT", {});
  }

  function emitViewOnce() {
    emit("FRAME_VIEW", {});
  }

  document.addEventListener("DOMContentLoaded", function () {
    setBadge("busy");
    wireClickTracking();
    emitVisitOnce();
    emitViewOnce();
    refresh();
    setInterval(refresh, 15000);
  });
})();
