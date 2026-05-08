# 1) Validierung
k validate kernel/spec/kernel.yaml

# 2) Tests (Golden / Regression)
k test

# 3) Strict Build
k build --strict kernel/spec/kernel.yaml --out kernel/build/

# 4) Freeze (append-only History)
k freeze kernel/build/ --history kernel/build_history/