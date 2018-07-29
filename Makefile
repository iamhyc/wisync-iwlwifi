SHELL=/bin/bash
APT=apt-fast
KERVER=v0

all:build-dep build-krn install

build-dep:
	@echo "============== [apt] Installing Build Dependency =============="
	@sudo $(APT) install build-essential fakeroot libssl-dev qt5-default gcc-7-plugin-dev cmake libnl-3-dev libnl-genl-3-dev libelf-dev -y

	@echo "============== [apt] Installing Pacakge Dependency =============="
	@sudo $(APT) install kernel-package libncurses5-dev bison flex quilt pkg-config -y

	@echo "============== [git] Fetching deepin-kernel =============="
	@git clone https://github.com/linuxdeepin/deepin-kernel.git --branch=4.14.12 --depth=1 \
	&& cd deepin-kernel && make -f debian/rules orig && cd .. \
	&& rm -rf orig && rm -rf deepin-kernel/.git && rm -f *.tar.xz \
	&& cp -r patch/* deepin-kernel/

	@echo "============== Installing Finished =============="

build-krn:
	./script/build_kernel.sh $(KERVER)

build-usr:
	cd iwlnf; make; cd ..
	cd iwlnl; make; cd ..

install:
	sudo dpkg -i linux-image-*$(KERVER)*.deb
	sudo dpkg -i linux-header-*$(KERVER)*.deb

route:
	./script/ip_route.sh

start:route
	# ./script/init_ap.sh
	cd iwlnf; make insmod; cd ..
	cd iwlnl; make start; cd ..

stop:
	# ./script/fini_ap.sh
	cd iwlnl; make stop; cd ..
	cd iwlnf; make rmmod; cd ..