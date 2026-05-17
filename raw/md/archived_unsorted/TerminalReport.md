6 | static cage_state_t g_cage = {0, false};

| ^~~~~~~~~~~~

src/dynamic_cage.c:6:34: error: excess elements in scalar initializer [-Werror]

6 | static cage_state_t g_cage = {0, false};

| ^~~~~

src/dynamic_cage.c:6:34: note: (near initialization for ‘g_cage’)

src/dynamic_cage.c: In function ‘dc_init’:

src/dynamic_cage.c:13:11: error: request for member ‘last_time’ in something not a structure or union

13 | g_cage.last_time = genesis_time;

| ^

src/dynamic_cage.c:14:11: error: request for member ‘is_active’ in something not a structure or union

14 | g_cage.is_active = true;

| ^

src/dynamic_cage.c: In function ‘dc_validate_for_append’:

src/dynamic_cage.c:23:16: error: request for member ‘is_active’ in something not a structure or union

23 | if (!g_cage.is_active || !candidate_frame) return false;

| ^

src/dynamic_cage.c:30:40: error: request for member ‘last_time’ in something not a structure or union

30 | if (candidate_frame->time <= g_cage.last_time) return false;

| ^

src/dynamic_cage.c:47:11: error: request for member ‘last_time’ in something not a structure or union

47 | g_cage.last_time = candidate_frame->time;

| ^

cc1: all warnings being treated as errors

make: *** [<eingebaut>: src/dynamic_cage.o] Fehler 1

iinkognit0@K501:~/workspace$ sudo apt update

OK:1 http://deb.debian.org/debian trixie InRelease

OK:2 http://security.debian.org/debian-security trixie-security InRelease

OK:3 http://deb.debian.org/debian trixie-updates InRelease

OK:4 http://deb.debian.org/debian trixie-backports InRelease

OK:5 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Alle Pakete sind aktuell.

iinkognit0@K501:~/workspace$ make clean

