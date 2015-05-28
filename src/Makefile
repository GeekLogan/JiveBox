all:
	cc -o ../bin/jive jive.c -lm
	cc -o ../bin/filters filters.c -lm
	cc -o ../bin/utilities utilities.c -lm

mac-verbose:
	cc -o ../bin/jive jive.c -lm -v
	cc -o ../bin/filters filters.c -lm -v
	cc -o ../bin/utilities utilities.c -lm -v

ubuntu:
	gcc -o ../bin/jive jive.c -lm
	gcc -o ../bin/filters filters.c -lm
	gcc -o ../bin/utilities utilities.c -lm

ubuntu-verbose:
	gcc -o ../bin/jive jive.c -lm -v
	gcc -o ../bin/filters filters.c -lm -v
	gcc -o ../bin/utilities utilities.c -lm -v

clean:
	rm -f ../bin/jive
	rm -f ../bin/filters
	rm -f ../bin/utilities
