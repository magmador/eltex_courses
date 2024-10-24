#!/bin/bash
QEMU_AUDIO_DRV=none qemu-system-arm -M vexpress-a9 -kernel zImage \
-initrd busyboxFS.cpio.gz -dtb vexpress-v2p-ca9.dtb -nographic -append "console=ttyAMA0"
