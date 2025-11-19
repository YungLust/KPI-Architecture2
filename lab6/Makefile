ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello1.o hello2.o

# add debug info to module
ccflags-y += -g

else
# normal makefile (outer build)
KDIR ?= /home/artur/repos/linux-stable
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	# save unstripped copies for debugging
	cp -f hello1.ko hello1.ko.unstripped || true
	cp -f hello2.ko hello2.ko.unstripped || true
	# strip debug symbols, but keep copies
	$(CROSS_COMPILE)strip -g hello1.ko || true
	$(CROSS_COMPILE)strip -g hello2.ko || true

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f hello1.ko.unstripped hello2.ko.unstripped

%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$(PWD) $@
endif

