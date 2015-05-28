all:
	cc -o ../bin/jive jive.c filters.c synth.c utilities.c -lm

old:
	cc -o ../bin/filters filters.c -lm
	cc -o ../bin/utilities utilities.c -lm
	cc -o ../bin/synth synth.c -lm
	cc -o ../bin/jive jive.c -lm

mac-verbose:
	cc -o ../bin/jive jive.c filters.c synth.c utilities.c -lm -v

gnu:
	gcc -o ../bin/jive jive.c filters.c synth.c utilities.c -lm

gnu-verbose:
	gcc -o ../bin/jive jive.c filters.c synth.c utilities.c -lm -v

clean:
	rm -f ../bin/jive
	rm -f TMP

release:
	make clean
	make
	zip -r ../release.zip ../bin
