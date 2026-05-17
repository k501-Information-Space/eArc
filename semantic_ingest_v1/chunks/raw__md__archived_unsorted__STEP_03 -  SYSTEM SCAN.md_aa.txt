Perfekt. apt layer jetzt sauber.

# STEP_03 :: SYSTEM SCAN

Jetzt kompletter Ist-Zustand.

Führe das aus:

```bash
echo "===== OS =====" &&
cat /etc/os-release &&
echo &&
echo "===== KERNEL =====" &&
uname -a &&
echo &&
echo "===== SESSION =====" &&
echo $XDG_SESSION_TYPE &&
echo &&
echo "===== CPU =====" &&
lscpu | grep "Model name" &&
echo &&
echo "===== RAM =====" &&
free -h &&
echo &&
echo "===== GPU =====" &&
lspci | grep -E "VGA|3D" &&
echo &&
echo "===== DISKS =====" &&
lsblk &&
echo &&
echo "===== KDE =====" &&
plasmashell --version &&
echo &&
echo "===== INSTALLED BROWSERS =====" &&
dpkg -l | grep -E "firefox|chromium|chrome" &&
echo &&
echo "===== INSTALLED EDITORS =====" &&
dpkg -l | grep -E "code|codium|obsidian" &&
echo &&
echo "===== WAYLAND/X11 =====" &&
loginctl show-session $(loginctl | grep $(whoami) | awk '{print $1}') -p Type
```

Poste Output.