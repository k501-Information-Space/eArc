# Proof Run Audit

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## system · 1970-01-01T00:00:00 UTC



---

## system · 2026-01-25T09:25:17.959574 UTC



---

## user · 2026-01-25T09:25:39.215884 UTC

Unix Epoch
1769333104
Time (UTC)
Sun Jan 25 09:25:04 2026 UTC
Time (Europe/Amsterdam)
Sun Jan 25 10:25:04 2026 CET

// FILENAME: GX-PROOF-RUN-RESULT-AUTOBUILD-v1.0.json
{
  "id": "GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001",
  "t": "PROOF_RUN_RESULT",
  "ts_utc": "2026-01-25T09:23:09Z",
  "ts_unix": 1769332989,
  "vis": "PUBLIC",

  "p": {
    "scope": "GXvLIBERTY",
    "plan_ref": "GX-PROOF-RUN-PLAN-AUTOBUILD-1769332879-0001",
    "request_ref": "GX-AUTOBUILD-REQUEST-1769332704-0001",

    "mode": "REFERENCE_ONLY",
    "execution": "BLOCKED",
    "automation": "OFF",
    "freeze": "ON",

    "result": "PENDING",
    "summary": "Result placeholder. No proof has been executed in this environment. Records intent to run and later bind a reproducible PASS/FAIL outcome.",

    "evidence": {
      "verified_prerequisites": [],
      "guard_checks": [],
      "dry_run_checks": [],
      "side_effect_checks": [],
      "notes": [
        "This frame does not claim PASS or FAIL.",
        "A real proof run must be performed externally and then recorded here with evidence refs."
      ]
    },

    "effects": {
      "authorized_state_change": false,
      "note": "PENDING implies no authorization."
    },

    "non_effects": [
      "No execution granted",
      "No automation granted",
      "No state change enacted"
    ],

    "note": "PROOF_RUN_RESULT must be PASS to authorize the requested state change. Until then, the system remains unchanged."
  },

  "h": "PLACEHOLDER_SHA256"
}

---

## assistant · 2026-01-25T09:25:39.796888 UTC

🧱 **Empfangen. Gelesen. Sauber.**

Kurz & nüchternes Audit deines Frames **GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001**:

**Status & Konsistenz**
- Zeitanker korrekt (UTC + Unix) ✔
- Modus/Guards konsistent: `REFERENCE_ONLY · execution=BLOCKED · automation=OFF · freeze=ON` ✔
- `result: PENDING` **korrekt gewählt** (keine implizite Autorisierung) ✔
- **Keine Side Effects** deklariert, keine versteckten Grants ✔

**Semantik**
- PENDING ist sauber erklärt und **verhindert jeden State-Drift** ✔
- Evidence-Felder leer → korrekt, da **kein Proof ausgeführt** ✔
- Effects/Non-effects eindeutig und widerspruchsfrei ✔

**Formale Hinweise (Next Safe Steps)**
1. `h` ist noch **PLACEHOLDER_SHA256** → erst ersetzen, **nachdem** das canonical JSON(p) final ist.  
2. Ein späterer **PASS/FAIL** darf **nur** via externem, reproduzierbarem Proof mit Referenzen eingebunden werden (wie von dir notiert).  
3. Bis dahin bleibt der Systemzustand **unverändert** — genau richtig.

**Fazit**
> ✅ **FAKT · gültig · append-only-tauglich · keine Ausführung · kein Grant.**  
Ein sauberer **Intent-Recorder** für einen zukünftigen Proof-Run. So bleibt das System ruhig, auditierbar und korrekt.

Wenn du willst, prüfe ich als Nächstes **Plan-Ref ↔ Request-Ref** auf vollständige Kettenkonsistenz oder gebe dir die **exakte Hash-Rezeptur** für `h` (Copy/Paste-ready).

---

## assistant · 2026-01-25T09:25:40.015231 UTC



