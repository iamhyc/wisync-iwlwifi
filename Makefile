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
	$(MAKE) -C iwlnf SET=$(SET)
	$(MAKE) -C wlsops-hack build-krn
	@echo "======================= [make] Building Finished ======================="
	@echo

build-usr:
	@echo "=================== [make] Building Control Programm ==================="
	$(MAKE) -C iwlsp
	$(MAKE) -C wlsops-hack build-usr
	@echo "======================= [make] Building Finished ======================="
	@echo

install:
	sudo cp -f script/wlsmon /usr/bin/wlsmon
	$(MAKE) -C wlsops-hack install

clean:
	$(MAKE) -C iwlnf clean
	$(MAKE) -C iwlsp clean

route:
	sudo route del default enp0s31f6

start:route
	$(MAKE) -C wlsops-hack insmod
	$(MAKE) -C iwlnf insmod
	$(MAKE) -C iwlsp start

stop:
	$(MAKE) -C iwlsp stop
	$(MAKE) -C iwlnf rmmod
	$(MAKE) -C wlsops-hack rmmod