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

signed short highpass_filer(signed short val, signed short filter) {
    if(val < filter && val > 0) {
        return filter;
    } else if(val > filter * -1 && val < 0) {
        return filter * -1;
    } else {
        return val;
    }
}
