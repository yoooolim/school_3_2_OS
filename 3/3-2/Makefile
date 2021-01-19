all: gen_files.c schedtest.c
	gcc -o gen_files -g gen_files.c
	gcc -o schedtest -g schedtest.c

gen_files: gen_files.c
	gcc -o gen_files -g gen_files.c

thread: schedtest.c
	gcc -o schedtest -g schedtest.c -schedtest

clean:
	rm -rf tmp*
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches


