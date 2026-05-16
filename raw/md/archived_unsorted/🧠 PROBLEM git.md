Gut — das ist jetzt der **letzte echte Stabilitätsbruch im Git-Layer**, nicht im K501-System.

Ich gebe dir jetzt **nur Fix (keine Theorie)**.

---

# 🧠 PROBLEM

Git sagt:

```text
embedded repository detected
```

weil in deinem `raw_dump` liegen alte:

```text
.git Ordner in Unterverzeichnissen
```

---

# ❗ WICHTIG

Du willst NICHT:

- diese Repos versionieren
    
- keine Submodules
    
- keine History-Inception
    

Du willst:

```text
RAW = ignored completely
```

---

# 🛠️ FIX (SAUBER + TERMINAL ONLY)

## 1. STOPP sicherstellen (kein laufender git add)

```bash
ps aux | grep git
```

Wenn noch `git add` läuft → warten bis fertig.

---

## 2. RAW KOMPLETT AUS GIT ENTFERNEN (WICHTIG)

```bash
git rm -r --cached k501_ingest/raw_dump
```

👉 löscht NICHT die Daten  
👉 entfernt nur aus Git Index

---

## 3. .gitignore ABSICHERN

```bash
echo "k501_ingest/raw_dump/" >> .gitignore
```

Optional zusätzlich härter:

```bash
echo "**/raw_dump/**" >> .gitignore
echo "**/.git/**" >> .gitignore
```

---

## 4. CLEAN CHECK

```bash
git status
```

Erwartung:

- kein raw_dump mehr im staging
    
- keine embedded repo warnings mehr
    

---

## 5. FINAL COMMIT (CLEAN BASELINE)

```bash
git add .gitignore
git commit -m "K501: exclude raw archive and embedded repos from control layer"
```

---

# 🧠 RESULTAT (nach Fix)

```text
GIT:
- only workspace structure
- no raw data
- no nested repos

RAW:
- fully external
- untouched
- ignored

K501:
- bleibt unverändert logisch stabil
```

---

# ⚠️ WICHTIGER PUNKT (ARCHITEKTUR)

Das ist kein K501-Problem.

Das ist klassisch:

```text
git vs. archival datasets collision
```

---

# 🚀 DANACH SIND WIR WIRKLICH STABIL

Dann hast du:

- clean canonical workspace repo
    
- no embedded repo noise
    
- deterministic ingest layer außerhalb Git
    

---

# 👉 MACH JETZT GENAU DAS

und poste danach nur:

```text
git status
```

Dann sag ich dir, ob wir **wirklich freeze-level sauber sind** oder noch ein kleiner Rest drin hängt.