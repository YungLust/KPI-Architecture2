obj-m := hello.o

# Куди дивитися на джерела ядра (можеш переписати у зовнішні змінні)
KDIR ?= $(HOME)/repos/linux-stable
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

