all:
	make jive
	make filters

clean:
	rm jive
	rm filters

ubuntu:
	gcc -o jive jive.c -lm
	gcc -o filters filters.c -lm

ubuntu-verbose:
	gcc -o jive jive.c -lm -v
	gcc -o filters filters.c -lm -v
