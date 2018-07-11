obj-m += timer_module.o

all:
	make -C /home/ibarantseva/Downloads/linux-4.17.2/ M=$(PWD) modules

clean:
	make -C /home/ibarantseva/Downloads/linux-4.17.2/ M=$(PWD) clean
