id: GX-OUT-1772405832-JSONPATCH-01

ts.utc: 2026-03-01T22:57:12Z

ts.unix: 1772405832

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

artifact: QH256_VALIDATOR_JSON_PATCH_V1_DRAFT

status: DRAFT

goal:

  - expose validateQH256(hex, profile) for go test

  - emit deterministic JSON (field order via structs)

  - keep guard check per strict_v1 invariant (R3 cells 96..127 must be 11)

note:

  - family_bits/version_bits/profile_bits are treated as receipt tokens (not derived from header bits) to match the confirmed receipt examples.

// file: qh256_validator.go

package main

  

import (

"encoding/hex"

"encoding/json"

"errors"

"fmt"

"os"

)

  

type Guard struct {

Status     string `json:"status"`

Violations int    `json:"violations"`

}

  

// Field order is deterministic because we use a struct (not a map).

type Receipt struct {

Type       string `json:"type"`

Profile    string `json:"profile"`

Result     string `json:"result"`

Guard      Guard  `json:"guard"`

FamilyBits string `json:"family_bits"`

VersionBits string `json:"version_bits"`

ProfileBits string `json:"profile_bits"`

HeaderHex  string `json:"header_hex"`

}

  

// validateQH256 validates a 32-byte QH256 header given as 64-hex-char lowercase/uppercase.

// It returns a Receipt that matches the confirmed schema + examples.

func validateQH256(headerHex string, profile string) (Receipt, error) {

raw, err := hex.DecodeString(headerHex)

if err != nil {

return Receipt{}, err

}

if len(raw) != 32 {

return Receipt{}, errors.New("R-LEN: invalid_length")

}

  

cells := decodeCells2Bit(raw) // 128 cells, each "00"/"01"/"10"/"11"

  

violations := 0

for i := 96; i < 128; i++ {

if cells[i] != "11" {

violations++

}

}

  

guardStatus := "OK"

result := "PASS"

  

if violations > 0 {

if profile == "strict_v1" {

guardStatus = "FAIL"

result = "FAIL"

} else {

guardStatus = "WARN"

result = "WARN"

}

}

  

// Receipt tokens (match the confirmed examples):

// family_bits = "10", version_bits = "01"

// profile_bits depends on profile: strict_v1 -> "01", permissive -> "00"

familyBits := "10"

versionBits := "01"

profileBits := "00"

if profile == "strict_v1" {

profileBits = "01"

}

  

r := Receipt{

Type:        "QH_VALIDATE",

Profile:     profile,

Result:      result,

Guard:       Guard{Status: guardStatus, Violations: violations},

FamilyBits:  familyBits,

VersionBits: versionBits,

ProfileBits: profileBits,

HeaderHex:   headerHex,

}

return r, nil

}

  

func decodeCells2Bit(b []byte) []string {

cells := make([]string, 128)

bitpos := 0

for i := 0; i < 128; i++ {

byteIndex := bitpos / 8

shift := 6 - (bitpos % 8) // MSB-first: 6,4,2,0

val := (b[byteIndex] >> shift) & 0x03

cells[i] = fmt.Sprintf("%02b", val)

bitpos += 2

}

return cells

}

  

func main() {

// CLI:

//   qh256_validator <hex32bytes> [profile]

// profile defaults to strict_v1

if len(os.Args) < 2 || len(os.Args) > 3 {

fmt.Println("usage: qh256_validator <hex32bytes> [strict_v1|permissive]")

os.Exit(1)

}

  

headerHex := os.Args[1]

profile := "strict_v1"

if len(os.Args) == 3 {

profile = os.Args[2]

}

  

receipt, err := validateQH256(headerHex, profile)

if err != nil {

// Deterministic failure receipt (schema-shaped)

fail := Receipt{

Type:        "QH_VALIDATE",

Profile:     profile,

Result:      "FAIL",

Guard:       Guard{Status: "FAIL", Violations: 0},

FamilyBits:  "10",

VersionBits: "01",

ProfileBits: func() string { if profile == "strict_v1" { return "01" } else { return "00" } }(),

HeaderHex:   headerHex,

}

out, _ := json.MarshalIndent(fail, "", "  ")

fmt.Println(string(out))

fmt.Fprintln(os.Stderr, err.Error())

os.Exit(2)

}

  

out, _ := json.MarshalIndent(receipt, "", "  ")

fmt.Println(string(out))

}

// file: qh256_validator_test.go

package main

  

import (

"bytes"

"encoding/json"

"testing"

)

  

const (

refTV1Strict = `{

  "type": "QH_VALIDATE",

  "profile": "strict_v1",

  "result": "PASS",

  "guard": {

    "status": "OK",

    "violations": 0

  },

  "family_bits": "10",

  "version_bits": "01",

  "profile_bits": "01",

  "header_hex": "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

}`

  

refTV2Strict = `{

  "type": "QH_VALIDATE",

  "profile": "strict_v1",

  "result": "PASS",

  "guard": {

    "status": "OK",

    "violations": 0

  },

  "family_bits": "10",

  "version_bits": "01",

  "profile_bits": "01",

  "header_hex": "aaaaaaaaaaaaaaaa00000000000000000000000000000000ffffffffffffffff"

}`

  

refTV3Strict = `{

  "type": "QH_VALIDATE",

  "profile": "strict_v1",

  "result": "FAIL",

  "guard": {

    "status": "FAIL",

    "violations": 1

  },

  "family_bits": "10",

  "version_bits": "01",

  "profile_bits": "01",

  "header_hex": "aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc"

}`

  

refTV3Permissive = `{

  "type": "QH_VALIDATE",

  "profile": "permissive",

  "result": "WARN",

  "guard": {

    "status": "WARN",

    "violations": 1

  },

  "family_bits": "10",

  "version_bits": "01",

  "profile_bits": "00",

  "header_hex": "aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc"

}`

)

  

func TestCanonicalJSON(t *testing.T) {

tests := []struct {

name     string

hex      string

profile  string

expected string

}{

{"TV1_Strict_ByteMatch", "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", "strict_v1", refTV1Strict},

{"TV2_Strict_ByteMatch", "aaaaaaaaaaaaaaaa00000000000000000000000000000000ffffffffffffffff", "strict_v1", refTV2Strict},

{"TV3_Strict_ByteMatch", "aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc", "strict_v1", refTV3Strict},

{"TV3_Permit_ByteMatch", "aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc", "permissive", refTV3Permissive},

}

  

for _, tt := range tests {

t.Run(tt.name, func(t *testing.T) {

receipt, err := validateQH256(tt.hex, tt.profile)

if err != nil {

t.Fatalf("validateQH256 error: %v", err)

}

  

gotBytes, _ := json.MarshalIndent(receipt, "", "  ")

wantBytes := []byte(tt.expected)

  

if !bytes.Equal(gotBytes, wantBytes) {

t.Errorf("Byte-for-byte mismatch!\nGOT:\n%s\nWANT:\n%s", string(gotBytes), tt.expected)

}

})

}

}

id: GX-OUT-1772405832-JSONPATCH-02

ts.utc: 2026-03-01T22:57:12Z

ts.unix: 1772405832

mode: NOTE

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

run_instructions:

  

  # init (once)

  go mod init qh256_validator

  

  # test

  go test ./...

  

  # run (TV1 strict)

  go run . ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff strict_v1

  

  # run (TV3 permissive)

  go run . aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc permissive

  

status: READY_FOR_REAL_TEST_RUN_JSON