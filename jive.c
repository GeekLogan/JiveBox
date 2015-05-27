#include <stdio.h>
#include <stdlib.h>

union BufferType {
	unsigned short int input;
	char parts[2];
};

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

int main(int argcnt, char ** args) {
	fprintf(stderr, "Starting JiveBox 0.1 Terminal...\n");

	union BufferType buffer;
	buffer.input = 32767;
	fprintf(stderr, "\nSize of buffer (bytes): %lu\n", sizeof(buffer));

	fprintf(stderr, "\tLocation of input: %p\n", &buffer.input);
	fprintf(stderr, "\tLocation of part #1: %p\n", &buffer.parts[0]);
	fprintf(stderr, "\tLocation of part #2: %p\n\n", &buffer.parts[1]);

	fprintf(stderr, "Initial Variable States:\n");
	fprintf(stderr, "\tBuffer input: %hu\n", buffer.input);
	fprintf(stderr, "\tBuffer part #1: %c\n", buffer.parts[0]);
	fprintf(stderr, "\tBuffer part #2: %c\n\n", buffer.parts[1]);

	while(1) {
		writeBuffer(buffer);
		usleep(1000);
	}

	return 0;
}
