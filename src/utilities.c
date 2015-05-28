#include "utilities.h"

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
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
