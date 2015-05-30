#include "constants.h"
#include "utilities.h"
#include "filters.h"
#include <math.h>

double sine_synth(double t, int wavefreq);
double cosine_synth(double t, int wavefreq);
double sine_beat_synth(double t, int wavefreq, int bps);
double cosine_beat_synth(double t, int wavefreq, int bps);
double fm_synth(double t, int wavefreq1, int wavefreq2);
double sawtooth_synth(double t, int wavefreq);
double triangle_synth(double t, int wavefreq);
