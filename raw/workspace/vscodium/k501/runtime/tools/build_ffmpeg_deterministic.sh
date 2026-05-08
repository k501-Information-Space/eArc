#!/bin/bash
# ==============================================================================
# K501 Sovereign Toolchain: FFmpeg Deterministic Build Script
# Target: ThinkPad T520 (Intel Core i5) | Debian 13
# Policy: Thermal-Safe (make -j2) | Metadata-Free Binaries
# ==============================================================================

# 1. Configuration & Paths
ST_ROOT="/opt/k501/st_root"
SRC_DIR="$ST_ROOT/genesis_src/ffmpeg_sources"
PREFIX="$ST_ROOT"
FFMPEG_VERSION="7.0" 

# Ensure directories exist
mkdir -p "$SRC_DIR"
cd "$SRC_DIR"

echo "[K501] Initiating FFmpeg Deterministic Build..."
echo "[K501] Thermal Policy: Restricted to 2 threads (make -j2)"

# 2. Install Build-Time Dependencies (Debian 13)
# These are necessary for the codecs we defined in the roadmap
sudo apt update
sudo apt install -y \
  yasm nasm build-essential pkg-config \
  libx264-dev libx265-dev libvpx-dev \
  libfdk-aac-dev libmp3lame-dev libopus-dev

# 3. Download Source
if [ ! -f "ffmpeg-${FFMPEG_VERSION}.tar.bz2" ]; then
    echo "[K501] Downloading FFmpeg v${FFMPEG_VERSION} source..."
    wget -q --show-progress "https://ffmpeg.org/releases/ffmpeg-${FFMPEG_VERSION}.tar.bz2"
    tar xjvf "ffmpeg-${FFMPEG_VERSION}.tar.bz2"
fi

cd "ffmpeg-${FFMPEG_VERSION}"

# 4. Configure Build
# We strip DATE and TIME to ensure the binary itself is deterministic
./configure \
  --prefix="$PREFIX" \
  --extra-cflags="-I$ST_ROOT/include -DDATE=0 -DTIME=0" \
  --extra-ldflags="-L$ST_ROOT/lib" \
  --bindir="$ST_ROOT/bin" \
  --enable-gpl \
  --enable-libx264 \
  --enable-libx265 \
  --enable-libvpx \
  --enable-libfdk-aac \
  --enable-libmp3lame \
  --enable-libopus \
  --enable-nonfree \
  --disable-debug \
  --disable-doc \
  --disable-htmlpages \
  --disable-manpages \
  --disable-podpages \
  --disable-txtpages

# 5. Execute Thermal-Safe Compilation
echo "[K501] Starting compilation. Estimated time: 15-30 minutes."
make -j2

# 6. Install to Sovereign Toolchain
echo "[K501] Installing binaries to $ST_ROOT/bin..."
sudo make install

echo "=============================================================================="
echo "[K501] SUCCESS: Sovereign FFmpeg manifested at $ST_ROOT/bin/ffmpeg"
echo "=============================================================================="