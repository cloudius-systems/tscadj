

kver := $(shell uname -r)

all:
	make -C /lib/modules/$(kver)/build M=$(shell pwd)

install:
	make -C /lib/modules/$(kver)/build M=$(shell pwd) modules_install


