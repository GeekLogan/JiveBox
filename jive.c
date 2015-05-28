#define TWOPI (M_PI * 2)
#define PI M_PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FREQUENCY 44000

union BufferType buffer;

union BufferType {
	char parts[2];
};

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

void delayNanoSecs(long int seconds, long int nanoseconds) {
}


	fprintf(stderr, "Starting JiveBox 0.1 Terminal...\n");

	buffer.input = 0;
	fprintf(stderr, "\nSize of buffer (bytes): %lu\n", sizeof(buffer));

	fprintf(stderr, "\tLocation of input: %p\n", &buffer.input);
	fprintf(stderr, "\tLocation of part #1: %p\n", &buffer.parts[0]);
	fprintf(stderr, "\tLocation of part #2: %p\n\n", &buffer.parts[1]);

	fprintf(stderr, "Initial Variable States:\n");
	fprintf(stderr, "\tBuffer part #1: %c\n", buffer.parts[0]);
	fprintf(stderr, "\tBuffer part #2: %c\n\n", buffer.parts[1]);

	timeDiff = 1.0 / FREQUENCY;

			samples++;
		}
	}

	return 0;
}
