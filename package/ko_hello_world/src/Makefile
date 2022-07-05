CROSS_COMPILE := riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)ld


ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= $(BR2_EXTERNAL_K510_PATH)/k510_crb_lp3_v1_2_defconfig/build/linux-4.17
	PWD := $(shell pwd)
	modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	clean:
	rm -rf *.o *~core.depend .*.cmd *.ko *.mod.c .tmp_versions
else
	obj-m := ko_hello_world.o
endif


