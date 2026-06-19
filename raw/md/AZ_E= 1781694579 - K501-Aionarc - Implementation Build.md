
while true; do date +%s; sleep 1; clear; done

Good. Looking at the architecture and the fact that you already have:

- Architecture documents
    
- Engineering Plan v6.0
    
- JSON schemas
    
- Ontology defined
    
- Phase 0 completed
    

I would **not start coding retrieval, embeddings, agents, APIs, or governance yet**.

The fastest path is to build the deterministic backbone first.

Tomorrow's Step 15 should be:

> Create the workspace, project skeleton, package structure, tooling, and validation pipeline.

The objective is:

> "make `pytest`, `ruff`, `mypy`, imports, schemas, and package loading work before writing business logic."

---

# 1. Create Project Directory

```bash
mkdir -p ~/Projekte/k501-aionarc
cd ~/Projekte/k501-aionarc
```

Initialize git:

```bash
git init
```

---

# 2. Install UV

If not already installed:

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
```

reload shell:

```bash
source ~/.bashrc
```

verify:

```bash
uv --version
```

---

# 3. Initialize Python Project

```bash
uv init
```

or

```bash
uv init --package
```

This generates:

```text
pyproject.toml
src/
```

---

# 4. Create Repository Skeleton

From project root:

```bash
mkdir -p \
docs/architecture \
docs/api \
docs/schemas \
docs/runbooks \
docs/adr \
configs \
data/archive \
data/manifests \
data/proofs \
data/audits \
data/claims \
data/beliefs \
data/snapshots \
data/freezes \
data/indexes \
scripts \
tests/unit \
tests/integration \
tests/e2e \
tests/fixtures/documents \
tests/fixtures/graphs \
tests/fixtures/proofs \
tests/fixtures/audits \
benchmarks/datasets \
benchmarks/queries \
benchmarks/expected
```

---

# 5. Create Source Tree

```bash
mkdir -p src/k501/{\
api/routes,\
api/middleware,\
core,\
evidence,\
graph,\
retrieval,\
governance,\
agent,\
embeddings,\
storage,\
observability,\
utils,\
workers}
```

---

# 6. Create Package Files

```bash
find src/k501 -type d -exec touch {}/__init__.py \;
```

---

# 7. Install Core Dependencies

```bash
uv add \
fastapi \
uvicorn \
pydantic \
networkx \
numpy \
orjson \
jsonschema \
sqlalchemy \
httpx \
typer \
rich
```

---

# 8. Install Development Dependencies

```bash
uv add --dev \
pytest \
pytest-cov \
ruff \
mypy
```

---

# 9. Create Basic Configuration Files

```bash
touch \
ruff.toml \
mypy.ini \
pytest.ini \
.gitignore \
.env.example \
Makefile
```

---

# 10. Minimal Ruff Config

`ruff.toml`

```toml
line-length = 100

[lint]
select = ["E","F","I"]
```

---

# 11. Minimal Mypy Config

`mypy.ini`

```ini
[mypy]
python_version = 3.12
strict = True
```

---

# 12. Minimal Pytest Config

`pytest.ini`

```ini
[pytest]
testpaths = tests
```

---

# 13. Create Core Primitive Stubs

Create:

```text
src/k501/core/
```

Files:

```text
axiom.py
kernel.py
frame.py
snapshot.py
freeze.py
state_object.py
lifecycle.py
```

Each file:

```python
from pydantic import BaseModel
```

Nothing more yet.

---

# 14. Create First Validation Test

`tests/unit/test_imports.py`

```python
def test_import():
    import k501

    assert k501 is not None
```

Run:

```bash
uv run pytest
```

Goal:

```text
1 passed
```

---

# 15. Create VS Codium Workspace

Open:

```bash
codium .
```

Install extensions:

- Python
    
- Ruff
    
- Pylance
    
- Even Better TOML
    
- YAML
    

Workspace settings:

`.vscode/settings.json`

```json
{
    "python.defaultInterpreterPath": ".venv/bin/python",
    "python.testing.pytestEnabled": true,
    "python.linting.enabled": true,
    "editor.formatOnSave": true
}
```

---

# End State Tomorrow

When we stop tomorrow, the repository should:

```text
✓ git initialized
✓ uv environment working
✓ package imports working
✓ pytest working
✓ ruff working
✓ mypy working
✓ directory tree complete
✓ source tree complete
✓ VS Codium configured
✓ first test green
```

Only after that would I move to the first actual implementation layer:

```text
FRAME
STATE_OBJECT
SNAPSHOT
FREEZE
ARCHIVE
```

in that exact order, because everything else in AIONARC depends on those primitives.