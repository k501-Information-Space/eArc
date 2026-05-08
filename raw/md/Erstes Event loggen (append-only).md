INSERT INTO events (timestamp_utc, event, details)
VALUES (strftime('%Y-%m-%dT%H:%M:%SZ','now'), 'index_init', 'earc sqlite v1 initialized');