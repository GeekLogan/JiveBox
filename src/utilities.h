#include <time.h>
#include <stdio.h>
#include "constants.h"

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

union BufferType {
	signed short int input;
	char parts[2];
};

double convertSecondsToMicroSeconds(double seconds);
void writeBuffer(union BufferType piece);
void writeBufferHumanReadable(union BufferType piece, int charCount);
void delayNanoSecs(long int seconds, long int nanoseconds);
double addSounds(double one, double two);
double addSoundsWeighted(double one, double oneWeight, double two, double twoWeight);
short signed int rasterizeSound(double in);

#endif
