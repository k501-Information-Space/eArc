# 20_FRAMES Archiv Index

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## system · 2026-01-21T07:52:16.497185 UTC



---

## user · 2026-01-21T07:52:22.597379 UTC

20_FRAMES – Archiv & Index

---

## assistant · 2026-01-21T07:52:23.266016 UTC

## **20_FRAMES – Archiv & Index**

image_group{"query":["digital archive index diagram","append-only log database diagram","knowledge graph index structure","timeline index data visualization"]}

### **Zweck**
`20_FRAMES` ist die **Archiv- und Index-Schicht** des Systems.  
Sie trennt **Speicherung (Archiv)** strikt von **Auffindbarkeit (Index)** – ruhig, nachvollziehbar, dauerhaft.

---

### **1) Archiv (Write-Once, Append-Only)**
- **Unveränderlich:** Jeder Frame wird einmal geschrieben, nie überschrieben.
- **Zeitlich verankert:** UTC / Epoch als Referenz (kein impliziter Zeitdrift).
- **Inhaltlich roh:** Text, Meta, Hash – keine Interpretation.
- **Quelle der Wahrheit:** Das Archiv ist *die* kanonische Referenz.

**Eigenschaften**
- `append_only = true`
- `read_only_public = optional`
- `delete = never`
- `rewrite = forbidden`

---

### **2) Index (Verortung, nicht Bewertung)**
- **Abgeleitet:** Der Index entsteht *aus* dem Archiv, nicht umgekehrt.
- **Mehrfach möglich:** Ein Frame kann in mehreren Indizes erscheinen.
- **Ohne Bedeutung:** Der Index ordnet, erklärt nicht.

**Typische Indizes**
- Zeit-Index (Epoch / Session)
- Themen-Index (Thematik / Domäne)
- Typ-Index (DECLARATION, LOG, ANALYSIS, …)
- Referenz-Index (Verknüpfungen zwischen Frames)

---

### **3) Trennlinie (kritisch)**
> **Archiv speichert. Index zeigt.**  
> **Der Index darf das Archiv niemals verändern.**

Diese Trennung verhindert:
- Narrativ-Drift  
- stille Umschreibungen  
- implizite Bewertungen  

---

### **4) Minimaler Frame-Lebenszyklus**
1. **Frame entsteht** → wird ins Archiv geschrieben  
2. **Hash & Meta fixiert** → kanonisch  
3. **Index liest Archiv** → erzeugt Verweise  
4. **Darstellung** → rein lesend

---

### **5) Systemprinzipien**
- *Archive before action*
- *Index is not truth*
- *Silence is a valid state*
- *Stability > Velocity*

---

### **Kurzfassung**
`20_FRAMES – Archiv & Index` ist die **ruhige Infrastruktur**:  
Das Archiv hält die Realität fest.  
Der Index macht sie auffindbar – ohne sie zu verändern.

---

## assistant · 2026-01-21T07:52:23.596340 UTC



---

