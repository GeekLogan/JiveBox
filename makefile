all:
	make utilities
	make filters
	make jive

mac-verbose:
	cc -o jive jive.c -lm -v
	cc -o filters filters.c -lm -v
	cc -o utilities utilities.c -lm -v

ubuntu:
	gcc -o jive jive.c -lm
	gcc -o filters filters.c -lm
	gcc -o utilities utilities.c -lm

ubuntu-verbose:
	gcc -o jive jive.c -lm -v
	gcc -o filters filters.c -lm -v
	gcc -o utilities utilities.c -lm -v


clean:
	rm -f jive
	rm -f filters
	rm -f utilities
