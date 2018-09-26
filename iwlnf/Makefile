SET=1

# AES Hook Makefile
ifneq ($(KERNELRELEASE),)
	obj-m := iwlmod_icp.o iwlmod_inj.o
	iwlmod_icp-objs := iwl_icp.o
	iwlmod_inj-objs := iwl_inj.o
else
	PWD := $(shell pwd)
	KDIR := /lib/modules/$(shell uname -r)/build

all:build-krn

build-krn:
	cp -f IWLINC.h.$(SET) IWLINC.h
	$(MAKE) -C $(KDIR) M=$(PWD)

insmod:
	sudo insmod iwlmod_inj.ko
	sudo insmod iwlmod_icp.ko

rmmod:
	sudo rmmod iwlmod_icp iwlmod_inj

dmesg:
	sudo dmesg

clean:
	rm -f .cache.mk .*.cmd
	rm -f *.o *.o.cmd *.ko *.mod.c *.symvers *.order
	rm -rf .tmp_versions
endif