#!/bin/bash
cd /usr/src/linux-5.7
make mrproper
make ARCH=arm multi_v7_defconfig
make -j4 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
cp -a /usr/src/linux-5.7/arch/arm/boot/zImage /home/anton/DISTR
