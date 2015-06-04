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
    double out = t * wavefreq;
    out = (out - floor(0.5 + out));
    out = gain_filter_lossless(out, 2.0);
    return out;
}

double triangle_synth(double t, int wavefreq) {
    double saw = sawtooth_synth(t, wavefreq);
    if(saw < 0.0) saw = gain_filter_lossless(saw, -1.0);
    saw = gain_filter_lossless(saw, 2.0);
    saw -= 1.0; //shift range from [0, 2] to [-1, 1]
    return saw;
}
