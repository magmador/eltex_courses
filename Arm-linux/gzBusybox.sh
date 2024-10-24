#!/bin/bash
cd ./busybox/_install
find . -print0 | cpio --null -ov --format=newc | \
gzip > /home/anton/DISTR/busyboxFS.cpio.gz
