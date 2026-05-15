Dann jetzt sauber mit einem echten 5GB-Batch anfangen.

Erst Batch-Verzeichnis erzeugen:

```bash
mkdir -p ~/workspace/batches/Batch_0001
```

Dann prüfen, welche großen Bereiche im RAW existieren:

```bash
du -sh ~/workspace/k501_ingest/raw_dump/* | sort -h
```

Dann gezielt ungefähr 5GB auswählen und kopieren:

Beispiel:

```bash
cp -r ~/workspace/k501_ingest/raw_dump/K501_Information_Space_DEV \
~/workspace/batches/Batch_0001/
```

Danach Größe prüfen:

```bash
du -sh ~/workspace/batches/Batch_0001
```

Wenn zu groß:

- Unterordner reduzieren
    

Wenn kleiner als 5GB:

- weitere Unterordner ergänzen
    

Dann Manifest erzeugen:

```bash
find ~/workspace/batches/Batch_0001 -type f \
> ~/workspace/batches/Batch_0001_manifest.txt
```

Dann Hashliste:

```bash
find ~/workspace/batches/Batch_0001 -type f -exec sha256sum {} \; \
> ~/workspace/batches/Batch_0001_sha256.txt
```

Dann optional komprimieren:

```bash
tar -czf ~/workspace/Batch_0001.tar.gz \
-C ~/workspace/batches Batch_0001
```

Danach:

```bash
du -sh ~/workspace/Batch_0001.tar.gz
```

Das wäre dann dein erster kontrollierter transportabler Archivbatch.