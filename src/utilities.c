#include "utilities.h"

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

void writeBufferHumanReadable(union BufferType piece, int charCount) {
	if(charCount % 2 == 0)
		charCount++;
	int middle = (charCount / 2) + 1;
	int point = piece.input;
	point /= (BITHEIGHT / (charCount / 2));
	point += charCount / 2;

	fprintf(stdout, "|");
	for(int i = 0; i < charCount; i++) {
		if(i == middle || i == point) {
			if(i == point) {
				fprintf(stdout, "*");
			} else {
				fprintf(stdout, "|");
			}
		} else {
			fprintf(stdout, " ");
		}
	}
	fprintf(stdout, "|\n");
}

void delayNanoSecs(long int seconds, long int nanoseconds) {
	struct timespec time, time2;
	time.tv_sec = seconds;
	time.tv_nsec = nanoseconds;
	nanosleep(&time , &time2);
}

double addSounds(double one, double two) {
	double res = one + two;
	res /= 2.0;
	return res;
}

short signed int rasterizeSound(double in) {
	double res = in;
	res *= BITHEIGHT;
	res = floor(res);
	return (signed int) res;
}