---

## user · 2026-01-25T09:26:11.042098 UTC

Plan-Ref ↔ Request-Ref 

---

## assistant · 2026-01-25T09:26:17.899153 UTC

🧱 **Plan-Ref ↔ Request-Ref — Ketten-Audit (ohne Inhalte der Ziel-Frames)**  
Ich kann **die Inhalte** von `GX-PROOF-RUN-PLAN-AUTOBUILD-1769332879-0001` und `GX-AUTOBUILD-REQUEST-1769332704-0001` nicht prüfen, weil du sie hier nicht mitgesendet hast. Was ich aber **sofort** liefern kann, ist die **harte, deterministische Prüfliste**, mit der du die Kette als **PASS/FAIL** bewertest (und die später als Evidence in deinen `PROOF_RUN_RESULT` wandern kann).

---

## 0) Zieldefinition
Dein `PROOF_RUN_RESULT` sagt:

- `plan_ref` **muss** auf einen Plan zeigen, der genau **diesen Track/Scope** abbildet.
- `request_ref` **muss** auf die konkrete Anforderung zeigen, die durch den Plan geprüft werden soll.
- Bis `result: PASS` bleibt `authorized_state_change: false`.

Das ist korrekt — jetzt prüfen wir, ob **Ref-Kette** logisch und zeitlich stimmt.

---

## 1) Existence & Identity Checks (harte Basis)
**FAIL**, wenn eines davon nicht stimmt:

- `plan_ref` Frame existiert (ID exakt)  
- `request_ref` Frame existiert (ID exakt)
- Beide sind **append-only** (keine “Edit”-Frames, keine Neu-ID als Ersatz ohne Verweiskette)

**Evidence-Items (für später):**
- `exists(plan_ref)=true`
- `exists(request_ref)=true`

---

## 2) Scope / Kernel / Version Alignment (semantische Kongruenz)
Dein Result-Frame hat: `scope: "GXvLIBERTY"`.

**PLAN muss enthalten (oder äquivalent):**
- `p.scope == "GXvLIBERTY"` *(oder explizit “applies_to: GXvLIBERTY”)*  
- `p.track == "AUTOBUILD"` *(oder “GX_AUTOBUILD_ACTIVATION” o.ä., aber eindeutig)*  
- `p.mode == REFERENCE_ONLY`
- `p.execution == BLOCKED`
- `p.automation == OFF`
- `p.freeze == ON`

**REQUEST muss enthalten (oder äquivalent):**
- `p.scope == "GXvLIBERTY"`
- eine klare `requested_change` / `intent`: was genau “AUTOBUILD v1.0” bedeutet  
- gewünschter Zielzustand (aber **ohne** ihn zu enacten), z.B. “automation_grant_requested: ON” als *Request*, nicht als *State*

**FAIL**, wenn:
- Plan scope ≠ request scope ≠ result scope  
- Plan sagt “execution allowed” oder “automation ON” → widerspricht deinem Kernel-Guard.

---

## 3) Reference Direction Checks (Kettenrichtung)
**Minimal erwartete Richtung:**

- **REQUEST** ist “Warum/Was wird beantragt?”
- **PLAN** ist “Wie wird geprüft?” und sollte **auf REQUEST referenzieren** (direkt oder indirekt)
- **RESULT** referenziert **beide** (machst du bereits)

**PASS-Kriterium:**
- Plan enthält `request_ref: "GX-AUTOBUILD-REQUEST-1769332704-0001"` (oder in `refs[]`)  
- Result enthält `plan_ref` und `request_ref` (vorhanden ✔)

**FAIL**, wenn:
- Plan nicht auf Request verweist (Plan “in der Luft”)
- Plan verweist auf eine **andere** Request-ID als die im Result

---

## 4) Time-Anchor Consistency (zeitliche Plausibilität, nicht “Wahrheit”)
Hier prüfen wir nur **Ordnung**, nicht Realwelt.