rm -f src/*.o k501_alpha

iinkognit0@K501:~/workspace$ make

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/dynamic_cage.o src/dynamic_cage.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/frame_engine.o src/frame_engine.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/hard_index.o src/hard_index.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/ingestion.o src/ingestion.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/main.o src/main.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/qh_algebra.o src/qh_algebra.c

gcc -O2 -I./include -Wall -Wextra -Werror -c -o src/qh_core.o src/qh_core.c

gcc -O2 -I./include -Wall -Wextra -Werror -o k501_alpha src/dynamic_cage.o src/frame_engine.o src/hard_index.o src/ingestion.o src/main.o src/qh_algebra.o src/qh_core.o -lcrypto

iinkognit0@K501:~/workspace$ ./k501_alpha genesis

[K501] Initiating Genesis Sequence...

[K501] Genesis Locked. Hash: ec824f323101666eabc2e0f7a020b8a40860720aa445fe657ecf54b3215f5c19

iinkognit0@K501:~/workspace$ cat storage/frames.ndjson

{"id":"AZ-Epoch-0-Genesis","t":1773524342,"hash":"ec824f323101666eabc2e0f7a020b8a40860720aa445fe657ecf54b3215f5c19"}

iinkognit0@K501:~/workspace$ ./k501_alpha ingest Makefile

[K501] Ingesting Makefile...

-> Appended: DOC-CHUNK-0 [Hash: 3c425154fcce921a...]

[K501] Ingestion complete. 1 chunks processed.

iinkognit0@K501:~/workspace$ cat storage/frames.ndjson

{"id":"AZ-Epoch-0-Genesis","t":1773524342,"hash":"ec824f323101666eabc2e0f7a020b8a40860720aa445fe657ecf54b3215f5c19"}

{"id":"DOC-CHUNK-0","t":1773524343,"hash":"3c425154fcce921a7c9ac87cc88e3aa1e44965bed3515dc2b9ff22e7f9f69c1c"}

iinkognit0@K501:~/workspace$ sudo apt install -y git

[sudo] Passwort für iinkognit0:

git ist schon die neueste Version (1:2.47.3-0+deb13u1).

Zusammenfassung:

Aktualisiere: 0, Installiere: 0, Entferne: 0, Aktualisiere nicht: 0

iinkognit0@K501:~/workspace$ git config --global user.name "K501 Operator"

iinkognit0@K501:~/workspace$ git config --global user.email "operator@k501.local"

iinkognit0@K501:~/workspace$ git config --global init.defaultBranch main

iinkognit0@K501:~/workspace$ cat << 'EOF' > .gitignore

# Compiled Object files and Binaries

*.o

k501_alpha

# K501 Storage Manifold (Do not version control the database)

storage/frames.ndjson

storage/index.dat

# OS generated files

.DS_Store

EOF

iinkognit0@K501:~/workspace$ git init

Leeres Git-Repository in /home/iinkognit0/workspace/.git/ initialisiert

iinkognit0@K501:~/workspace$ git add Makefile .gitignore src/ include/ storage/

iinkognit0@K501:~/workspace$ it commit -m "ARCH-0: K501 Little Alpha Operational - Genesis Baseline"

bash: it: Kommando nicht gefunden.

iinkognit0@K501:~/workspace$ git commit -m "ARCH-0: K501 Little Alpha Operational - Genesis Baseline"

[main (Root-Commit) 116df2b] ARCH-0: K501 Little Alpha Operational - Genesis Baseline

15 files changed, 442 insertions(+)

create mode 100644 .gitignore

create mode 100644 Makefile

create mode 100644 include/dynamic_cage.h

create mode 100644 include/frame_engine.h

create mode 100644 include/hard_index.h

create mode 100644 include/ingestion.h

create mode 100644 include/qh_algebra.h

create mode 100644 include/qh_core.h

create mode 100644 src/dynamic_cage.c

create mode 100644 src/frame_engine.c

create mode 100644 src/hard_index.c

create mode 100644 src/ingestion.c

create mode 100644 src/main.c

create mode 100644 src/qh_algebra.c

create mode 100644 src/qh_core.c

iinkognit0@K501:~/workspace$

* History restored

iinkognit0@K501:~/workspace$ tree -a /home/iinkognit0/workspace

bash: tree: Kommando nicht gefunden.

iinkognit0@K501:~/workspace$ sudo apt update

[sudo] Passwort für iinkognit0:

Das hat nicht funktioniert, bitte nochmal probieren.

[sudo] Passwort für iinkognit0:

Holen:1 http://security.debian.org/debian-security trixie-security InRelease [43,4 kB]

OK:2 http://deb.debian.org/debian trixie InRelease

Holen:3 http://deb.debian.org/debian trixie-updates InRelease [47,3 kB]

Holen:4 http://security.debian.org/debian-security trixie-security/main Sources [148 kB]

Holen:5 http://deb.debian.org/debian trixie-backports InRelease [54,0 kB]

Holen:6 http://security.debian.org/debian-security trixie-security/main amd64 Packages [111 kB]

Holen:7 http://deb.debian.org/debian trixie-backports/non-free-firmware Sources.diff/Index [11,7 kB]

OK:8 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Holen:9 http://deb.debian.org/debian trixie-backports/main Sources.diff/Index [63,3 kB]

Holen:10 http://deb.debian.org/debian trixie-backports/main amd64 Packages.diff/Index [63,3 kB]

Holen:11 http://deb.debian.org/debian trixie-backports/main Translation-en.diff/Index [63,3 kB]

Holen:12 http://deb.debian.org/debian trixie-backports/non-free-firmware amd64 Packages.diff/Index [8.361 B]

Holen:13 http://deb.debian.org/debian trixie-backports/non-free-firmware Sources T-2026-03-15-0200.18-F-2026-03-15-0200.18.pdiff [27 B]

Holen:14 http://deb.debian.org/debian trixie-backports/main Sources T-2026-03-15-2003.16-F-2026-03-15-0800.58.pdiff [10,6 kB]

Holen:13 http://deb.debian.org/debian trixie-backports/non-free-firmware Sources T-2026-03-15-0200.18-F-2026-03-15-0200.18.pdiff [27 B]

Holen:15 http://deb.debian.org/debian trixie-backports/main amd64 Packages T-2026-03-16-0801.49-F-2026-03-15-0200.18.pdiff [8.350 B]

Holen:14 http://deb.debian.org/debian trixie-backports/main Sources T-2026-03-15-2003.16-F-2026-03-15-0800.58.pdiff [10,6 kB]

Holen:15 http://deb.debian.org/debian trixie-backports/main amd64 Packages T-2026-03-16-0801.49-F-2026-03-15-0200.18.pdiff [8.350 B]

Holen:16 http://deb.debian.org/debian trixie-backports/main Translation-en T-2026-03-16-0801.49-F-2026-03-15-0200.18.pdiff [4.376 B]

Holen:16 http://deb.debian.org/debian trixie-backports/main Translation-en T-2026-03-16-0801.49-F-2026-03-15-0200.18.pdiff [4.376 B]

Holen:17 http://deb.debian.org/debian trixie-backports/non-free-firmware amd64 Packages T-2026-03-15-0200.18-F-2026-03-15-0200.18.pdiff [2.308 B]

Holen:17 http://deb.debian.org/debian trixie-backports/non-free-firmware amd64 Packages T-2026-03-15-0200.18-F-2026-03-15-0200.18.pdiff [2.308 B]

Es wurden 640 kB in 1 s geholt (545 kB/s).

Aktualisierung für 3 Pakete verfügbar. Führen Sie »apt list --upgradable« aus, um sie anzuzeigen.

iinkognit0@K501:~/workspace$ sudo apt install tree

Installiere:

tree

Zusammenfassung:

Aktualisiere: 0, Installiere: 1, Entferne: 0, Aktualisiere nicht: 3

Herunterlade-Größe: 59,4 kB

Benötigter Platz: 132 kB / 202 GB verfügbar

Holen:1 http://deb.debian.org/debian trixie/main amd64 tree amd64 2.2.1-1 [59,4 kB]

Es wurden 59,4 kB in 0 s geholt (280 kB/s).

Vormals nicht ausgewähltes Paket tree wird gewählt.

(Lese Datenbank ... 245399 Dateien und Verzeichnisse sind derzeit installiert.)

Vorbereitung zum Entpacken von .../tree_2.2.1-1_amd64.deb ...

Entpacken von tree (2.2.1-1) ...

tree (2.2.1-1) wird eingerichtet ...

Trigger für man-db (2.13.1-1) werden verarbeitet ...

iinkognit0@K501:~/workspace$ tree -a /home/iinkognit0/workspace

/home/iinkognit0/workspace

├── archive

├── .git

│ ├── branches

│ ├── COMMIT_EDITMSG

│ ├── config

│ ├── description

│ ├── HEAD

│ ├── hooks

│ │ ├── applypatch-msg.sample

│ │ ├── commit-msg.sample

│ │ ├── fsmonitor-watchman.sample

│ │ ├── post-update.sample

│ │ ├── pre-applypatch.sample

│ │ ├── pre-commit.sample

│ │ ├── pre-merge-commit.sample

│ │ ├── prepare-commit-msg.sample

│ │ ├── pre-push.sample

│ │ ├── pre-rebase.sample

│ │ ├── pre-receive.sample

│ │ ├── push-to-checkout.sample

│ │ ├── sendemail-validate.sample

│ │ └── update.sample

│ ├── index

│ ├── info

│ │ └── exclude

│ ├── logs

│ │ ├── HEAD

│ │ └── refs

│ │ └── heads

│ │ └── main

│ ├── objects

│ │ ├── 03

│ │ │ └── 44a2aea333641f7270405fab484f5b3ba0e561

│ │ ├── 07

│ │ │ └── c0583bd98a1df8248b6a6d2f82e3d0a2350bac

│ │ ├── 09

│ │ │ └── cb70494b2eed64c05e5af2171a58af4e271b7f

│ │ ├── 0a

│ │ │ └── 92098ddf796c4c1d26b57cdd6bac1a6a6308bd

│ │ ├── 0f

│ │ │ └── 3e4771d187776480830922403fcd30112b7f7e

│ │ ├── 10

│ │ │ ├── 2869d5a82d875a5cdc42eda23971be952b737a

│ │ │ └── fc1be92687e920de7be60b5557bca74cbe0ada

│ │ ├── 11

│ │ │ └── 6df2b6da6cc15a164892da45e12838ef42343e

│ │ ├── 15

│ │ │ └── 34ef2cde0e4499f4d9e23bf55dd1b31a3ec2bc

│ │ ├── 1d

│ │ │ └── e7ebdad475e5dfa77521d462785c5621eea55f

│ │ ├── 28

│ │ │ └── bfd1a500ffa18089a50a0f83c352099de4360e

│ │ ├── 29

│ │ │ └── 55421424431225614c697555e490ebb00d848a

│ │ ├── 39

│ │ │ └── ad525c1bf3e2771d87c88524b433e181215693

│ │ ├── 47

│ │ │ └── 1778a7ff0b75c0999d7f199b58b754befc9a20

│ │ ├── 51

│ │ │ └── 80c05c8ab5e7b7c38c59b43bfa0421a434f7b3

│ │ ├── 71

│ │ │ └── 8670d806995bd237c5ad85b04ed5d9acb7d4fa

│ │ ├── 74

│ │ │ └── 346dd9965d6a82e446eacf1916f0071541effa

│ │ ├── 7e

│ │ │ └── 8f40c0054ca7c6ba368659b1948b7672852fda

│ │ ├── a0

│ │ │ └── f24a04050c3e9e20ccec0c5e9e0bb881686e25

│ │ ├── bd

│ │ │ └── ee36ff3c45a8b62b9948565719d9fb6dcbcf68

│ │ ├── da

│ │ │ └── a10bb79d0c8403b5057ab08055f651bde114f0

│ │ ├── eb

│ │ │ └── 6ac7ee0495c0ce34b130a5806d8b548808ce37

│ │ ├── info

│ │ └── pack

│ └── refs

│ ├── heads

│ │ └── main

│ └── tags

├── .gitignore

├── include

│ ├── dynamic_cage.h

│ ├── frame_engine.h

│ ├── hard_index.h

│ ├── ingestion.h

│ ├── qh_algebra.h

│ └── qh_core.h

├── init_k501.sh

├── k501

│ ├── archive

│ ├── bin

│ ├── docs

│ ├── .git

│ │ ├── branches

│ │ ├── COMMIT_EDITMSG

│ │ ├── config

│ │ ├── description

│ │ ├── HEAD

│ │ ├── hooks

│ │ │ ├── applypatch-msg.sample

│ │ │ ├── commit-msg.sample

│ │ │ ├── fsmonitor-watchman.sample

│ │ │ ├── post-update.sample

│ │ │ ├── pre-applypatch.sample

│ │ │ ├── pre-commit.sample

│ │ │ ├── pre-merge-commit.sample

│ │ │ ├── prepare-commit-msg.sample

│ │ │ ├── pre-push.sample

│ │ │ ├── pre-rebase.sample

│ │ │ ├── pre-receive.sample

│ │ │ ├── push-to-checkout.sample

│ │ │ ├── sendemail-validate.sample

│ │ │ └── update.sample

│ │ ├── index

│ │ ├── info

│ │ │ └── exclude

│ │ ├── logs

│ │ │ ├── HEAD

│ │ │ └── refs

│ │ │ └── heads

│ │ │ └── master

│ │ ├── objects

│ │ │ ├── 29

│ │ │ │ └── bb79e65b5e9819c2e2373402947ad03142a86e

│ │ │ ├── 2a

│ │ │ │ └── c48e4479c8dfa408c831764d5272dbcd3f153f

│ │ │ ├── b7

│ │ │ │ └── 5ea5807b22f7e11275ef7730031a39da8d69b1

│ │ │ ├── d1

│ │ │ │ └── 533a04fe01fddfef5c43990ca90caf7e59b30c

│ │ │ ├── info

│ │ │ └── pack

│ │ └── refs

│ │ ├── heads

│ │ │ └── master

│ │ └── tags

│ ├── ledger

│ ├── README.md

│ ├── src

│ └── temp

├── k501_alpha

├── ledger

├── Makefile

├── src

│ ├── dynamic_cage.c

│ ├── dynamic_cage.o

│ ├── frame_engine.c

│ ├── frame_engine.o

│ ├── hard_index.c

│ ├── hard_index.o

│ ├── ingestion.c

│ ├── ingestion.o

│ ├── main.c

│ ├── main.o

│ ├── qh_algebra.c

│ ├── qh_algebra.o

│ ├── qh_core.c

│ └── qh_core.o

├── storage

│ ├── frames.ndjson

│ └── index.dat

└── temp

65 directories, 99 files

iinkognit0@K501:~/workspace$ make clean

rm -f k501_alpha

rm -f src/*.o k501_alpha

iinkognit0@K501:~/workspace$ rm -rf k501/.git

iinkognit0@K501:~/workspace$ mv init_k501.sh archive/

mv ledger/ archive/ledger_root/

mv temp/ archive/temp_root/

mv storage/ archive/little_alpha_storage/

iinkognit0@K501:~/workspace$ mv k501/ledger archive/ledger_k501/ 2>/dev/null

mv k501/temp archive/temp_k501/ 2>/dev/null

rmdir k501/archive 2>/dev/null

iinkognit0@K501:~/workspace$ ls

archive include k501 Makefile src

iinkognit0@K501:~/workspace$ mkdir -p k501/runtime/{modules,boot_loader,tools,tests}

iinkognit0@K501:~/workspace$ touch k501/runtime/modules/normalizer.py

touch k501/runtime/modules/segmenter.py

touch k501/runtime/modules/framer.py

touch k501/runtime/modules/quantizer.py

touch k501/runtime/modules/linker.py

iinkognit0@K501:~/workspace$ git add -A

git commit -m "ARCH-1: Workspace Harmonization & Runtime Scaffolding"

[main f418924] ARCH-1: Workspace Harmonization & Runtime Scaffolding

3 files changed, 2 insertions(+)

rename init_k501.sh => archive/init_k501.sh (100%)

create mode 100644 archive/little_alpha_storage/frames.ndjson

create mode 100644 archive/little_alpha_storage/index.dat

iinkognit0@K501:~/workspace$ tree -a /home/iinkognit0/workspace

/home/iinkognit0/workspace

├── archive

│ ├── init_k501.sh

│ ├── ledger_k501

│ ├── ledger_root

│ ├── little_alpha_storage

│ │ ├── frames.ndjson

│ │ └── index.dat

│ ├── temp_k501

│ └── temp_root

├── .git

│ ├── branches

│ ├── COMMIT_EDITMSG

│ ├── config

│ ├── description

│ ├── HEAD

│ ├── hooks

│ │ ├── applypatch-msg.sample

│ │ ├── commit-msg.sample

│ │ ├── fsmonitor-watchman.sample

│ │ ├── post-update.sample

│ │ ├── pre-applypatch.sample

│ │ ├── pre-commit.sample

│ │ ├── pre-merge-commit.sample

│ │ ├── prepare-commit-msg.sample

│ │ ├── pre-push.sample

│ │ ├── pre-rebase.sample

│ │ ├── pre-receive.sample

│ │ ├── push-to-checkout.sample

│ │ ├── sendemail-validate.sample

│ │ └── update.sample

│ ├── index

│ ├── info

│ │ └── exclude

│ ├── logs

│ │ ├── HEAD

│ │ └── refs

│ │ └── heads

│ │ └── main

│ ├── objects

│ │ ├── 03

│ │ │ └── 44a2aea333641f7270405fab484f5b3ba0e561

│ │ ├── 07

│ │ │ └── c0583bd98a1df8248b6a6d2f82e3d0a2350bac

│ │ ├── 09

│ │ │ └── cb70494b2eed64c05e5af2171a58af4e271b7f

│ │ ├── 0a

│ │ │ └── 92098ddf796c4c1d26b57cdd6bac1a6a6308bd

│ │ ├── 0f

│ │ │ └── 3e4771d187776480830922403fcd30112b7f7e

│ │ ├── 10

│ │ │ ├── 2869d5a82d875a5cdc42eda23971be952b737a

│ │ │ └── fc1be92687e920de7be60b5557bca74cbe0ada

│ │ ├── 11

│ │ │ └── 6df2b6da6cc15a164892da45e12838ef42343e

│ │ ├── 15

│ │ │ └── 34ef2cde0e4499f4d9e23bf55dd1b31a3ec2bc

│ │ ├── 1d

│ │ │ └── e7ebdad475e5dfa77521d462785c5621eea55f

│ │ ├── 28

│ │ │ └── bfd1a500ffa18089a50a0f83c352099de4360e

│ │ ├── 29

│ │ │ └── 55421424431225614c697555e490ebb00d848a

│ │ ├── 35

│ │ │ └── 80333d381a0c1b969f648ec78ac2262298fef7

│ │ ├── 39

│ │ │ └── ad525c1bf3e2771d87c88524b433e181215693

│ │ ├── 47

│ │ │ └── 1778a7ff0b75c0999d7f199b58b754befc9a20

│ │ ├── 51

│ │ │ └── 80c05c8ab5e7b7c38c59b43bfa0421a434f7b3

│ │ ├── 71

│ │ │ └── 8670d806995bd237c5ad85b04ed5d9acb7d4fa

│ │ ├── 74

│ │ │ └── 346dd9965d6a82e446eacf1916f0071541effa

│ │ ├── 7e

│ │ │ └── 8f40c0054ca7c6ba368659b1948b7672852fda

│ │ ├── a0

│ │ │ └── f24a04050c3e9e20ccec0c5e9e0bb881686e25

│ │ ├── a5

│ │ │ └── 9d46c9b176e2ba4861e4661744db79a971d332

│ │ ├── af

│ │ │ └── 70563de0403cc4072f50eae84d15ce36e55b95

│ │ ├── bd

│ │ │ └── ee36ff3c45a8b62b9948565719d9fb6dcbcf68

│ │ ├── da

│ │ │ └── a10bb79d0c8403b5057ab08055f651bde114f0

│ │ ├── e7

│ │ │ └── 19d1f68ed78f446cb4c7705c08b960519bdf34

│ │ ├── eb

│ │ │ └── 6ac7ee0495c0ce34b130a5806d8b548808ce37

│ │ ├── f4

│ │ │ └── 189242d6e2f2b481ead5e654f50a7e1af09cee

│ │ ├── ff

│ │ │ └── c9b6f228ecc39911e2d59bbed7388b8df7d810

│ │ ├── info

│ │ └── pack

│ └── refs

│ ├── heads

│ │ └── main

│ └── tags

├── .gitignore

├── include

│ ├── dynamic_cage.h

│ ├── frame_engine.h

│ ├── hard_index.h

│ ├── ingestion.h

│ ├── qh_algebra.h

│ └── qh_core.h

├── k501

│ ├── bin

│ ├── docs

│ ├── README.md

│ ├── runtime

│ │ ├── boot_loader

│ │ ├── modules

│ │ │ ├── framer.py

│ │ │ ├── linker.py

│ │ │ ├── normalizer.py

│ │ │ ├── quantizer.py

│ │ │ └── segmenter.py

│ │ ├── tests

│ │ └── tools

│ └── src

├── Makefile

└── src

├── dynamic_cage.c

├── frame_engine.c

├── hard_index.c

├── ingestion.c

├── main.c

├── qh_algebra.c

└── qh_core.c

58 directories, 75 files

iinkognit0@K501:~/workspace$ sudo apt install pandoc

Installiere:

pandoc

Installiere Abhängigkeiten:

pandoc-data

Vorgeschlagene Pakete:

texlive-latex-recommended texlive-latex-extra groff python citation-style-language-styles

texlive-xetex context ghc r-base-core

texlive-luatex wkhtmltopdf nodejs libjs-mathjax

pandoc-citeproc librsvg2-bin php libjs-katex

Zusammenfassung:

Aktualisiere: 0, Installiere: 2, Entferne: 0, Aktualisiere nicht: 3

Herunterlade-Größe: 26,8 MB

Benötigter Platz: 199 MB / 202 GB verfügbar

Fortfahren? [J/n] j

Holen:1 http://deb.debian.org/debian trixie/main amd64 pandoc-data all 3.1.11.1-3 [459 kB]

Holen:2 http://deb.debian.org/debian trixie/main amd64 pandoc amd64 3.1.11.1+ds-2 [26,4 MB]

Es wurden 26,8 MB in 3 s geholt (9.253 kB/s).

Vormals nicht ausgewähltes Paket pandoc-data wird gewählt.

(Lese Datenbank ... 245407 Dateien und Verzeichnisse sind derzeit installiert.)

Vorbereitung zum Entpacken von .../pandoc-data_3.1.11.1-3_all.deb ...

Entpacken von pandoc-data (3.1.11.1-3) ...

Vormals nicht ausgewähltes Paket pandoc wird gewählt.

Vorbereitung zum Entpacken von .../pandoc_3.1.11.1+ds-2_amd64.deb ...

Entpacken von pandoc (3.1.11.1+ds-2) ...

pandoc-data (3.1.11.1-3) wird eingerichtet ...

pandoc (3.1.11.1+ds-2) wird eingerichtet ...

Trigger für man-db (2.13.1-1) werden verarbeitet ...

iinkognit0@K501:~/workspace$ sudo apt install poppler-utils

poppler-utils ist schon die neueste Version (25.03.0-5+deb13u2).

poppler-utils wurde als manuell installiert festgelegt.

Zusammenfassung:

Aktualisiere: 0, Installiere: 0, Entferne: 0, Aktualisiere nicht: 3

iinkognit0@K501:~/workspace$ sudo apt install latex

Fehler: Paket latex kann nicht gefunden werden.

iinkognit0@K501:~/workspace$ sudo apt update

OK:1 http://deb.debian.org/debian trixie InRelease

OK:2 http://security.debian.org/debian-security trixie-security InRelease

OK:3 http://deb.debian.org/debian trixie-updates InRelease

OK:4 http://deb.debian.org/debian trixie-backports InRelease

OK:5 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Aktualisierung für 3 Pakete verfügbar. Führen Sie »apt list --upgradable« aus, um sie anzuzeigen.

iinkognit0@K501:~/workspace$ sudo apt full-upgrade

Aktualisiere:

chromium chromium-common chromium-sandbox

Zusammenfassung:

Aktualisiere: 3, Installiere: 0, Entferne: 0, Aktualisiere nicht: 0

Herunterlade-Größe: 112 MB

Benötigter Platz: 0 B / 202 GB verfügbar

Fortfahren? [J/n] j

Holen:1 http://security.debian.org/debian-security trixie-security/main amd64 chromium amd64 146.0.7680.80-1~deb13u1 [82,5 MB]

Holen:2 http://security.debian.org/debian-security trixie-security/main amd64 chromium-sandbox amd64 146.0.7680.80-1~deb13u1 [111 kB]

Holen:3 http://security.debian.org/debian-security trixie-security/main amd64 chromium-common amd64 146.0.7680.80-1~deb13u1 [29,2 MB]

Es wurden 112 MB in 8 s geholt (13,3 MB/s).

Changelogs werden gelesen... Fertig

(Lese Datenbank ... 245630 Dateien und Verzeichnisse sind derzeit installiert.)

Vorbereitung zum Entpacken von .../chromium_146.0.7680.80-1~deb13u1_amd64.deb ...

Entpacken von chromium (146.0.7680.80-1~deb13u1) über (146.0.7680.71-1~deb13u1) ...

Vorbereitung zum Entpacken von .../chromium-sandbox_146.0.7680.80-1~deb13u1_amd64.deb ...

Entpacken von chromium-sandbox (146.0.7680.80-1~deb13u1) über (146.0.7680.71-1~deb13u1) ...

Vorbereitung zum Entpacken von .../chromium-common_146.0.7680.80-1~deb13u1_amd64.deb ...

Entpacken von chromium-common (146.0.7680.80-1~deb13u1) über (146.0.7680.71-1~deb13u1) ...

chromium-sandbox (146.0.7680.80-1~deb13u1) wird eingerichtet ...

chromium-common (146.0.7680.80-1~deb13u1) wird eingerichtet ...

chromium (146.0.7680.80-1~deb13u1) wird eingerichtet ...

Trigger für desktop-file-utils (0.28-1) werden verarbeitet ...

Trigger für hicolor-icon-theme (0.18-2) werden verarbeitet ...

Trigger für libc-bin (2.41-12+deb13u2) werden verarbeitet ...

Trigger für man-db (2.13.1-1) werden verarbeitet ...

Trigger für mailcap (3.74) werden verarbeitet ...

iinkognit0@K501:~/workspace$ sudo apt update

OK:1 http://security.debian.org/debian-security trixie-security InRelease

OK:2 http://deb.debian.org/debian trixie InRelease

OK:3 http://deb.debian.org/debian trixie-updates InRelease

OK:4 http://deb.debian.org/debian trixie-backports InRelease

OK:5 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Alle Pakete sind aktuell.

iinkognit0@K501:~/workspace$ python3 k501/runtime/modules/normalizer.py Makefile k501/runtime/tests/

[NORMALIZER] Source: Makefile (Hash: af5cc2a571b0e5c7...)

[NORMALIZER] Output: NORM-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b.txt (Hash: af5cc2a571b0e5c7...)

iinkognit0@K501:~/workspace$ ^[[200~# Extract the exact filename generated in your last output

bash: $'\E[200~#': Kommando nicht gefunden.

iinkognit0@K501:~/workspace$ # Extract the exact filename generated in your last output

python3 k501/runtime/modules/segmenter.py k501/runtime/tests/NORM-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b.txt k501/runtime/tests/chunks/

[SEGMENTER] Processed 236 bytes into 1 blocks.

iinkognit0@K501:~/workspace$ ls -la k501/runtime/tests/chunks/

insgesamt 12

drwxrwxr-x 2 iinkognit0 iinkognit0 4096 16. Mär 15:57 .

drwxrwxr-x 3 iinkognit0 iinkognit0 4096 16. Mär 15:57 ..

-rw-rw-r-- 1 iinkognit0 iinkognit0 236 16. Mär 15:57 CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.bin

iinkognit0@K501:~/workspace$ # Substitute the exact filename of your CHUNK-*.bin file

python3 k501/runtime/modules/framer.py k501/runtime/tests/chunks/CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.bin k501/runtime/tests/frames/

[FRAMER] Constructed: CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json

└─ Content Hash: af5cc2a571b0e5c7...

iinkognit0@K501:~/workspace$ cat k501/runtime/tests/frames/CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json

{"id":"CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000","type":"chunk_frame","qh":[2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"d":{"source_identity":"af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b","chunk_index":0,"content_hash":"af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b","size_bytes":236}}iinkognit0@K501:~/workspace$ python3 k501/runtime/modules/linker.py k501/runtime/tests/frames/CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json

[LINKER] Appended: CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000

└─ Hash: 541e73c7e9ba606089830758a0e4dbf29031b43c95e435c4649e83a97701e28c

└─ T: 1773677052

iinkognit0@K501:~/workspace$ cat archive/little_alpha_storage/frames.ndjson

{"id":"AZ-Epoch-0-Genesis","t":1773524342,"hash":"ec824f323101666eabc2e0f7a020b8a40860720aa445fe657ecf54b3215f5c19"}

{"id":"DOC-CHUNK-0","t":1773524343,"hash":"3c425154fcce921a7c9ac87cc88e3aa1e44965bed3515dc2b9ff22e7f9f69c1c"}

{"id":"CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000","type":"chunk_frame","qh":[2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"d":{"source_identity":"af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b","chunk_index":0,"content_hash":"af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b","size_bytes":236},"t":1773677052,"relations":{"origin":"AZ-Epoch-0-Genesis","parent":"CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000","hash_prev":"3c425154fcce921a7c9ac87cc88e3aa1e44965bed3515dc2b9ff22e7f9f69c1c"},"hash":"541e73c7e9ba606089830758a0e4dbf29031b43c95e435c4649e83a97701e28c"}

iinkognit0@K501:~/workspace$ mkdir -p k501/docs/input

iinkognit0@K501:~/workspace$ cp Makefile k501/docs/input/

cp k501/runtime/modules/normalizer.py k501/docs/input/

iinkognit0@K501:~/workspace$ python3 k501/runtime/ingest_runner.py k501/docs/input/

==================================================

[K501] INITIATING PIPELINE FOR 2 FILE(S)

==================================================

[->] INGESTING: normalizer.py

[NORMALIZER] Source: normalizer.py (Hash: 951fa554af4738fb...)

[NORMALIZER] Output: NORM-951fa554af4738fb30895a5c9c018f3b66a59ae754edc5da20d3cd6cd5937058.txt (Hash: 951fa554af4738fb...)

[SEGMENTER] Processed 3472 bytes into 1 blocks.

[FRAMER] Constructed: CHUNK-951fa554af4738fb30895a5c9c018f3b66a59ae754edc5da20d3cd6cd5937058-000000.json

└─ Content Hash: 951fa554af4738fb...

[LINKER] Appended: CHUNK-951fa554af4738fb30895a5c9c018f3b66a59ae754edc5da20d3cd6cd5937058-000000

└─ Hash: 0689e13d71d5109ee2fcc3c686c053226100ff38837bf85f897eeded890c054f

└─ T: 1773677306

[->] INGESTING: Makefile

[NORMALIZER] Source: Makefile (Hash: af5cc2a571b0e5c7...)

[NORMALIZER] Output: NORM-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b.txt (Hash: af5cc2a571b0e5c7...)

[SEGMENTER] Processed 236 bytes into 1 blocks.

[FRAMER] Constructed: CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json

└─ Content Hash: af5cc2a571b0e5c7...

[LINKER] Appended: CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000

└─ Hash: 51cc48cda9844a68a338076b3f45ed803f8048fd1cdab2a163e802e00a464978

└─ T: 1773677307

==================================================

[K501] INGESTION CYCLE COMPLETE.

==================================================

iinkognit0@K501:~/workspace$ tree -a /home/iinkognit0/workspace

/home/iinkognit0/workspace

├── archive

│ ├── init_k501.sh

│ ├── ledger_k501

│ ├── ledger_root

│ ├── little_alpha_storage

│ │ ├── frames.ndjson

│ │ └── index.dat

│ ├── temp_k501

│ └── temp_root

├── .git

│ ├── branches

│ ├── COMMIT_EDITMSG

│ ├── config

│ ├── description

│ ├── HEAD

│ ├── hooks

│ │ ├── applypatch-msg.sample

│ │ ├── commit-msg.sample

│ │ ├── fsmonitor-watchman.sample

│ │ ├── post-update.sample

│ │ ├── pre-applypatch.sample

│ │ ├── pre-commit.sample

│ │ ├── pre-merge-commit.sample

│ │ ├── prepare-commit-msg.sample

│ │ ├── pre-push.sample

│ │ ├── pre-rebase.sample

│ │ ├── pre-receive.sample

│ │ ├── push-to-checkout.sample

│ │ ├── sendemail-validate.sample

│ │ └── update.sample

│ ├── index

│ ├── info

│ │ └── exclude

│ ├── logs

│ │ ├── HEAD

│ │ └── refs

│ │ └── heads

│ │ └── main

│ ├── objects

│ │ ├── 03

│ │ │ └── 44a2aea333641f7270405fab484f5b3ba0e561

│ │ ├── 07

│ │ │ └── c0583bd98a1df8248b6a6d2f82e3d0a2350bac

│ │ ├── 09

│ │ │ └── cb70494b2eed64c05e5af2171a58af4e271b7f

│ │ ├── 0a

│ │ │ └── 92098ddf796c4c1d26b57cdd6bac1a6a6308bd

│ │ ├── 0f

│ │ │ └── 3e4771d187776480830922403fcd30112b7f7e

│ │ ├── 10

│ │ │ ├── 2869d5a82d875a5cdc42eda23971be952b737a

│ │ │ └── fc1be92687e920de7be60b5557bca74cbe0ada

│ │ ├── 11

│ │ │ └── 6df2b6da6cc15a164892da45e12838ef42343e

│ │ ├── 15

│ │ │ └── 34ef2cde0e4499f4d9e23bf55dd1b31a3ec2bc

│ │ ├── 1d

│ │ │ └── e7ebdad475e5dfa77521d462785c5621eea55f

│ │ ├── 28

│ │ │ └── bfd1a500ffa18089a50a0f83c352099de4360e

│ │ ├── 29

│ │ │ └── 55421424431225614c697555e490ebb00d848a

│ │ ├── 35

│ │ │ └── 80333d381a0c1b969f648ec78ac2262298fef7

│ │ ├── 39

│ │ │ └── ad525c1bf3e2771d87c88524b433e181215693

│ │ ├── 47

│ │ │ └── 1778a7ff0b75c0999d7f199b58b754befc9a20

│ │ ├── 51

│ │ │ └── 80c05c8ab5e7b7c38c59b43bfa0421a434f7b3

│ │ ├── 71

│ │ │ └── 8670d806995bd237c5ad85b04ed5d9acb7d4fa

│ │ ├── 74

│ │ │ └── 346dd9965d6a82e446eacf1916f0071541effa

│ │ ├── 7e

│ │ │ └── 8f40c0054ca7c6ba368659b1948b7672852fda

│ │ ├── a0

│ │ │ └── f24a04050c3e9e20ccec0c5e9e0bb881686e25

│ │ ├── a5

│ │ │ └── 9d46c9b176e2ba4861e4661744db79a971d332

│ │ ├── af

│ │ │ └── 70563de0403cc4072f50eae84d15ce36e55b95

│ │ ├── bd

│ │ │ └── ee36ff3c45a8b62b9948565719d9fb6dcbcf68

│ │ ├── da

│ │ │ └── a10bb79d0c8403b5057ab08055f651bde114f0

│ │ ├── e7

│ │ │ └── 19d1f68ed78f446cb4c7705c08b960519bdf34

│ │ ├── eb

│ │ │ └── 6ac7ee0495c0ce34b130a5806d8b548808ce37

│ │ ├── f4

│ │ │ └── 189242d6e2f2b481ead5e654f50a7e1af09cee

│ │ ├── ff

│ │ │ └── c9b6f228ecc39911e2d59bbed7388b8df7d810

│ │ ├── info

│ │ └── pack

│ └── refs

│ ├── heads

│ │ └── main

│ └── tags

├── .gitignore

├── include

│ ├── dynamic_cage.h

│ ├── frame_engine.h

│ ├── hard_index.h

│ ├── ingestion.h

│ ├── qh_algebra.h

│ └── qh_core.h

├── k501

│ ├── bin

│ ├── docs

│ │ └── input

│ │ ├── Makefile

│ │ └── normalizer.py

│ ├── README.md

│ ├── runtime

│ │ ├── boot_loader

│ │ ├── ingest_runner.py

│ │ ├── modules

│ │ │ ├── framer.py

│ │ │ ├── linker.py

│ │ │ ├── normalizer.py

│ │ │ ├── __pycache__

│ │ │ │ └── quantizer.cpython-313.pyc

│ │ │ ├── quantizer.py

│ │ │ └── segmenter.py

│ │ ├── tests

│ │ │ ├── chunks

│ │ │ │ └── CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.bin

│ │ │ ├── frames

│ │ │ │ └── CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json

│ │ │ └── NORM-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b.txt

│ │ └── tools

│ └── src

├── Makefile

└── src

├── dynamic_cage.c

├── frame_engine.c

├── hard_index.c

├── ingestion.c

├── main.c

├── qh_algebra.c

└── qh_core.c

62 directories, 82 files