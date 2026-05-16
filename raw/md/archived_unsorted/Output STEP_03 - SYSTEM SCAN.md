# Output STEP_03 :: SYSTEM SCAN

iinkognit0@K501:~$ echo "===== OS =====" &&  
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
===== OS =====  
PRETTY_NAME="Debian GNU/Linux 13 (trixie)"  
NAME="Debian GNU/Linux"  
VERSION_ID="13"  
VERSION="13 (trixie)"  
VERSION_CODENAME=trixie  
DEBIAN_VERSION_FULL=13.4  
ID=debian  
HOME_URL="https://www.debian.org/"  
SUPPORT_URL="https://www.debian.org/support"  
BUG_REPORT_URL="https://bugs.debian.org/"  
  
===== KERNEL =====  
Linux K501 6.12.86+deb13-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.12.86-1 (2026-05-08) x86_64 GNU/Linux  
  
===== SESSION =====  
x11  
  
===== CPU =====  
Model name:                              Intel(R) Xeon(R) CPU           E5430  @ 2.66GHz  
  
===== RAM =====  
             gesamt       benutzt     frei      gemns.  Puffer/Cache verfügbar  
Speicher:       15Gi       5,9Gi       7,4Gi        47Mi       2,7Gi       9,7Gi  
Swap:           32Gi          0B        32Gi  
  
===== GPU =====  
60:00.0 VGA compatible controller: NVIDIA Corporation GT200GL [Quadro FX 3800] (rev a1)  
  
===== DISKS =====  
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS  
loop0    7:0    0   1,5G  1 loop /snap/android-studio/209  
loop1    7:1    0    74M  1 loop /snap/core22/2411  
loop2    7:2    0  49,3M  1 loop /snap/snapd/26865  
sda      8:0    0 931,5G  0 disk    
├─sda1   8:1    0     1K  0 part    
├─sda2   8:2    0 683,6G  0 part    
├─sda5   8:5    0 235,3G  0 part /  
└─sda6   8:6    0  12,6G  0 part [SWAP]  
sr0     11:0    1  1024M  0 rom     
zram0  254:0    0   7,8G  0 disk [SWAP]  
  
===== KDE =====  
plasmashell 6.3.6  
QThreadStorage: Thread 0x557da680b2b0 exited after QThreadStorage 8 destroyed  
QThreadStorage: Thread 0x557da680b2b0 exited after QThreadStorage 3 destroyed  
QThreadStorage: Thread 0x557da680b2b0 exited after QThreadStorage 2 destroyed  
  
===== INSTALLED BROWSERS =====  
ii  chromium                                            148.0.7778.96-1~deb13u1              amd64        web browser  
ii  chromium-common                                     148.0.7778.96-1~deb13u1              amd64        web browser - common resources used by the chromium packages  
ii  chromium-sandbox                                    148.0.7778.96-1~deb13u1              amd64        web browser - setuid security sandbox for chromium  
ii  firefox-esr                                         140.10.2esr-1~deb13u1                amd64        Mozilla Firefox web browser - Extended Support Release (ESR)  
ii  firefox-esr-l10n-de                                 140.10.2esr-1~deb13u1                all          German language package for Firefox ESR  
  