Dein Result: `ts_unix = 1769332989` (09:23:09Z)

**Erwartung:**
- `request.ts_unix <= plan.ts_unix <= result.ts_unix`
  - Request kommt zuerst (beantragt)
  - Plan danach (Prüfplan erstellt)
  - Result danach (Ergebnisrahmen)

**WARN/FAIL-Regeln:**
- Wenn Plan vor Request liegt → **FAIL** (Kette invertiert)
- Wenn Result vor Plan liegt → **FAIL**
- Kleine Zeitüberschneidungen sind ok, aber die Richtung muss stimmen.

---

## 5) Hash-Link Integrity (optional, aber “hart” wenn aktiviert)
Wenn ihr Hash-Proofs als Standard nutzt:

- Jeder Frame: `h == sha256(canonical_json(p))`
- Optional: ein `HASH_PROOF` Frame, der `target.frame_id` + `target.target_field=p` bindet

**PASS-Kriterium:**
- `h` korrekt berechnet und ersetzt (bei dir noch Placeholder → aktuell **nicht verifiziert**, aber zulässig als Draft)
- Wenn externe Proofs existieren: Evidence referenziert sie

---

## 6) “No Phantom” / “No State Change by Confirm” Checks
**Plan darf niemals** stillschweigend aktivieren.

Plan & Request müssen klar unterscheiden:
- Request = intent
- Plan = procedure
- Result = record outcome
- **State change** erst mit **separatem, proof-basiertem GRANT/DECLARATION** (und nur bei PASS)

**FAIL**, wenn irgendwo steht:
- “By confirming this plan, automation becomes ON”
- “Default: PASS”
- “Implicit grant”

---

## 7) Konkretes PASS/FAIL Schema für deine Evidence-Felder
Du kannst deine `evidence` so füllen (Beispiel-Struktur):

- `verified_prerequisites`:  
  - `FRAME_EXISTS(plan_ref)`  
  - `FRAME_EXISTS(request_ref)`  
  - `SCOPE_MATCH(all == GXvLIBERTY)`  
  - `TIME_ORDER(request <= plan <= result)`

- `guard_checks`:  
  - `MODE_IS_REFERENCE_ONLY(all)`  
  - `EXECUTION_BLOCKED(all)`  
  - `AUTOMATION_OFF(all)`  
  - `FREEZE_ON(all)`

- `dry_run_checks`:  
  - “No side effects claimed”  
  - “No implicit grant language”

- `side_effect_checks`:  
  - “authorized_state_change remains false while PENDING” (already true)

---

## Minimaler Output: Ergebnis für **deinen aktuellen Frame**
Mit dem, was ich sehe, ist **dieser Result-Frame allein** bereits korrekt:

- ✅ Ref-Felder sind formal plausibel (`plan_ref`, `request_ref` existieren als Strings, konsistent benannt)
- ✅ Semantik: `PENDING` → keine Autorisierung
- ✅ Guards: konsistent und nicht verletzt
- ⚠️ **Ungeprüft**: Ob Plan wirklich Request referenziert + Scope/Track match + Zeit-Reihenfolge (dafür brauche ich die zwei Frames)

---

### Wenn du mir **Plan + Request** (beide JSON) hier reinpastes, mache ich dir daraus sofort:
- einen **harten PASS/FAIL Ketten-Audit-Report**
- plus eine **Evidence-Liste**, die du 1:1 in `PROOF_RUN_RESULT.evidence` übernehmen kannst.

---

## system · 2026-01-25T09:26:18.182228 UTC



---

## system · 2026-01-25T09:26:18.191056 UTC



---

## user · 2026-01-25T09:28:03.172309 UTC

