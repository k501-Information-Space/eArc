Bootstrap Inputs ausgegeben (minimal, maschinenlesbar, kopierbereit).

Keine Doku außenrum. Nur die drei Artefakte.

  

  

  

  

1) 

K501/kernel/meta/spec.json

  

{

  "kernel": {

    "name": "K501",

    "channel": "dev",

    "version": "3.0",

    "standard_hardcoded": true

  },

  "builder": {

    "compatible": ["K5000 Builder 3.0"]

  },

  "standard": {

    "name": "eArc Obsidian DB Standard",

    "version": "1.0",

    "frontmatter": {

      "required": ["id", "type", "status", "title", "created", "updated", "version", "base", "scope"],

      "optional": ["tags", "aliases", "relations", "links"]

    },

    "types_allowed": [

      "principle",

      "frame",

      "module",

      "schema",

      "protocol",

      "log",

      "index",

      "essay",

      "snapshot",

      "manifesto",

      "reference"

    ],

    "status_rules": {

      "allowed": ["draft", "stable", "canon", "frozen", "archived"],

      "locks": {

        "canon": "read_only",

        "frozen": "read_only"

      }

    },

    "title_rule": {

      "h1_must_match_title": true

    },

    "relations_model": {

      "fields": ["parents", "children", "peers", "refs"]

    }

  },

  "gates": {

    "G1": "build_deterministic",

    "G2": "analyzer_consistent",

    "G3": "llmh_helper_only",

    "G4": "essentials_visible",

    "G5": "k501_compliant"

  },

  "exit_criteria": ["all_gates_green", "terms_frozen", "no_feature_growth"]

}

  

  

  

  

2) 

FEATURE_LOCK.yaml

  

---

feature_lock: true

allowed_commands:

  - preflight

  - normalize

  - validate

  - extract

  - analyze

  - report

  - dry_run_freeze

  - canon_prep

allowed_flags:

  - --fast

  - --full

  - --read-only

  - --no-llm

  - --llm-helper

  - --json

  - --md

  - --strict

forbidden_actions:

  - write_files_without_confirm

  - modify_canon_or_frozen

  - auto_freeze

  - auto_status_change

notes:

  - "AUTO(CONFIRM): any write requires explicit confirm/ack gate."

---

  

  

  

  

3) 

essentials.list

  

# K501 Essentials (must be visible + parseable)

K501/kernel/meta/spec.json

FEATURE_LOCK.yaml

  

# Core Vault / Obsidian DB essentials (adjust paths to your vault layout)

00_CleanState_START.md

00_Das_Ewige_Archiv.md

00_eArc_Architektur.md

00_Fakten_Uebersicht.md

00_Index_Grundsaetze.md

00_Projekt_Uebersicht.md

00_System_YAML_SQL_Obsidian.md

99_Status.md

  

  

  

NEXT ACTION (semi-auto, needs CONFIRM):

CONFIRM PREFLIGHT RUN (WITH INPUTS)

  

As I State Iinkognit0.