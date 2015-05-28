#include "synth.h"

double sine_synth(double t, int wavefreq) {
    double x = TWOPI  * t * wavefreq;
    return sin(x);
}
