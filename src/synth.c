#include "synth.h"

double sine_synth(double t, int wavefreq) {
    double x = TWOPI  * t * wavefreq;
    return sin(x);
}

double cosine_synth(double t, int wavefreq) {
    double x = TWOPI  * t * wavefreq;
    return cos(x);
}

double sine_beat_synth(double t, int wavefreq, int bps) {
    double one = sine_synth(t, wavefreq);
    double two = sine_synth(t, wavefreq + bps);
    return addSounds(one, two);
}
