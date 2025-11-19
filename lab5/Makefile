
# Makefile for lab5 kernel modules
KDIR ?= /home/artur/repos/linux-stable
PWD := $(shell pwd)

# additionally: setting ARCH and CROSS_COMPILE in environment
# export ARCH=arm
# export CROSS_COMPILE=arm-linux-gnueabihf-

obj-m += hello1.o
obj-m += hello2.o

ccflags-y += -I$(PWD)/inc

all:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) clean
