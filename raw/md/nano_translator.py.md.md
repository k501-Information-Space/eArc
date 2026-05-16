# Nano Translator (Python)

Status: minimal · deterministic · non-executing by default

This translator converts **Frames** into **human-readable text**.
It does not write back.
It does not modify frames.
It does not interpret beyond structure.

---

## Code

```python
import json
from pathlib import Path

def load_frame(path: Path) -> dict:
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)

def translate_frame(frame: dict) -> str:
    lines = []
    lines.append(f"Frame ID: {frame.get('id', 'unknown')}")
    lines.append(f"Status: {frame.get('status', 'undefined')}")
    lines.append("")
    lines.append(frame.get("content", "").strip())
    return "\n".join(lines)

def translate_file(frame_path: str) -> str:
    frame = load_frame(Path(frame_path))
    return translate_frame(frame)

# No execution on import
# No file writing
# Pure transformation