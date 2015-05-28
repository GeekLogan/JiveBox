#define TWOPI (M_PI * 2)
#define PI M_PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BITHEIGHT 32000
#define FREQUENCY 44000

double timeDiff, timer;
union BufferType buffer;
long long int samples;

union BufferType {
	short int input;
	char parts[2];
};

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

void delayNanoSecs(long int seconds, long int nanoseconds) {
	struct timespec tim, tim2;
	tim.tv_sec = seconds;
	tim.tv_nsec = nanoseconds;
	nanosleep(&tim , &tim2);
}


int main(int argcnt, char ** args) {
	fprintf(stderr, "Starting JiveBox 0.1 Terminal...\n");

	buffer.input = 0;
	fprintf(stderr, "\nSize of buffer (bytes): %lu\n", sizeof(buffer));

	fprintf(stderr, "\tLocation of input: %p\n", &buffer.input);
	fprintf(stderr, "\tLocation of part #1: %p\n", &buffer.parts[0]);
	fprintf(stderr, "\tLocation of part #2: %p\n\n", &buffer.parts[1]);

	fprintf(stderr, "Initial Variable States:\n");
	fprintf(stderr, "\tBuffer input: %hu\n", buffer.input);
	fprintf(stderr, "\tBuffer part #1: %c\n", buffer.parts[0]);
	fprintf(stderr, "\tBuffer part #2: %c\n\n", buffer.parts[1]);

	timer = 0;
	timeDiff = 1.0 / FREQUENCY;
	samples = 0;

	register int wavefreq = 400;

	while(1) {
		writeBuffer(buffer);

		double fofx = sin(TWOPI * timer * wavefreq);
		fofx *= BITHEIGHT;
		fofx = floor(fofx);
		buffer.input = (short int) fofx;

		timer += timeDiff;
		if(samples > FREQUENCY) {
			samples = 0;
			if(timer < 1.0) {
				register double diff = 1.0 - timer;
				diff *= 10,000;
				diff = floor(diff);
				long int diffLong = (long int) diff;
				delayNanoSecs(0L, diffLong);
			}
			timer = 0.0;
		} else {
			samples++;
		}
	}

	return 0;
}