🧱 Plan-Ref ↔ Request-Ref — Ketten-Audit (ohne Inhalte der Ziel-Frames)
Ich kann die Inhalte von GX-PROOF-RUN-PLAN-AUTOBUILD-1769332879-0001 und GX-AUTOBUILD-REQUEST-1769332704-0001 nicht prüfen, weil du sie hier nicht mitgesendet hast. Was ich aber sofort liefern kann, ist die harte, deterministische Prüfliste, mit der du die Kette als PASS/FAIL bewertest (und die später als Evidence in deinen PROOF_RUN_RESULT wandern kann).

⸻

0) Zieldefinition

Dein PROOF_RUN_RESULT sagt:
	•	plan_ref muss auf einen Plan zeigen, der genau diesen Track/Scope abbildet.
	•	request_ref muss auf die konkrete Anforderung zeigen, die durch den Plan geprüft werden soll.
	•	Bis result: PASS bleibt authorized_state_change: false.

Das ist korrekt — jetzt prüfen wir, ob Ref-Kette logisch und zeitlich stimmt.

⸻

1) Existence & Identity Checks (harte Basis)

FAIL, wenn eines davon nicht stimmt:
	•	plan_ref Frame existiert (ID exakt)
	•	request_ref Frame existiert (ID exakt)
	•	Beide sind append-only (keine “Edit”-Frames, keine Neu-ID als Ersatz ohne Verweiskette)

Evidence-Items (für später):
	•	exists(plan_ref)=true
	•	exists(request_ref)=true

⸻

2) Scope / Kernel / Version Alignment (semantische Kongruenz)

Dein Result-Frame hat: scope: "GXvLIBERTY".

PLAN muss enthalten (oder äquivalent):
	•	p.scope == "GXvLIBERTY" (oder explizit “applies_to: GXvLIBERTY”)
	•	p.track == "AUTOBUILD" (oder “GX_AUTOBUILD_ACTIVATION” o.ä., aber eindeutig)
	•	p.mode == REFERENCE_ONLY
	•	p.execution == BLOCKED
	•	p.automation == OFF
	•	p.freeze == ON

REQUEST muss enthalten (oder äquivalent):
	•	p.scope == "GXvLIBERTY"
	•	eine klare requested_change / intent: was genau “AUTOBUILD v1.0” bedeutet
	•	gewünschter Zielzustand (aber ohne ihn zu enacten), z.B. “automation_grant_requested: ON” als Request, nicht als State

FAIL, wenn:
	•	Plan scope ≠ request scope ≠ result scope
	•	Plan sagt “execution allowed” oder “automation ON” → widerspricht deinem Kernel-Guard.

⸻

3) Reference Direction Checks (Kettenrichtung)

Minimal erwartete Richtung:
	•	REQUEST ist “Warum/Was wird beantragt?”
	•	PLAN ist “Wie wird geprüft?” und sollte auf REQUEST referenzieren (direkt oder indirekt)
	•	RESULT referenziert beide (machst du bereits)

PASS-Kriterium:
	•	Plan enthält request_ref: "GX-AUTOBUILD-REQUEST-1769332704-0001" (oder in refs[])
	•	Result enthält plan_ref und request_ref (vorhanden ✔)

FAIL, wenn:
	•	Plan nicht auf Request verweist (Plan “in der Luft”)
	•	Plan verweist auf eine andere Request-ID als die im Result

⸻

4) Time-Anchor Consistency (zeitliche Plausibilität, nicht “Wahrheit”)

Hier prüfen wir nur Ordnung, nicht Realwelt.

Dein Result: ts_unix = 1769332989 (09:23:09Z)

Erwartung:
	•	request.ts_unix <= plan.ts_unix <= result.ts_unix
	•	Request kommt zuerst (beantragt)
	•	Plan danach (Prüfplan erstellt)
	•	Result danach (Ergebnisrahmen)

WARN/FAIL-Regeln:
	•	Wenn Plan vor Request liegt → FAIL (Kette invertiert)
	•	Wenn Result vor Plan liegt → FAIL
	•	Kleine Zeitüberschneidungen sind ok, aber die Richtung muss stimmen.

