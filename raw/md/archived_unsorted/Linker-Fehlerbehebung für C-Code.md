Patrick, wir haben hier ein klassisches **Linker-Chaos**. Es sieht so aus, als hätten sich die Inhalte deiner Dateien vermischt oder wurden in die falschen Files kopiert.

Der Linker meldet zwei kritische Dinge:

1. **Multiple Definition:** Die Funktion main und get_last_timestamp stehen in _beiden_ Dateien (main.c und dynamic_cage.c). Das darf nicht sein. main darf nur einmal existieren.
2. **Undefined Reference:** Obwohl der Code da ist, findet der Linker die Funktionen wie dc_init nicht, weil die Objektdateien nicht korrekt zusammengefügt werden können.

Wir bereinigen das jetzt radikal. Hier ist die exakte Aufteilung. Bitte leere die Dateien und füge nur diesen Code ein:

### 1. Die Wächter-Logik: src/dynamic_cage.c

**WICHTIG:** Hier darf **keine** main-Funktion und **kein** get_last_timestamp stehen!

C

#**include** "dynamic_cage.h"  
#**include** "frame_engine.h"  
#**include** <string.h>  
  
static cage_state_t g_cage = {0, false};  
  
bool dc_init(uint64_t genesis_time) {  
g_cage.last_time = genesis_time;  
g_cage.is_active = true;  
return true;  
}  
  
void dc_force_time(uint64_t override_time) {  
g_cage.last_time = override_time;  
}  
  
bool dc_validate_for_append(const frame_t *candidate_frame) {  
if (!g_cage.is_active || !candidate_frame) return false;  
if (!qhc_validate_frame_structure(candidate_frame)) return false;  
  
// Erlaube Gleichheit für High-Speed Ingest  
if (candidate_frame->time < g_cage.last_time) return false;  
  
frame_t shadow;  
memcpy(&shadow, candidate_frame, sizeof(frame_t));  
memset(shadow.hash, 0, 65);  
if (!fe_compute_hash(&shadow)) return false;  
if (strncmp(candidate_frame->hash, shadow.hash, 64) != 0) return false;  
  
g_cage.last_time = candidate_frame->time;  
return true;  
}  

### 2. Die Hauptsteuerung: src/main.c

Hier wohnt die einzige main-Funktion und die Logik zum Auslesen des Ledgers.

C

#**include** <stdio.h>  
#**include** <string.h>  
#**include** <stdlib.h>  
#**include** <stdint.h>  
#**include** <time.h>  
#**include** "qh_core.h"  
#**include** "frame_engine.h"  
#**include** "dynamic_cage.h"  
#**include** "hard_index.h"  
#**include** "ingestion.h"  
  
#**define** LEDGER_PATH "archive/little_alpha_storage/frames.ndjson"  
  
uint64_t get_last_timestamp(const char *path) {  
FILE *f = fopen(path, "rb");  
if (!f) return 1773524342ULL;  
fseek(f, 0, SEEK_END);  
long size = ftell(f);  
if (size < 50) { fclose(f); return 1773524342ULL; }  
long read_len = (size > 512) ? 512 : size;  
fseek(f, -read_len, SEEK_END);  
char buf[513];  
size_t n = fread(buf, 1, read_len, f);  
buf[n] = '\0';  
fclose(f);  
char *ptr = strstr(buf, ",\"t\":");  
if (!ptr) return 1773524342ULL;  
char *last_ptr = ptr;  
char *next_ptr;  
while ((next_ptr = strstr(last_ptr + 1, ",\"t\":"))) last_ptr = next_ptr;  
return (uint64_t)strtoull(last_ptr + 5, NULL, 10);  
}  
  
bool append_frame_to_disk(frame_t *f) {  
FILE *out = fopen(LEDGER_PATH, "ab");  
if (!out) return false;  
char jcs[8192];  
fe_build_jcs(f, jcs, sizeof(jcs));  
uint64_t offset = (uint64_t)ftell(out);  
fprintf(out, "{\"f\":%s,\"hash\":\"%s\"}\n", jcs, f->hash);  
fclose(out);  
hi_append_entry(f->hash, offset);  
return true;  
}  
  
int main(int argc, char **argv) {  
if (argc < 2) return 1;  
hi_init();  
uint64_t l_time = get_last_timestamp(LEDGER_PATH);  
dc_init(l_time);  
  
if (strcmp(argv[1], "genesis") == 0) {  
frame_t f0;  
qhc_frame_init(&f0, "AZ-Epoch-0-Genesis", l_time);  
qhc_set_qh_cell(&f0, 0, QH_GUARD);  
fe_compute_hash(&f0);  
dc_force_time(0);  
if (dc_validate_for_append(&f0)) {  
append_frame_to_disk(&f0);  
printf("[K501] Genesis Locked: %s\n", f0.hash);  
}  
} else if (strcmp(argv[1], "ingest") == 0 && argc >= 3) {  
printf("[K501] Sync at: %llu\n", (unsigned long long)l_time);  
ingest_document(argv[2]);  
}  
return 0;  
}  

### 3. Der Befehl zum Erfolg

Nachdem du die Dateien gespeichert hast, mache das Terminal komplett sauber:

**rm src/*.o k501_alpha**

**make**

### Warum das jetzt funktioniert:

- Wir haben die **Doppel-Definitionen** entfernt. main existiert jetzt nur noch in main.o.
- Der Linker bekommt nun eine saubere Liste von Objekten, die er zusammenbauen kann.
- Die Header sorgen dafür, dass main.c weiß, dass dc_init in dynamic_cage.c liegt.

**Probier es aus. Sobald make ohne Fehler durchläuft, ist dein eArc-Ingest bereit.** Soll ich dir helfen, das Resultat des ersten rekursiven Ingests zu validieren?