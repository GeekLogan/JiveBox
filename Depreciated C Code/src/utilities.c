#include "utilities.h"

void writeBuffer(union BufferType piece) {
	fprintf(stdout, "%c%c", piece.parts[0], piece.parts[1]);
}

void writeBufferHumanReadable(union BufferType piece, int charCount) {
	if(charCount % 2 == 0) charCount++;
	int middle = (charCount / 2) + 1;
	int point = piece.input;
	point /= (BITHEIGHT / (charCount / 2));
	point += (charCount / 2);

	fprintf(stderr, "|");
	int i;
	for(i = 0; i < charCount; i++) {
		if(i == middle || i == point) {
			if(i == point) {
				fprintf(stderr, "*");
			} else {
				fprintf(stderr, "|");
			}
		} else {
			fprintf(stderr, " ");
		}
	}
	fprintf(stderr, "|\n");
}

double addSounds(double one, double two) {
	double res = one + two;
	res /= 2.0;
	return res;
}

double addSoundsWeighted(double one, double oneWeight, double two, double twoWeight) {
	double res = ( one * oneWeight + two * twoWeight);
	return res;
}

short signed int rasterizeSound(double in) {
	double res = in;
	res *= BITHEIGHT;
	res = floor(res);
	return (signed int) res;
}
