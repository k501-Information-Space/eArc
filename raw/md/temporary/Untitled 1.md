-- PATH: 00_Grundsaetze/web/earc-website-konzept.sql
-- Minimaler Struktur-Snapshot (maschinenlesbar)

CREATE TABLE IF NOT EXISTS earc_config (
  key TEXT PRIMARY KEY,
  value TEXT NOT NULL
);

INSERT OR REPLACE INTO earc_config (key, value) VALUES
('project.name', 'iInkognit0'),
('system.name', 'eArc – Das Ewige Archiv'),
('style.palette', 'black_on_white'),
('style.shapes', 'square_only'),
('style.borders', 'thin_black'),
('style.no_rgb', 'true'),
('style.no_glow', 'true'),
('style.no_glass', 'true'),
('origin.url', 'https://iinkognit0.de/'),
('page.earc.url', 'https://iinkognit0.de/earc/'),
('page.podcast.url', 'https://iinkognit0.de/podcast/'),
('substack.url', 'https://iinkognit0.substack.com'),
('substack.rss', 'https://iinkognit0.substack.com/feed'),
('podcast.hub', 'https://pod.link/1862625280'),
('podcast.master_rss', 'https://anchor.fm/s/10d156d24/podcast/rss'),
('rss.earc.canonical', 'https://iinkognit0.de/rss'),
('start.modules', 'header,newsloop,identity,manifest_scroll,links,rss_links'),
('header.brand', 'eArc_only'),
('header.nav.items', 'eArc=https://iinkognit0.de/earc/'),
('newsloop.animation', 'horizontal_infinite_loop'),
('newsloop.source', 'https://iinkognit0.de/rss'),
('manifest.animation', 'vertical_infinite_rise'),
('manifest.content', 'FULL_MANIFEST_TEXT'),
('links.earc', 'https://iinkognit0.de/earc/'),
('links.podcast', 'https://iinkognit0.de/podcast/'),
('links.podlink', 'https://pod.link/1862625280'),
('links.substack', 'https://iinkognit0.substack.com');