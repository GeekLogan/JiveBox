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

double cos_beat_synth(double t, int wavefreq, int bps) {
    double one = cosine_synth(t, wavefreq);
    double two = cosine_synth(t, wavefreq + bps);
    return addSounds(one, two);
}

double fm_synth(double t, int wavefreq1, int wavefreq2) {
    double x = TWOPI * t * wavefreq1;
    return sin(x + sine_synth(t, wavefreq2));
}

double sawtooth_synth(double t, int wavefreq) {
    double x = t * wavefreq;
    x = (x - floor(0.5 + x));
    x *= 2.0;
    return x;
}

double triangle_synth(double t, int wavefreq) {
    double saw = sawtooth_synth(t, wavefreq);
    if(saw < 0.0) saw *= -1.0;
    saw *= 2.0;
    saw -= 1.0;
    return saw;
}