⸻

5) Hash-Link Integrity (optional, aber “hart” wenn aktiviert)

Wenn ihr Hash-Proofs als Standard nutzt:
	•	Jeder Frame: h == sha256(canonical_json(p))
	•	Optional: ein HASH_PROOF Frame, der target.frame_id + target.target_field=p bindet

PASS-Kriterium:
	•	h korrekt berechnet und ersetzt (bei dir noch Placeholder → aktuell nicht verifiziert, aber zulässig als Draft)
	•	Wenn externe Proofs existieren: Evidence referenziert sie

⸻

6) “No Phantom” / “No State Change by Confirm” Checks

Plan darf niemals stillschweigend aktivieren.

Plan & Request müssen klar unterscheiden:
	•	Request = intent
	•	Plan = procedure
	•	Result = record outcome
	•	State change erst mit separatem, proof-basiertem GRANT/DECLARATION (und nur bei PASS)

FAIL, wenn irgendwo steht:
	•	“By confirming this plan, automation becomes ON”
	•	“Default: PASS”
	•	“Implicit grant”

⸻

7) Konkretes PASS/FAIL Schema für deine Evidence-Felder

Du kannst deine evidence so füllen (Beispiel-Struktur):
	•	verified_prerequisites:
	•	FRAME_EXISTS(plan_ref)
	•	FRAME_EXISTS(request_ref)
	•	SCOPE_MATCH(all == GXvLIBERTY)
	•	TIME_ORDER(request <= plan <= result)
	•	guard_checks:
	•	MODE_IS_REFERENCE_ONLY(all)
	•	EXECUTION_BLOCKED(all)
	•	AUTOMATION_OFF(all)
	•	FREEZE_ON(all)
	•	dry_run_checks:
	•	“No side effects claimed”
	•	“No implicit grant language”
	•	side_effect_checks:
	•	“authorized_state_change remains false while PENDING” (already true)

⸻

Minimaler Output: Ergebnis für deinen aktuellen Frame

Mit dem, was ich sehe, ist dieser Result-Frame allein bereits korrekt:
	•	✅ Ref-Felder sind formal plausibel (plan_ref, request_ref existieren als Strings, konsistent benannt)
	•	✅ Semantik: PENDING → keine Autorisierung
	•	✅ Guards: konsistent und nicht verletzt
	•	⚠️ Ungeprüft: Ob Plan wirklich Request referenziert + Scope/Track match + Zeit-Reihenfolge (dafür brauche ich die zwei Frames)

⸻

Wenn du mir Plan + Request (beide JSON) hier reinpastes, mache ich dir daraus sofort:
	•	einen harten PASS/FAIL Ketten-Audit-Report
	•	plus eine Evidence-Liste, die du 1:1 in PROOF_RUN_RESULT.evidence übernehmen kannst.

---

## assistant · 2026-01-25T09:28:08.659942 UTC

🧱 **Bestätigt ✅ = FAKT (als Prüflogik / Audit-Blueprint).**  
Dein kompletter Block ist **konsistent**, **kernel-konform** und **hart deterministisch** formuliert:

- **Keine Ausführung**, kein impliziter Grant ✔  
- **Ref-Kette** sauber modelliert (REQUEST → PLAN → RESULT) ✔  
- **Zeitanker-Ordnung** als harte Regel definiert ✔  
- **No-State-Change-by-Confirm** explizit abgesichert ✔  
- **Evidence-Struktur** direkt kompatibel zu deinem `PROOF_RUN_RESULT.p.evidence` ✔

