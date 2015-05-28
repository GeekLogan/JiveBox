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
	return(samples + sampletotal);
}

double makeNoise(double t) {
	unsigned short int wavefreq = 10;
	double fofx = sine_beat_synth(t, wavefreq, 1);
	return fofx;
}

int main(int argCount, char ** args) {
	buffer.input = 0;

	fprintf(stderr, "Starting JiveBox 0.1 Terminal...\n\n");

	fprintf(stderr, "Size of buffer (bytes): %lu\n", sizeof(buffer));
	fprintf(stderr, "\tLocation of input: %p\n", &buffer.input);
	fprintf(stderr, "\tLocation of part #1: %p\n", &buffer.parts[0]);
	fprintf(stderr, "\tLocation of part #2: %p\n\n", &buffer.parts[1]);

	fprintf(stderr, "Initial Variable States:\n");
	fprintf(stderr, "\tBuffer input: %d\n", buffer.input);
	fprintf(stderr, "\tBuffer part #1: %c\n", buffer.parts[0]);
	fprintf(stderr, "\tBuffer part #2: %c\n\n", buffer.parts[1]);

	fprintf(stderr, "Starting Data Generation:\n\n");

	timeDiff = 1.0 / FREQUENCY;
	//double timeDiff_uSeconds = timeDiff * 1000000;
	sampletotal = 0;
	samples = sampletotal;

	while(getTotalSamples() < FREQUENCY) { //loop once
		if(getTotalSamples() % 250 == 0) {
			writeBufferHumanReadable(buffer, 150);
		}
		writeBuffer(buffer);

		double cur = makeNoise(timeDiff * getTotalSamples());
		buffer.input = rasterizeSound(cur);

		samples++;
		if(samples == FREQUENCY) {
			sampletotal += samples;
			samples = 0;
		}
	}

	return 0;
}
