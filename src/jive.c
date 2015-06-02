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
	return fm_synth(t, 4, 9);
	//return sawtooth_synth(t, 2);
	//return triangle_synth(t, 2);
}

signed short doFilters(signed short in) {
	//in = lowpass_filter(in, (signed short) (BITHEIGHT * 0.5));
	//in = highpass_filter(in, (signed short) (BITHEIGHT * 0.1));
	//in = gain_filter(in, 2);
	//in = bitcrush_filter(in, 4000);
	return in;
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
	sampletotal = 0;
	samples = sampletotal;

	while(getTotalSamples() < FREQUENCY) {
		if(getTotalSamples() % 100 == 0) {
			writeBufferHumanReadable(buffer, CONSOLEWIDTH);
		}
		writeBuffer(buffer);

		double fromGenerator = makeNoise(timeDiff * getTotalSamples());
		signed short toProcess = rasterizeSound(fromGenerator);
		buffer.input = doFilters(toProcess);

		samples++;
		if(samples == FREQUENCY) {
			sampletotal += samples;
			samples = 0;
		}
	}

	return 0;
}
