#!/bin/bash 
#show errors in color red 
set -o pipefail
cl()("$@" 2>&1>&3|sed $'s,.*,\e[31m&\e[m,'>&2)3>&1


echo -e "\033[1;32m ---------------------- update and install packages ---------------------- \033[0m"
cl sudo apt-get update
cl sudo apt-get -y upgrade
cl sudo apt-get -y install git doxygen gcc g++ make libwxgtk3.*-dev \
libelf-dev freeglut3-dev cutecom gcc-avr avr-libc libopenal-dev libncurses-dev gtkwave \
gedit cmake ccache bison pulseview
cl sudo apt-get -y install linux-headers-`uname -r` dkms 
cl mkdir build_all
cd build_all
echo -e "\033[1;32m ---------------------- download deps -------------------------------------\033[0m"
git clone --depth=1 https://github.com/lcgamboa/picsim.git
git clone --depth=1 https://github.com/lcgamboa/lxrad.git
git clone --depth=1 https://github.com/lcgamboa/simavr.git
git clone --depth=1 https://github.com/lcgamboa/uCsim_picsimlab.git
cl sudo apt-get -y install python3 libglib2.0-dev libpixman-1-dev libfdt-dev gpsim-dev gpsim \
ninja-build meson libgcrypt-dev libslirp-dev
git clone --depth=1 --no-single-branch https://github.com/lcgamboa/qemu.git
echo -e "\033[1;32m ---------------------- build picsim ------------------------- \033[0m"
cd picsim
cl git pull --no-rebase
cl make clean;make -j$(nproc)
cl ln -s ../include/ include/picsim
cd ..
echo -e "\033[1;32m ---------------------- build lxrad -------------------------- \033[0m"
cd lxrad
git pull --no-rebase
cl ./make_deps.sh
cl ./configure --prefix=/usr
cl make clean;make -j$(nproc)
cd ..
echo -e "\033[1;32m ---------------------- build simavr ------------------------- \033[0m"
cd simavr
git pull --no-rebase
cl make clean;make build-simavr -j$(nproc) 
cl ln -s ../sim/ simavr/sim/simavr
cd ../
echo -e "\033[1;32m ---------------------- build uCsim -------------------------- \033[0m"
cd uCsim_picsimlab
git pull --no-rebase
cl ./config_linux.sh
cl make clean;make -j$(nproc)
cd picsimlab
make clean;make
cl make clean;make
ln -s . ucsim
cd ../../
echo -e "\033[1;32m ---------------------- build qemu --------------------- \033[0m"
cd qemu
cl git checkout picsimlab-stm32
git pull --no-rebase
cl ./build_libqemu-stm32.sh
cd build
cl strip libqemu-stm32.so
cl install -d ../../../lib/qemu/
cl cp libqemu-stm32.so ../../../lib/qemu/
cd ..
cl git checkout picsimlab-esp32
cl ./build_libqemu-esp32.sh
cd build
cl strip libqemu-xtensa.so
cl cp libqemu-xtensa.so ../../../lib/qemu/
cl strip libqemu-riscv32.so
cl cp libqemu-riscv32.so ../../../lib/qemu/
cd ..
cl install -d ../../lib/qemu/fw
cl cp pc-bios/esp32-v3-rom*.bin pc-bios/esp32c3-rom.bin ../../lib/qemu/fw/
cd ..
echo -e "\033[1;32m ---------------------- build picsimlab ---------------------- \033[0m"
#git pull --no-rebase
cd ../
cl make clean;make CXX="ccache g++" -j$(nproc) LIBPATH="../build_all/" FILE=Makefile.static
user=`whoami`
cl sudo usermod -a -G dialout $user
echo -e "\033[1;32m ---------------------- done! -------------------------------------------- \033[0m"
echo -e "\033[1;32m logout your session and login to use serial \033[0m"
if xhost > /dev/null 2>&1 ; then
cd share
ln -s ../share/ picsimlab
cd ..
cd lib
ln -s ../lib/ picsimlab
cd ..
cd src
ln -s ../tools/srtank/srtank srtank
ln -s ../tools/espmsim/espmsim espmsim
ln -s ../tools/PinViewer/PinViewer PinViewer
cd ..
cl ./src/picsimlab
fi
