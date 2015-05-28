#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "utilities.h"
#include "synth.h"
#include "filters.h"

union BufferType buffer;
long long int sampletotal;
int samples;
double timeDiff;

long long int getTotalSamples() {
	return (samples + sampletotal);
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

	unsigned short int wavefreq = 10;

	sampletotal = 0;
	samples = 0;

	while(getTotalSamples() < FREQUENCY) {
		if(getTotalSamples() % 200 == 0)
			writeBufferHumanReadable(buffer, 100);

		double fofx = sine_beat_synth(timeDiff * getTotalSamples(), wavefreq, 1);
		buffer.input = rasterizeSound(fofx);

		samples++;
		if(samples == FREQUENCY) {
			sampletotal += samples;
			samples = 0;
		}
	}


	return 0;
}
