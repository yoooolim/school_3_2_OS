obj-m := file_varea.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

test: test.c
	gcc -o test test.c

testwrapping: test.c
	gcc -o test test.c -DWRAPPING

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

