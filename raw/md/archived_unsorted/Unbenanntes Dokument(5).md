inkognit0@K501:~/workspace$ find ~ -name "frames.ndjson"

/home/iinkognit0/Desktop/K501GeminiNet_Backup/Pfad-home-iinkognit0-Dokumente-/K501_Vault/archive/frames.ndjson

/home/iinkognit0/Desktop/K501GeminiNet_Backup/Pfad-home-iinkognit0-Dokumente-/K501_Vault_old/archive/frames.ndjson

/home/iinkognit0/Desktop/K501GeminiNet_Backup/Daten/Obsidian/backup/K501_Vault/archive/frames.ndjson

/home/iinkognit0/Desktop/K501GeminiNet_Backup/pfad-Root-/K501GeminiNet/Node01/vault/ledger/frames.ndjson

/home/iinkognit0/Desktop/K501GeminiNet_Backup/Pfad-home-iinkognit0-/K501Gemini/vault/ledger/frames.ndjson

/home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

/home/iinkognit0/k501_ingest_staging/input/K501Gemini_N01_T520/pfad-Root-/K501GeminiNet/Node01/vault/ledger/frames.ndjson

/home/iinkognit0/k501_ingest_staging/input_too_large/frames.ndjson

iinkognit0@K501:~/workspace$ wc -l /PFAD/ZU/frames.ndjson

wc: /PFAD/ZU/frames.ndjson: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:~/workspace$ wc -l /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

161667 /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

iinkognit0@K501:~/workspace$ du -h /home/iinkognit0/workspace/archive/little_alpha_storage/

frames.ndjson

40M /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

iinkognit0@K501:~/workspace$ echo "$(du -b /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson | cut -f1) / $(wc -l < /home/iinkognit0/workspace/archive/little_alph

a_storage/frames.ndjson)" | bc

253

iinkognit0@K501:~/workspace$ /workspace/archive/little_alpha_storage/semantic.ndjson

bash: /workspace/archive/little_alpha_storage/semantic.ndjson: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:~/workspace$ wc -l ~/workspace/archive/little_alpha_storage/semantic.ndjson

308 /home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson

iinkognit0@K501:~/workspace$ du -h ~/workspace/archive/little_alpha_storage/semantic.ndjson

3,1M /home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson

iinkognit0@K501:~/workspace$ echo "scale=4; $(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson) / $(wc -l < /home/iinkognit0/workspace/archive/little_alpha_storage/fr

ames.ndjson) * 100" | bc

.1900

iinkognit0@K501:~/workspace$