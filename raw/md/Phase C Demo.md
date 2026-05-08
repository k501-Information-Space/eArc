python3 phase_c/tools/indexer.py \
  --db phase_c/db/archive_index.sqlite \
  --schema phase_c/db/schema.sql \
  --vault phase_c/sample_vault

python3 phase_c/tools/rss_generator.py \
  --db phase_c/db/archive_index.sqlite \
  --out phase_c/db/feed.xml