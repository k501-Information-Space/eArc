#!/usr/bin/env python3
import sqlite3, datetime
from pathlib import Path
import html

ROOT = Path("earc")
DB = ROOT / "index" / "earc.sqlite"
OUT = ROOT / "feeds"

OUT.mkdir(parents=True, exist_ok=True)

def utc():
    return datetime.datetime.utcnow().replace(microsecond=0).isoformat() + "Z"

con = sqlite3.connect(DB)
cur = con.cursor()

cur.execute("SELECT COUNT(*) FROM artifacts")
count = cur.fetchone()[0]

now = utc()
title = f"eArc · Diamond Status · {now}"
desc = f"artifacts={count} · comm=OFF · tat1=active-priority"

# RSS 2.0
rss = f"""<?xml version="1.0" encoding="UTF-8"?>
<rss version="2.0">
<channel>
<title>eArc · TAT1</title>
<link>https://iinkognit0.de/earc-feed/</link>
<description>Local artifact feed (no transmit)</description>
<item>
<title>{html.escape(title)}</title>
<guid isPermaLink="false">{now}</guid>
<pubDate>{datetime.datetime.utcnow().strftime("%a, %d %b %Y %H:%M:%S GMT")}</pubDate>
<description>{html.escape(desc)}</description>
</item>
</channel>
</rss>
"""
(OUT / "tat1.rss").write_text(rss, encoding="utf-8")

# Atom 1.0
atom = f"""<?xml version="1.0" encoding="utf-8"?>
<feed xmlns="http://www.w3.org/2005/Atom">
<title>eArc · TAT1</title>
<id>urn:iarc:tat1</id>
<updated>{now}</updated>
<entry>
<title>{html.escape(title)}</title>
<id>urn:iarc:entry:{now}</id>
<updated>{now}</updated>
<summary>{html.escape(desc)}</summary>
</entry>
</feed>
"""
(OUT / "tat1.atom").write_text(atom, encoding="utf-8")

cur.execute("""
  INSERT INTO events (timestamp_utc,event,details)
  VALUES (?,?,?)
""", (now, "tat1_generate", f"feeds generated: {count} artifacts"))

con.commit()
con.close()