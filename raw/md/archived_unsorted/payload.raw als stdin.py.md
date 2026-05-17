# im Projektordner (root = ".")
python3 bundle_kernel.py init

# payload.raw als stdin
python3 bundle_kernel.py frame --system SUPERFLOW_HD --frame-id FRM-SUPERFLOWHD-0001 --truth MODEL --mode CANON --density MAX <<'EOF'
SUPERFLOW_HD v0.1
- SuperHUD: always-on, 1-line pilot view, big font, minimal stats
- SuperVisuals: SVG HUD overlay, scalable, calm markers
- SuperAcoustics: 3 event tones, <220ms, no loops, mute default ON
- No kernel changes. Module-level only.
EOF