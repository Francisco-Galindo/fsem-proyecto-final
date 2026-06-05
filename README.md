# arcade-fsem

Custom Buildroot configuration for a dedicated retro game console running on Raspberry Pi 4.

Emulates NES, SNES, and Game Boy Advance via Mednafen. Boots directly into a fullscreen
SDL2 launcher controlled by a USB gamepad. No desktop environment.

## Requirements

- Ubuntu or Debian Linux host (x86_64)
- 20 GiB free disk space
- 4 GiB RAM recommended

## Setup

### 1. Install dependencies

```bash
sudo apt update
sudo apt install -y git bc bison flex libssl-dev make libc6-dev \
     libncurses5-dev build-essential crossbuild-essential-arm64
```

### 2. Clone Buildroot

```bash
git clone --branch 2025.02 https://github.com/buildroot/buildroot.git
cd buildroot
```

### 3. Apply this configuration

```bash
# Copy all files from this repo on top of the Buildroot tree
cp -r /path/to/arcade-buildroot/* .
make oldconfig
```

### 4. Add ROMs

ROMs are not included in this repository. Place them in the overlay before building:

```
board/raspberrypi4-64/rootfs-overlay/usr/share/roms/nes/    (.nes)
board/raspberrypi4-64/rootfs-overlay/usr/share/roms/snes/   (.sfc .smc)
board/raspberrypi4-64/rootfs-overlay/usr/share/roms/gba/    (.gba)
```

A minimum of 15 ROM files is required.

### 5. Add assets

```
board/raspberrypi4-64/rootfs-overlay/usr/share/arcade/splash.bmp
board/raspberrypi4-64/rootfs-overlay/usr/share/arcade/splash.wav
board/raspberrypi4-64/rootfs-overlay/usr/share/fonts/launcher.ttf
```

### 6. Build

```bash
make
```

Build time is approximately 90 minutes to 4 hours depending on host hardware.
Output image is at `output/images/sdcard.img`.

### 7. Flash

Identify your SD card device node first:

```bash
lsblk
```

Then flash:

```bash
sudo dd if=output/images/sdcard.img of=/dev/sdX bs=10M status=progress
sync
```

Replace `/dev/sdX` with the correct device. Verify carefully before running.

## Rebuilding a single package

```bash
make <package>-dirclean && make <package> && make
```

Packages: `splash`, `launcher`, `remote`

## Remote control

Connect the Pi to the local network via Ethernet. The system obtains an IP via DHCP.
Open `http://<pi-ip>:8080` in any browser on the same network.
