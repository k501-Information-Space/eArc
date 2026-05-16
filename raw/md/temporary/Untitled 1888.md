# One-command: create validator + run it immediately
# usage:
#   FILE=your.md  bash -c '...'

FILE="${FILE:-}"
[[ -n "$FILE" ]] || { echo "Set FILE=path/to/doc.md" >&2; exit 1; }

cat > k501_validate.sh <<'SH'
#!/usr/bin/env bash
set -euo pipefail

f="${1:-}"
if [[ -z "$f" || ! -f "$f" ]]; then
  echo "usage: $0 file.md" >&2
  exit 1
fi

fail(){ echo "FAIL: $*" >&2; exit 1; }
ok(){ echo "OK: $*"; }

body_start="$(
  awk '
    BEGIN{c=0}
    /^---[[:space:]]*$/ {c++; if (c==2){print NR+1; exit}}
  ' "$f"
)"
[[ -n "${body_start:-}" ]] || fail "missing YAML closing fence (need 2 lines with exactly ---)"
head -n 1 "$f" | grep -qx '---' || fail "file must start with --- (YAML frontmatter)"

header="$(
  awk '
    BEGIN{c=0}
    /^---[[:space:]]*$/ {c++; next}
    c==1 {print}
    c>=2 {exit}
  ' "$f"
)"

body="$(
  tail -n +"$body_start" "$f" | tr -d '\r'
)"

body_lines="$(printf "%s\n" "$body" | wc -l | tr -d ' ')"
hash="$(printf "%s" "$body" | sha256sum | awk '{print $1}')"

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
  printf "%s\n" "$header" | grep -Eq "^[[:space:]]*${k//./\\.}[[:space:]]*:" || fail "missing header key: $k"
done
ok "required header keys present"

printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.schema:[[:space:]]*"(K501-DOC/v1\.1)"[[:space:]]*$' \
  || fail 'k501.schema must be "K501-DOC/v1.1"'
ok "schema ok"

printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.mode:[[:space:]]*"(REFERENCE_ONLY)"[[:space:]]*$' \
  || fail 'k501.mode must be "REFERENCE_ONLY"'
ok "mode ok"

printf "%s\n" "$header" | grep -Eq '^[[:space:]]*k501\.append_only:[[:space:]]*(true|True)[[:space:]]*$' \
  || fail "k501.append_only must be true"
ok "append_only ok"

utc="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*time\.utc:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$utc" ]] || fail "time.utc empty"
printf "%s" "$utc" | grep -Eq '^[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}Z$' \
  || fail "time.utc must match YYYY-MM-DDTHH:MM:SSZ"
ok "time.utc format ok"

unix="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*time\.unix:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$unix" ]] || fail "time.unix empty"
printf "%s" "$unix" | grep -Eq '^-?[0-9]+$' || fail "time.unix must be integer"
ok "time.unix format ok"

printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.algorithm:[[:space:]]*"(sha256)"[[:space:]]*$' \
  || fail 'hash.algorithm must be "sha256"'
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.scope:[[:space:]]*"(body)"[[:space:]]*$' \
  || fail 'hash.scope must be "body"'
printf "%s\n" "$header" | grep -Eq '^[[:space:]]*hash\.canonicalization:[[:space:]]*"(utf8\+lf)"[[:space:]]*$' \
  || fail 'hash.canonicalization must be "utf8+lf"'
ok "hash policy ok"

doc_hash="$(printf "%s\n" "$header" | awk -F': ' '/^[[:space:]]*hash\.document:/ {sub(/^[[:space:]]*/,"",$2); gsub(/"/,"",$2); print $2; exit}')"
[[ -n "$doc_hash" ]] || fail "hash.document empty"
if [[ "$doc_hash" != "TO_BE_COMPUTED" ]]; then
  printf "%s" "$doc_hash" | tr 'A-F' 'a-f' | grep -Eq '^[0-9a-f]{64}$' || fail "hash.document must be 64 hex or TO_BE_COMPUTED"
  [[ "${doc_hash,,}" == "$hash" ]] || fail "hash.document does not match computed sha256(body)"
  ok "hash.document matches body"
else
  ok "hash.document is TO_BE_COMPUTED (computed shown below)"
fi

echo "----"
echo "FILE: $f"
echo "BODY_LINES: $body_lines"
echo "SHA256_BODY(utf8+lf): $hash"
echo "----"
ok "VALID"
SH

chmod +x k501_validate.sh
./k501_validate.sh "$FILE"