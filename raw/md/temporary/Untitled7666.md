# K501 v1.1 — One-Command Full Validator
# Checks: YAML header required keys + UTC/Unix presence + sha256 scope/body + canonicalization utf8+lf + hash format
# Also prints: computed sha256(body) + body line count
#
# Usage:
#   ./k501_validate.sh file.md
# Exit codes:
#   0 ok, 1 fail

cat > k501_validate.sh <<'SH'
#!/usr/bin/env bash
set -euo pipefail

f="${1:-}"
if [[ -z "$f" || ! -f "$f" ]]; then
  echo "usage: $0 file.md" >&2
  exit 1
fi

# --- helpers ---------------------------------------------------------------
fail(){ echo "FAIL: $*" >&2; exit 1; }
ok(){ echo "OK: $*"; }

# Require exactly 2 YAML fences '---' (at least) and compute body start line
body_start="$(
  awk '
    BEGIN{c=0}
    /^---[[:space:]]*$/ {c++; if (c==2){print NR+1; exit}}
  ' "$f"
)"

[[ -n "${body_start:-}" ]] || fail "missing YAML closing fence (need 2 lines with exactly ---)"
# Ensure file starts with YAML fence
head -n 1 "$f" | grep -qx '---' || fail "file must start with --- (YAML frontmatter)"

# Extract header (between fences, excluding fences)
header="$(
  awk '
    BEGIN{c=0}
    /^---[[:space:]]*$/ {c++; next}
    c==1 {print}
    c>=2 {exit}
  ' "$f"
)"

# Extract body (after second fence), normalize to LF
body="$(
  tail -n +"$body_start" "$f" | tr -d '\r'
)"

# Count body lines (after LF normalization)
body_lines="$(printf "%s\n" "$body" | wc -l | tr -d ' ')"

# Compute sha256(body) over utf8+lf (we assume UTF-8 bytes; LF normalized by tr -d '\r')
hash="$(printf "%s" "$body" | sha256sum | awk '{print $1}')"

# --- validate required header keys -----------------------------------------
# Minimal required keys for your v1.1 standard (adjust if you want more)
req_keys=(
  'k501.schema'
  'k501.mode'
  'k501.append_only'
  'document.id'
  'frame.id'
  'version'
  'author.name'
  'time.utc'
  'time.unix'
  'source.canonical'
  'hash.algorithm'
  'hash.scope'
  'hash.canonicalization'
  'hash.document'
)

for k in "${req_keys[@]}"; do
  # match YAML-ish: key: value  (allow spaces)
  printf "%s\n" "$header" | grep -Eq "^[[:space:]]*${k//./\\.}[[:space:]]*:" || fail "missing header key: $k"
done
ok "required header keys present"

# --- validate values (strict where it matters) -----------------------------
# k501.schema exact
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.schema:[[:space:]]*"(K501-DOC/v1\.1)"[[:space:]]*$' \
  || fail 'k501.schema must be "K501-DOC/v1.1"'
ok "schema ok"

# mode exact
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.mode:[[:space:]]*"(REFERENCE_ONLY)"[[:space:]]*$' \
  || fail 'k501.mode must be "REFERENCE_ONLY"'
ok "mode ok"

# append_only true
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.append_only:[[:space:]]*(true|True)[[:space:]]*$' \
  || fail "k501.append_only must be true"
ok "append_only ok"

# time.utc ISO-8601 Zulu basic check
utc="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*time\.utc:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$utc" ]] || fail "time.utc empty"
printf "%s" "$utc" | grep -Eq '^[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}Z$' \
  || fail "time.utc must match YYYY-MM-DDTHH:MM:SSZ"
ok "time.utc format ok"

# time.unix integer (allow negative if you want; here allow -?\d+)
unix="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*time\.unix:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$unix" ]] || fail "time.unix empty"
printf "%s" "$unix" | grep -Eq '^-?[0-9]+$' || fail "time.unix must be integer"
ok "time.unix format ok"

# hash algorithm/scope/canonicalization exact
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.algorithm:[[:space:]]*"(sha256)"[[:space:]]*$' \
  || fail 'hash.algorithm must be "sha256"'
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.scope:[[:space:]]*"(body)"[[:space:]]*$' \
  || fail 'hash.scope must be "body"'
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.canonicalization:[[:space:]]*"(utf8\+lf)"[[:space:]]*$' \
  || fail 'hash.canonicalization must be "utf8+lf"'
ok "hash policy ok"

# hash.document must be 64 hex OR the placeholder TO_BE_COMPUTED
doc_hash="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*hash\.document:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$doc_hash" ]] || fail "hash.document empty"
if [[ "$doc_hash" != "TO_BE_COMPUTED" ]]; then
  printf "%s" "$doc_hash" | tr 'A-F' 'a-f' | grep -Eq '^[0-9a-f]{64}$' || fail "hash.document must be 64 hex or TO_BE_COMPUTED"
  # If present, require it matches computed hash
  [[ "${doc_hash,,}" == "$hash" ]] || fail "hash.document does not match computed sha256(body)"
  ok "hash.document matches body"
else
  ok "hash.document is TO_BE_COMPUTED (computed shown below)"
fi

# --- output summary ---------------------------------------------------------
echo "----"
echo "FILE: $f"
echo "BODY_LINES: $body_lines"
echo "SHA256_BODY(utf8+lf): $hash"
echo "----"
ok "VALID"
SH

chmod +x k501_validate.sh
echo "Created: ./k501_validate.sh"
echo "Run: ./k501_validate.sh YOUR.md"