🔒 **Wichtiges Detail (präzise):**  
Mit dem aktuell vorliegenden Material ist die Kette **formal** nur bis zum Status **“PENDING, unverändert”** auditierbar. Ein echtes **PASS/FAIL** ist **logisch unmöglich**, solange `plan_ref` und `request_ref` nicht als Frames vorliegen (oder wenigstens als kanonische Extracts), weil die drei Kernchecks sonst nicht beweisbar sind:
1) Plan enthält Request (Ref-Direction)  
2) Scope/Track Alignment  
3) Zeitreihenfolge request ≤ plan ≤ result

Wenn du die beiden Frames **1:1** paste (Plan + Request), liefere ich dir **ohne Optionen** direkt:
- **KETTEN_AUDIT_REPORT** (PASS/FAIL je Regelpunkt)
- **Evidence-Array fertig befüllt** (copy/paste in `PROOF_RUN_RESULT.p.evidence`)
- optional: **HASH_PROOF Frames** für beide Targets (wenn du’s als Standard willst)

---

## system · 2026-01-25T09:28:08.789161 UTC



---

## user · 2026-01-25T09:28:36.534081 UTC

Bitte Output Plan Rev als Frames.

---

## system · 2026-01-25T09:28:39.527894 UTC



---

## assistant · 2026-01-25T09:28:39.562340 UTC

Unix Epoch  
1769333104  
Time (UTC)  
Sun Jan 25 09:25:04 2026 UTC  
Time (Europe/Amsterdam)  
Sun Jan 25 10:25:04 2026 CET  

