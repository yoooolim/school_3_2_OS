all: gen_file.c Thread.c
	gcc -o gen_file -g gen_file.c
	gcc -o thread -g Thread.c -lpthread

gen_file: gen_file.c
	gcc -o gen_file -g gen_file.c

thread: Thread.c
	gcc -o thread -g Thread.c -lpthread

clean:
	rm -rf tmp*
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches


