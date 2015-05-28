all:
	cc -o ../bin/jive jive.c -lm
	cc -o ../bin/filters filters.c -lm
	cc -o ../bin/utilities utilities.c -lm
	cc -o ../bin/synth synth.c -lm

mac-verbose:
	cc -o ../bin/jive jive.c -lm -v
	cc -o ../bin/filters filters.c -lm -v
	cc -o ../bin/utilities utilities.c -lm -v
	cc -o ../bin/synth synth.c -lm -v

gnu:
	gcc -o ../bin/jive jive.c -lm
	gcc -o ../bin/filters filters.c -lm
	gcc -o ../bin/utilities utilities.c -lm
	gcc -o ../bin/synth synth.c -lm

gnu-verbose:
	gcc -o ../bin/jive jive.c -lm -v
	gcc -o ../bin/filters filters.c -lm -v
	gcc -o ../bin/utilities utilities.c -lm -v
	gcc -o ../bin/synth synth.c -lm -v

clean:
	rm -f ../bin/jive
	rm -f ../bin/filters
	rm -f ../bin/utilities
	rm -f ../bin/synth

release:
	make clean
	make
	zip -r ../release.zip ../bin
