#include <time.h>
#include <stdio.h>
#include "constants.h"

union BufferType {
	signed short int input;
	char parts[2];
};

void writeBuffer(union BufferType piece);
void delayNanoSecs(long int seconds, long int nanoseconds);
double addSounds(double one, double two);
short signed int rasterizeSound(double in);