===== INSTALLED EDITORS =====  
ii  amd64-microcode                                     3.20250311.1                         amd64        Platform firmware and microcode for AMD CPUs and SoCs  
ii  code                                                1.120.0-1778619059                   amd64        Code editing. Redefined.  
ii  dmidecode                                           3.6-2                                amd64        SMBIOS/DMI table decoder  
ii  fonts-hack                                          3.003-3                              all          Typeface designed for source code  
ii  fonts-noto-cjk                                      1:20240730+repack1-1                 all          "No Tofu" font families with large Unicode coverage (CJK regular and bold)  
ii  fonts-noto-cjk-extra                                1:20240730+repack1-1                 all          "No Tofu" font families with large Unicode coverage (CJK all weight)  
ii  fonts-noto-core                                     20201225-2                           all          "No Tofu" font families with large Unicode coverage (core)  
ii  fonts-noto-extra                                    20201225-2                           all          "No Tofu" font families with large Unicode coverage (extra)  
ii  fonts-noto-mono                                     20201225-2                           all          "No Tofu" monospaced font family with large Unicode coverage  
ii  fonts-noto-ui-core                                  20201225-2                           all          "No Tofu" font families with large Unicode coverage (UI core)  
ii  fonts-noto-ui-extra                                 20201225-2                           all          "No Tofu" font families with large Unicode coverage (UI extra)  
ii  fonts-noto-unhinted                                 20201225-2                           all          "No Tofu" font families with large Unicode coverage (unhinted)  
ii  fonts-symbola                                       2.60-2                               all          symbolic font providing emoji characters from Unicode 9.0  
ii  intel-microcode                                     3.20251111.1~deb13u1                 amd64        Processor microcode firmware for Intel CPUs  
ii  iso-codes                                           4.18.0-1                             all          ISO language, territory, currency, script codes and their translations  
ii  iucode-tool                                         2.3.1-3                              amd64        Intel processor microcode tool  
ii  libavcodec61:amd64                                  7:7.1.3-0+deb13u1                    amd64        FFmpeg library with de/encoders for audio/video codecs - runtime files  
ii  libbrotli1:amd64                                    1.1.0-2+b7                           amd64        library implementing brotli encoder and decoder (shared libraries)  
ii  libcodec2-1.2:amd64                                 1.2.0-3                              amd64        Codec2 runtime library  
ii  libdav1d7:amd64                                     1.5.1-1                              amd64        fast and small AV1 video stream decoder (shared library)  
ii  libde265-0:amd64                                    1.0.15-1+b3                          amd64        Open H.265 video codec implementation  
ii  libdmtx0t64:amd64                                   0.7.7-1.2+b1                         amd64        Data Matrix barcodes (runtime library)  
ii  libencode-locale-perl                               1.05-3                               all          utility to determine the locale encoding  
ii  libfaad2:amd64                                      2.11.2-1                             amd64        freeware Advanced Audio Decoder - runtime files  
ii  libfribidi0:amd64                                   1.0.16-1                             amd64        Free Implementation of the Unicode BiDi algorithm  
ii  libfuturesql6-0:amd64                               0.1.1-2                              amd64        asynchronous Qt code library  
ii  libgav1-1:amd64                                     0.19.0-3+b1                          amd64        AV1 decoder developed by Google -- runtime library  
ii  libheif-plugin-aomenc:amd64                         1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - aomenc plugin  
ii  libheif-plugin-dav1d:amd64                          1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - dav1d plugin  
ii  libheif-plugin-j2kdec:amd64                         1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - j2kdec plugin  
ii  libheif-plugin-libde265:amd64                       1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - libde265 plugin  
ii  libheif-plugin-x265:amd64                           1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - x265 plugin  
ii  libheif1:amd64                                      1.19.8-1                             amd64        HEIF and AVIF file format decoder and encoder - shared library  
ii  libicu76:amd64                                      76.1-4                               amd64        International Components for Unicode  
ii  libipt2                                             2.1.2-1                              amd64        Intel Processor Trace Decoder Library  
ii  libjbig2dec0:amd64                                  0.20-1+b3                            amd64        JBIG2 decoder library - shared libraries  
ii  libkf5codecs-data                                   5.116.0-1                            all          collection of methods to manipulate strings  
ii  libkf5codecs5:amd64                                 5.116.0-1                            amd64        collection of methods to manipulate strings  
ii  libkf6codecs-data                                   6.13.0-1                             all          collection of methods to manipulate strings  
ii  libkf6codecs6:amd64                                 6.13.0-1                             amd64        collection of methods to manipulate strings  
ii  libkf6prison6:amd64                                 6.13.0-1                             amd64        barcode API for Qt  
ii  libkf6prisonscanner6:amd64                          6.13.0-1                             amd64        barcode API for Qt - barcode scanner  
ii  libldacbt-enc2:amd64                                2.0.2.3+git20200429+ed310a0-5        amd64        LDAC Bluetooth encoder library (shared library)  
ii  libltc11:amd64                                      1.3.2-1+b2                           amd64        linear timecode library  
ii  libmad0:amd64                                       0.15.1b-11+b1                        amd64        MPEG audio decoder library  
ii  libmagickcore-7.q16-10-extra:amd64                  8:7.1.1.43+dfsg1-1+deb13u8           amd64        low-level image manipulation library - extra codecs (Q16)  
ii  libmpcdec6:amd64                                    2:0.1~r495-3                         amd64        MusePack decoder - library  
ii  libmpeg2-4:amd64                                    0.5.1-9+b3                           amd64        MPEG1 and MPEG2 video decoder library  
ii  libmpg123-0t64:amd64                                1.32.10-1+deb13u1                    amd64        MPEG layer 1/2/3 audio decoder (shared library)  
ii  libopencore-amrnb0:amd64                            0.1.6-1+b2                           amd64        Adaptive Multi Rate speech codec - shared library  
ii  libopencore-amrwb0:amd64                            0.1.6-1+b2                           amd64        Adaptive Multi-Rate - Wideband speech codec - shared library  
ii  libopenfec1:amd64                                   1.4.2.11+dfsg-1                      amd64        Application-Level Forward Erasure Correction codes (shared library)  
ii  libopus0:amd64                                      1.5.2-2                              amd64        Opus codec runtime library  
ii  libqrencode4:amd64                                  4.1.1-2                              amd64        QR Code encoding library  
ii  librav1e0.7:amd64                                   0.7.1-9+b2                           amd64        Fastest and safest AV1 encoder - shared library  
ii  libraw23t64:amd64                                   0.21.4-2                             amd64        raw image decoder library  
ii  libsixel1:amd64                                     1.10.5-1                             amd64        DEC SIXEL graphics codec implementation (runtime)  
ii  libspeex1:amd64                                     1.2.1-3                              amd64        Speex codec library (runtime library)  
ii  libunibreak6:amd64                                  6.1-3                                amd64        line breaking library for Unicode (shared library)  
ii  libunistring5:amd64                                 1.3-2                                amd64        Unicode string library for C  
ii  libvdpau1:amd64                                     1.5-3+b1                             amd64        Video Decode and Presentation API for Unix (libraries)  
ii  libvo-aacenc0:amd64                                 0.1.3-3                              amd64        VisualOn AAC encoder library  
ii  libvo-amrwbenc0:amd64                               0.1.3-2+b2                           amd64        VisualOn AMR-WB encoder library  
ii  libvorbis0a:amd64                                   1.3.7-3                              amd64        decoder library for Vorbis General Audio Compression Codec  
ii  libvorbisenc2:amd64                                 1.3.7-3                              amd64        encoder library for Vorbis General Audio Compression Codec  
ii  libvpx9:amd64                                       1.15.0-2.1+deb13u1                   amd64        VP8 and VP9 video codec (shared library)  
ii  libwavpack1:amd64                                   5.8.1-1                              amd64        audio codec (lossy and lossless) - library  
ii  libx265-215:amd64                                   4.1-2                                amd64        H.265/HEVC video stream encoder (shared library)  
ii  libxvidcore4:amd64                                  2:1.3.7-1+b2                         amd64        Open source MPEG-4 video codec (library)  
ii  libzbar0t64:amd64                                   0.23.93-8                            amd64        QR code / bar code scanner and decoder (library)  
ii  libzvbi-common                                      0.2.44-1                             all          Vertical Blanking Interval decoder (VBI) - common files  
ii  libzvbi0t64:amd64                                   0.2.44-1                             amd64        Vertical Blanking Interval decoder (VBI) - runtime files  
ii  luit                                                2.0.20240910-1                       amd64        locale and ISO 2022 support for Unicode terminals  
ii  numba-doc                                           0.61.2+dfsg-1                        all          native machine code compiler for Python (docs)  
ii  obsidian                                            1.12.7                               amd64           
ii  python3-asttokens                                   3.0.0-1                              all          annotate Python asbtract syntax trees with code references (Python 3)  
ii  python3-brotlicffi                                  1.1.0.0+ds1-1                        amd64        Python CFFI bindings for the reference Brotli encoder/decoder  
ii  python3-cffi-backend:amd64                          1.17.1-3                             amd64        Foreign Function Interface for Python 3 calling C code - runtime  
ii  python3-hyperframe                                  6.0.0-1                              all          Pure-Python3 HTTP/2 framing code  
ii  python3-linkify-it                                  2.0.3-1                              all          links recognition library with FULL unicode support  
ii  python3-numba                                       0.61.2+dfsg-1                        amd64        native machine code compiler for Python 3  
ii  python3-unicodedata2                                15.1.0+ds-1+b4                       amd64        Python unicodedata backport/updates  
ii  python3-unidecode                                   1.4.0-1                              all          ASCII transliterations of Unicode text (Python 3 module)  
ii  qml6-module-org-kde-prison:amd64                    6.13.0-1                             amd64        barcode API for Qt  
ii  unicode-data                                        15.1.0-1                             all          Property data for the Unicode character set  
ii  vdpau-driver-all:amd64                              1.5-3+b1                             amd64        Video Decode and Presentation API for Unix (driver metapackage)  
  
===== WAYLAND/X11 =====  
Type=x11  
  
Type=unspecified  
iinkognit0@K501:~$