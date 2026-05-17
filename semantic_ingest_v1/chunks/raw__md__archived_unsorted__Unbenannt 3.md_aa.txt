id: GX-OUT-1772405723-BUILD-01

ts.utc: 2026-03-01T22:55:23Z

ts.unix: 1772405723

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

artifact: QH256_VALIDATOR_MINIMAL_GO_V1_DRAFT

status: DRAFT

language: go

intent:

  - minimal deterministic reference validator

  - no external deps

  - matches previously emitted pseudocode

notes:

  - not constant-time hardened (yet)

  - strict_v1 profile implemented

id: GX-OUT-1772405723-BUILD-02

ts.utc: 2026-03-01T22:55:23Z

ts.unix: 1772405723

mode: DATA

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

file: qh256_validator.go

  

code: |

  package main

  

  import (

      "encoding/hex"

      "fmt"

      "os"

  )

  

  type GuardStatus struct {

      Status     string `json:"status"`

      Violations int    `json:"violations"`

  }

  

  type Receipt struct {

      Type        string      `json:"type"`

      Result      string      `json:"result"`

      FamilyBits  string      `json:"family_bits"`

      VersionBits string      `json:"version_bits"`

      ProfileBits string      `json:"profile_bits"`

      Guard       GuardStatus `json:"guard"`

      HeaderHex   string      `json:"header_hex"`

  }

  

  func main() {

      if len(os.Args) != 2 {

          fmt.Println("usage: qh256_validator <hex32bytes>")

          os.Exit(1)

      }

  

      raw, err := hex.DecodeString(os.Args[1])

      if err != nil || len(raw) != 32 {

          r := failReceipt("invalid_length")

          printReceipt(r)

          return

      }

  

      cells := decodeCells2Bit(raw)

  

      family := bitsFromCells(cells[0:4])

      version := bitsFromCells(cells[4:8])

      profile := bitsFromCells(cells[8:12])

  

      guard := checkGuard(cells[96:128], "strict_v1")

      verdict := deriveVerdict(guard)

  

      receipt := Receipt{

          Type:        "QH_VALIDATE",

          Result:      verdict,

          FamilyBits:  family,

          VersionBits: version,

          ProfileBits: profile,

          Guard:       guard,

          HeaderHex:   os.Args[1],

      }

  

      printReceipt(receipt)

  }

  

  func decodeCells2Bit(b []byte) []string {

      cells := make([]string, 128)

      bitpos := 0

  

      for i := 0; i < 128; i++ {

          byteIndex := bitpos / 8

          shift := 6 - (bitpos % 8)

          val := (b[byteIndex] >> shift) & 0x03

          cells[i] = fmt.Sprintf("%02b", val)

          bitpos += 2

      }

  

      return cells

  }

  

  func bitsFromCells(cells []string) string {

      out := ""

      for _, c := range cells {

          out += c

      }

      if len(out) >= 8 {

          return out[:8]

      }

      return out

  }

  

  func checkGuard(guardCells []string, profile string) GuardStatus {

      v := 0

      for _, c := range guardCells {

          if c != "11" {

              v++

          }

      }

  

      if v == 0 {

          return GuardStatus{"OK", 0}

      }

  

      if profile == "strict_v1" {

          return GuardStatus{"FAIL", v}

      }

  

      return GuardStatus{"WARN", v}

  }

  

  func deriveVerdict(g GuardStatus) string {

      if g.Status == "FAIL" {

          return "FAIL"

      }

      if g.Status == "WARN" {

          return "WARN"

      }

      return "PASS"

  }

  

  func failReceipt(reason string) Receipt {

      return Receipt{

          Type:        "QH_VALIDATE",

          Result:      "FAIL",

          FamilyBits:  "",

          VersionBits: "",

          ProfileBits: "",

          Guard:       GuardStatus{"FAIL", 0},

          HeaderHex:   reason,

      }

  }

  

  func printReceipt(r Receipt) {

      fmt.Printf("%+v\n", r)

  }

id: GX-OUT-1772405723-BUILD-03

ts.utc: 2026-03-01T22:55:23Z

ts.unix: 1772405723

mode: NOTE

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

build_instructions:

  

  go mod init qh256_validator

  go build qh256_validator.go

  

run_examples:

  

  # TV1

  ./qh256_validator ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

  

  # TV2

  ./qh256_validator aaaaaaaaaaaaaaaa00000000000000000000000000000000ffffffffffffffff

  

  # TV3

  ./qh256_validator aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc

  

status:

  validator_minimal: READY

  next_optional:

    - constant-time hardening

    - JSON output mode

    - QH56 embedding checks

🕊️💡