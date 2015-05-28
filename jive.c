#define TWOPI (M_PI * 2)
#define PI M_PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BITHEIGHT 32766
#define FREQUENCY 44000

union BufferType buffer;
long long int sampletotal;
int samples;
double timeDiff;

union BufferType {
	signed short int input;
	char parts[2];
};

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

void delayNanoSecs(long int seconds, long int nanoseconds) {
	struct timespec time, time2;
	time.tv_sec = seconds;
	time.tv_nsec = nanoseconds;
	nanosleep(&time , &time2);
}

int main(int argCount, char ** args) {
	fprintf(stderr, "Starting JiveBox 0.1 Terminal...\n");

	buffer.input = 0;
	fprintf(stderr, "\nSize of buffer (bytes): %lu\n", sizeof(buffer));

	fprintf(stderr, "\tLocation of input: %p\n", &buffer.input);
	fprintf(stderr, "\tLocation of part #1: %p\n", &buffer.parts[0]);
	fprintf(stderr, "\tLocation of part #2: %p\n\n", &buffer.parts[1]);

	fprintf(stderr, "Initial Variable States:\n");
	fprintf(stderr, "\tBuffer input: %d\n", buffer.input);
	fprintf(stderr, "\tBuffer part #1: %c\n", buffer.parts[0]);
	fprintf(stderr, "\tBuffer part #2: %c\n\n", buffer.parts[1]);

	timeDiff = 1.0 / FREQUENCY;
	double timeDiff_uSeconds = timeDiff * 1000000;

	unsigned short int wavefreq = 0;
	while (wavefreq < 100) {
		wavefreq += 10;

		sampletotal = 0;
		samples = 0;

		while((sampletotal + samples) < FREQUENCY * 3) {
			writeBuffer(buffer);

			double x = TWOPI * wavefreq * timeDiff * (samples + sampletotal);
			double fofx = sin(x);
			fofx += sin(x + 1);
			fofx *= BITHEIGHT;
			fofx = floor(fofx);
			buffer.input = (signed int) fofx;

			samples++;
			if(samples == FREQUENCY) {
				sampletotal += samples;
				samples = 0;
			}
		}

	}

	return 0;
}
