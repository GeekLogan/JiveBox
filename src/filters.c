#include "filters.h"

signed short lowpass_filter(signed short val, signed short filter) {
    if(val > filter) {
        return filter;
    } else if(val < (filter * -1)) {
        return (filter * -1);
    } else {
        return val;
    }
}

signed short highpass_filter(signed short val, signed short filter) {
    if(val < filter && val > 0) {
        return filter;
    } else if(val > filter * -1 && val < 0) {
        return filter * -1;
    } else {
        return val;
    }
}

signed short gain_filter(signed short val, double rate) {
    signed short out = (signed short) (val * rate);
    return out;
}

double gain_filter_lossless(double val, double rate) {
    return val * rate;
}
