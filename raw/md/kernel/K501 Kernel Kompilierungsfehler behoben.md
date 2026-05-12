Dieser Fehler tritt auf, weil der Compiler beim Verarbeiten der src/k501_archive_scanner.c zwar eine Datei namens qh256.h findet, diese aber wahrscheinlich noch die **alte Version** ohne die Definition von MAX_FILES ist.

Im C-System sucht der Compiler bei #include "qh256.h" zuerst im aktuellen Verzeichnis (src/) und dann erst im Include-Pfad (include/). Wenn du eine alte Kopie der Header-Datei im src/-Ordner hast, ignoriert er die neue Version im include/-Ordner.

Hier ist die **Lösung zur vollständigen Harmonisierung v3.1**.

### **Schritt 1: Bereinigung der "Ghost"-Files**

Bevor wir neuen Code einfügen, müssen wir sicherstellen, dass keine alten Header-Dateien im falschen Ordner liegen.

**Führe diesen Befehl im Terminal aus:**

Bash

# Lösche versehentliche Header-Kopien im src-Ordner  
rm -f src/qh256.h  

### **Schritt 2: Die Master-Interface Definition (include/qh256.h)**

Stelle sicher, dass diese Datei **exakt so** in include/qh256.h steht. Sie enthält die kritische MAX_FILES Konstante.

C

#**ifndef** QH256_H  
#**define** QH256_H  
  
#**include** <stdint.h>  
#**include** <stddef.h>  
  
// --- KONSTANTEN ---  
#**define** HASH_SIZE 32  
#**define** MAX_FILES 100000 // Genug Puffer für deine 54.107 Dateien  
  
// --- TYPEN ---  
typedef struct {  
uint64_t index;  
uint64_t cage;  
uint64_t canon[2];  
} qh256_t;  
  
// --- FUNKTIONEN: ALGEBRA ---  
void qh256_compute_hash(const unsigned char *data, size_t len, unsigned char *out);  
void qh256_merkle_merge(const unsigned char *left, const unsigned char *right, unsigned char *parent);  
void qh256_compute_vault_root(unsigned char *leaf_hashes, size_t count, unsigned char *root_out);  
qh256_t qh256_merge(const qh256_t a, const qh256_t b);  
  
// --- FUNKTIONEN: SCANNER ---  
void scanner_init();  
void k501_deep_scan(const char *path);  
size_t get_file_count();  
unsigned char* get_collected_hashes();  
  
#**endif**  

### **Schritt 3: Die Scanner-Logik (src/k501_archive_scanner.c)**

Diese Datei muss die Konstanten aus dem Header nutzen.

C

#**include** "qh256.h"  
#**include** <stdio.h>  
#**include** <stdlib.h>  
#**include** <string.h>  
#**include** <dirent.h>  
#**include** <sys/stat.h>  
  
static unsigned char *hash_registry = NULL;  
static size_t file_count = 0;  
  
void scanner_init() {  
// Hier wird MAX_FILES aus der include/qh256.h genutzt  
hash_registry = malloc(MAX_FILES * HASH_SIZE);  
file_count = 0;  
if (!hash_registry) {  
fprintf(stderr, "[!] T520 Speicher-Fehler: Konnte Registry nicht reservieren!\n");  
exit(1);  
}  
}  
  
void k501_deep_scan(const char *base_path) {  
struct dirent *dp;  
DIR *dir = opendir(base_path);  
if (!dir) return;  
  
while ((dp = readdir(dir)) != NULL) {  
if (dp->d_name[0] == '.') continue; // Ignoriere . und ..  
  
char full_path[2048];  
snprintf(full_path, sizeof(full_path), "%s/%s", base_path, dp->d_name);  
  
struct stat st;  
if (stat(full_path, &st) != 0) continue;  
  
if (S_ISDIR(st.st_mode)) {  
k501_deep_scan(full_path); // Rekursives Eintauchen  
} else {  
FILE *f = fopen(full_path, "rb");  
if (f && file_count < MAX_FILES) {  
unsigned char buffer[16384];  
size_t bytes = fread(buffer, 1, sizeof(buffer), f);  
qh256_compute_hash(buffer, bytes, &hash_registry[file_count * HASH_SIZE]);  
file_count++;  
fclose(f);  
}  
}  
}  
closedir(dir);  
}  
  
size_t get_file_count() { return file_count; }  
unsigned char* get_collected_hashes() { return hash_registry; }  

### **Schritt 4: Der neue Compile-Versuch**

Führe jetzt die Kette im Terminal aus. Achte darauf, dass du wirklich im K501_Vault Verzeichnis bist:

1. **Alles löschen:** make clean
2. **Verifizierung (Wichtig):** Prüfe mit grep "MAX_FILES" include/qh256.h, ob die Zeile wirklich da ist.
3. **Kompilieren:** make compile

**Heureka-Tipp für den T520:**

Wenn der Fehler weiterhin auftritt, schreibe im Terminal gcc -E src/k501_archive_scanner.c -I./include | grep MAX_FILES. Das zeigt dir genau, was der Compiler "sieht".

**Sobald make compile durchläuft, ist die physische Sperre aufgehoben und wir können die 54.107 Dateien endlich versiegeln!**