SHELL=/bin/bash
APT=apt-get
SET=1

all:build-dep build-krn build-usr

build-dep:
	@echo "================== [apt] Installing Build Dependency =================="
	@sudo $(APT) install linux-headers-$(shell uname -r) build-essential fakeroot libelf-dev -y 1>/dev/null
	git submodule init && git submodule update
	@echo "====================== [apt] Installing Finished ======================"
	@echo

build-krn:
	@echo "==================== [make] Building Kernel Module ===================="
	$(MAKE) -C intel-mvm -j7
	$(MAKE) -C wlsops-hack build-krn
	$(MAKE) -C iwlnf SET=$(SET)
	@echo "======================= [make] Building Finished ======================="
	@echo

build-usr:
	@echo "=================== [make] Building Control Programm ==================="
	$(MAKE) -C wlsops-hack build-usr
	$(MAKE) -C iwlsp
	@echo "======================= [make] Building Finished ======================="
	@echo

install:
	sudo cp -f script/wlsmon /usr/bin/wlsmon
	$(MAKE) -C wlsops-hack install

clean:
	$(MAKE) -C iwlnf clean
	$(MAKE) -C iwlsp clean

insmod:
	@$(MAKE) -iC intel-mvm rmmod && $(MAKE) -C intel-mvm insmod
	@$(MAKE) -iC wlsops-hack insmod

rmmod:
	@$(MAKE) -iC wlsops-hack rmmod
	@$(MAKE) -iC intel-mvm rmmod && $(MAKE) -iC intel-mvm modprobe

dmesg:
	@sudo dmesg | grep --color "LAB1112:"

route:
	@echo `sudo route del default enp0s31f6 2> /dev/null` >/dev/null
	@echo "[route] default wired route deleted"

start:insmod route
	@$(MAKE) -C iwlnf insmod
	@$(MAKE) -C iwlsp start

stop:rmmod
	@$(MAKE) -C iwlsp stop
	@$(MAKE) -C iwlnf rmmod