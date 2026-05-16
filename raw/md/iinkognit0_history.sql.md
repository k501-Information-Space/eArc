-- Projekt: iInkognit0
-- Zweck: Historische Speicherung (ohne Bedeutung)
-- Initialisiert: YYYY-MM-DD

CREATE TABLE project_snapshots (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  snapshot_date DATE NOT NULL,
  state TEXT,
  mode TEXT,
  vault_reference TEXT,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE platform_stats (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  platform TEXT NOT NULL,
  metric TEXT NOT NULL,
  value INTEGER,
  date_collected DATE NOT NULL,
  vault_reference TEXT,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);