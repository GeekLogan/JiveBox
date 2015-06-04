all:
	gcc -o jive jive.c filters.c synth.c utilities.c DVRGPIOInterface.c -l wiringPi -std=c99 -lm

gnu-verbose:
	gcc -o jive jive.c filters.c synth.c utilities.c DVRGPIOInterface.c -l wiringPi -std=c99 -lm -v

clean:
	rm -f jive
	rm -f TMP
