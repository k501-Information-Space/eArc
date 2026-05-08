# Tests
./k --root . test

# Strict Build (Contract)
./k --root . build kernel/spec/kernel.yaml --out kernel/build --strict

# Freeze (append-only build history)
./k --root . freeze kernel/build --history kernel/build_history

# Status (HUD-fähig)
./k --root . status