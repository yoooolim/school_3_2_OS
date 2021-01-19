obj-m = my_module.o

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc -o test test_add.c

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
