#!/bin/bash
echo lab1112-$1

cd ./deepin-kernel
make oldconfig
fakeroot make-kpkg --initrd --append-to-version=-lab1112-$1 kernel-image kernel-headers -j8
cd ..