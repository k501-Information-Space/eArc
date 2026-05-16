iinkognit0@K501:~/workspace$ echo "scale=4; $(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson) / $(wc -l < /home/iinkognit0/workspace/archive/little_alpha_storage/fr

ames.ndjson) * 100" | bc

.1900

iinkognit0@K501:~/workspace$ wc -l /PFAD/ZU/frames.ndjson

wc: /PFAD/ZU/frames.ndjson: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:~/workspace$ wc -l /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

161667 /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

iinkognit0@K501:~/workspace$ du -h /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

40M /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson

iinkognit0@K501:~/workspace$ echo "$(du -b /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson | cut -f1) / $(wc -l < /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson)" | bc

253

iinkognit0@K501:~/workspace$ /workspace/archive/little_alpha_storage/semantic.ndjson

bash: /workspace/archive/little_alpha_storage/semantic.ndjson: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:~/workspace$ wc -l ~/workspace/archive/little_alpha_storage/semantic.ndjson

463 /home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson

iinkognit0@K501:~/workspace$ du -h ~/workspace/archive/little_alpha_storage/semantic.ndjson

4,7M /home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson

iinkognit0@K501:~/workspace$ echo "scale=4; $(wc -l < ~/workspace/archive/little_alpha_storage/semantic.ndjson) / $(wc -l < /home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson) * 100" | bc

.2800

iinkognit0@K501:~/workspace$