# Phase_7_cli.md

This phase adds the command-line surface over the frozen kernel. It exposes operational commands only and does not alter truth semantics [web:178][web:187].

## Target files

- `src/k501/cli/main.py`
- `src/k501/cli/commands/*.py`
- `tests/unit/test_cli.py`
- `tests/integration/test_cli_replay.py`

## Dataclasses

- `CLIContext`
- `CommandResult`

## Functions

- `main()`
- `cmd_init()`
- `cmd_append()`
- `cmd_project()`
- `cmd_build_graph()`
- `cmd_freeze_archive()`
- `cmd_replay_archive()`
- `cmd_validate_replay()`

## Public interfaces

- `k501` console script
- command return codes
- CLI help text

## pytest tests

- CLI help renders
- init command creates layout
- append command writes transition
- project command materializes StateObject
- replay command validates digest
- error codes are stable

## mypy constraints

- argparse or typer types explicit
- no loosely typed command dispatch
- CLI context typed explicitly

## ruff constraints

- no command duplication
- no branching logic that bypasses validators
- no unused CLI flags

## Migration mapping from existing modules

- no current CLI modules in the tree.
- wire commands to storage/core modules only.

## Estimated git commits

- 1 to 2 commits.

## Expected repository tree after completion

```text
src/k501/cli/
├── __init__.py
├── main.py
└── commands/
tests/unit/
└── test_cli.py
tests/integration/
└── test_cli_replay.py
```