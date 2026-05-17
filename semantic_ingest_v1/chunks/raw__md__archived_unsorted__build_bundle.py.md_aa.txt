#!/usr/bin/env python3
import zipfile, datetime
from pathlib import Path

ROOT = Path("earc")
OUTD = ROOT / "exports"
OUTD.mkdir(parents=True, exist_ok=True)

def utc_tag():
    return datetime.datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")

bundle = OUTD / f"earc_bundle_{utc_tag()}.zip"

include = [
  "diamond/",
  "vault/",
  "index/earc.sqlite",
  "index/manifest.json",
  "feeds/tat1.rss",
  "feeds/tat1.atom",
]

with zipfile.ZipFile(bundle, "w", compression=zipfile.ZIP_DEFLATED) as z:
    for item in include:
        p = ROOT / item
        if p.is_dir():
            for f in p.rglob("*"):
                if f.is_file():
                    z.write(f, f.relative_to(ROOT))
        elif p.is_file():
            z.write(p, p.relative_to(ROOT))

print(bundle.as_posix())