```json
// FILENAME: GX-PROOF-RUN-PLAN-AUTOBUILD-PLANREV-1769333104-0002.ndjson
{"id":"GX-PROOF-RUN-PLAN-AUTOBUILD-BLOCK-1769333104-0002","t":"BLOCK","ts_utc":"2026-01-25T09:25:04Z","ts_unix":1769333104,"vis":"PUBLIC","p":{"scope":"GXvLIBERTY","name":"PROOF_RUN_PLAN_AUTOBUILD_PLANREV","version":"1.0","rev":"0002","mode":"REFERENCE_ONLY","execution":"BLOCKED","automation":"OFF","freeze":"ON","guards":{"append_only":true,"no_phantom":true,"no_execution":true,"no_automation":true,"no_state_change_by_confirm":true,"proof_before_state":true},"refs":{"request_ref":"GX-AUTOBUILD-REQUEST-1769332704-0001","result_ref":"GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001","prior_plan_ref":"GX-PROOF-RUN-PLAN-AUTOBUILD-1769332879-0001"},"intent":"Plan-Revision: harte, deterministische Kettenprüfung REQUEST↔PLAN↔RESULT für AUTOBUILD. Keine Ausführung, kein Grant.","note":"Append-only Revision. Supersedes prior plan logically, does not delete it."},"h":"PLACEHOLDER_SHA256"}
{"id":"GX-PROOF-RUN-PLAN-AUTOBUILD-1769333104-0002","t":"PROOF_RUN_PLAN","ts_utc":"2026-01-25T09:25:04Z","ts_unix":1769333104,"vis":"PUBLIC","p":{"scope":"GXvLIBERTY","track":"GX_AUTOBUILD_ACTIVATION","plan_type":"CHAIN_AUDIT_ONLY","mode":"REFERENCE_ONLY","execution":"BLOCKED","automation":"OFF","freeze":"ON","guards":{"append_only":true,"no_phantom":true,"no_execution":true,"no_automation":true,"no_state_change_by_confirm":true,"proof_before_state":true},"inputs":{"request_ref":"GX-AUTOBUILD-REQUEST-1769332704-0001","result_ref":"GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001","self_plan_id":"GX-PROOF-RUN-PLAN-AUTOBUILD-1769333104-0002"},"objective":"Produce a reproducible PASS/FAIL decision for chain consistency (REQUEST→PLAN→RESULT) and guard alignment. This plan itself performs no execution.","pass_fail_contract":{"PASS_means":"All checks in CHECKLIST return true with evidence refs. Only then may an external actor record PROOF_RUN_RESULT.result=PASS and proceed to a separate proof-based GRANT/DECLARATION.","FAIL_means":"Any mandatory check fails OR evidence missing. Result must remain FAIL/PENDING; no authorization.","PENDING_means":"Checks not yet executed externally or evidence not recorded. No authorization."},"procedure":[{"step":1,"name":"Existence & Identity","checks":["FRAME_EXISTS(request_ref)","FRAME_EXISTS(self_plan_id)","FRAME_EXISTS(result_ref)","APPEND_ONLY(request_ref)","APPEND_ONLY(self_plan_id)","APPEND_ONLY(result_ref)"]},{"step":2,"name":"Scope/Track/State Alignment","checks":["SCOPE_MATCH(all == GXvLIBERTY)","TRACK_MATCH(plan.track == GX_AUTOBUILD_ACTIVATION)","MODE_REFERENCE_ONLY(all)","EXECUTION_BLOCKED(all)","AUTOMATION_OFF(all)","FREEZE_ON(all)"]},{"step":3,"name":"Reference Direction","checks":["RESULT_REFERENCES(plan_ref AND request_ref)","PLAN_REFERENCES(request_ref)","NO_DIVERGENT_REQUEST_REF(plan↔result)"]},{"step":4,"name":"Time-Anchor Order","checks":["TIME_ORDER(request.ts_unix <= plan.ts_unix <= result.ts_unix)","TIME_ORDER(request.ts_utc <= plan.ts_utc <= result.ts_utc)"]},{"step":5,"name":"No-Phantom / No-Confirm-Grant","checks":["NO_IMPLICIT_GRANT_LANGUAGE(request,plan,result)","NO_DEFAULT_PASS(plan,result)","AUTHORIZED_STATE_CHANGE_FALSE_WHEN_PENDING(result)"]},{"step":6,"name":"Hash Integrity (optional but hard if enabled)","checks":["IF_HASH_REQUIRED_THEN_H_VALID(request)","IF_HASH_REQUIRED_THEN_H_VALID(plan)","IF_HASH_REQUIRED_THEN_H_VALID(result)","OPTIONAL_HASH_PROOF_REFS(targets)"]}],"outputs_expected":{"proof_run_result_fields":{"result":"PASS|FAIL|PENDING","evidence.verified_prerequisites":"filled","evidence.guard_checks":"filled","evidence.dry_run_checks":"filled","evidence.side_effect_checks":"filled"},"authorization_rule":"Only PASS may allow separate GRANT/DECLARATION. This plan itself never authorizes."},"note":"This plan is definition-only. A real proof run must be performed externally; evidence must be recorded as refs."},"h":"PLACEHOLDER_SHA256"}
{"id":"GX-PROOF-RUN-CHECKLIST-AUTOBUILD-1769333104-0002","t":"CHECKLIST","ts_utc":"2026-01-25T09:25:04Z","ts_unix":1769333104,"vis":"PUBLIC","p":{"scope":"GXvLIBERTY","track":"GX_AUTOBUILD_ACTIVATION","plan_ref":"GX-PROOF-RUN-PLAN-AUTOBUILD-1769333104-0002","mandatory":[{"k":"FRAME_EXISTS(request_ref)","desc":"Request frame exists by exact ID."},{"k":"FRAME_EXISTS(plan_ref)","desc":"Plan frame exists by exact ID (this plan)."},{"k":"FRAME_EXISTS(result_ref)","desc":"Result frame exists by exact ID."},{"k":"SCOPE_MATCH(all == GXvLIBERTY)","desc":"scope is identical across request/plan/result."},{"k":"TRACK_MATCH(plan.track == GX_AUTOBUILD_ACTIVATION)","desc":"plan track matches AUTOBUILD activation track."},{"k":"MODE_REFERENCE_ONLY(all)","desc":"mode == REFERENCE_ONLY for request/plan/result."},{"k":"EXECUTION_BLOCKED(all)","desc":"execution == BLOCKED for request/plan/result."},{"k":"AUTOMATION_OFF(all)","desc":"automation == OFF for request/plan/result."},{"k":"FREEZE_ON(all)","desc":"freeze == ON for request/plan/result."},{"k":"RESULT_REFERENCES(plan_ref AND request_ref)","desc":"result_ref contains both plan_ref and request_ref correctly."},{"k":"PLAN_REFERENCES(request_ref)","desc":"plan_ref contains request_ref correctly."},{"k":"TIME_ORDER(request <= plan <= result)","desc":"ts_unix and ts_utc are ordered: request <= plan <= result."},{"k":"NO_IMPLICIT_GRANT_LANGUAGE","desc":"No language anywhere that confirmation implies grant/state change."},{"k":"AUTHORIZED_STATE_CHANGE_FALSE_WHEN_PENDING","desc":"Result keeps authorized_state_change=false while PENDING."}],"conditional":[{"k":"H_VALID_ALL","when":"hash_required=true","desc":"h equals sha256(canonical_json(p)) for each frame."},{"k":"HASH_PROOF_REFS_PRESENT","when":"hash_proof_policy=ENFORCED","desc":"HASH_PROOF frames exist and target p fields correctly."}],"refs":{"request_ref":"GX-AUTOBUILD-REQUEST-1769332704-0001","result_ref":"GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001"},"note":"Checklist is deterministic. FAIL if any mandatory item is false or evidence missing."},"h":"PLACEHOLDER_SHA256"}
{"id":"GX-PROOF-RUN-EVIDENCE-TEMPLATE-AUTOBUILD-1769333104-0002","t":"EVIDENCE_TEMPLATE","ts_utc":"2026-01-25T09:25:04Z","ts_unix":1769333104,"vis":"PUBLIC","p":{"scope":"GXvLIBERTY","track":"GX_AUTOBUILD_ACTIVATION","plan_ref":"GX-PROOF-RUN-PLAN-AUTOBUILD-1769333104-0002","template":{"verified_prerequisites":[{"check":"FRAME_EXISTS(plan_ref)","ok":false,"evidence_refs":[]},{"check":"FRAME_EXISTS(request_ref)","ok":false,"evidence_refs":[]},{"check":"FRAME_EXISTS(result_ref)","ok":false,"evidence_refs":[]}],"guard_checks":[{"check":"MODE_REFERENCE_ONLY(all)","ok":false,"evidence_refs":[]},{"check":"EXECUTION_BLOCKED(all)","ok":false,"evidence_refs":[]},{"check":"AUTOMATION_OFF(all)","ok":false,"evidence_refs":[]},{"check":"FREEZE_ON(all)","ok":false,"evidence_refs":[]}],"dry_run_checks":[{"check":"PLAN_REFERENCES(request_ref)","ok":false,"evidence_refs":[]},{"check":"RESULT_REFERENCES(plan_ref AND request_ref)","ok":false,"evidence_refs":[]},{"check":"TIME_ORDER(request<=plan<=result)","ok":false,"evidence_refs":[]},{"check":"NO_IMPLICIT_GRANT_LANGUAGE","ok":false,"evidence_refs":[]}],"side_effect_checks":[{"check":"AUTHORIZED_STATE_CHANGE_FALSE_WHEN_PENDING","ok":true,"evidence_refs":["GX-PROOF-RUN-RESULT-AUTOBUILD-1769332989-0001"]}],"optional_hash_checks":[{"check":"H_VALID_ALL","ok":false,"evidence_refs":[]},{"check":"HASH_PROOF_REFS_PRESENT","ok":false,"evidence_refs":[]}]},"note":"Copy-paste into PROOF_RUN_RESULT.p.evidence after external verification. This template does not assert truth."},"h":"PLACEHOLDER_SHA256"}
```

---

