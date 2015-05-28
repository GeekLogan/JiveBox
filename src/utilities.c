#include "utilities.h"

void delayNanoSecs(long int seconds, long int nanoseconds) {
	struct timespec time, time2;
	time.tv_sec = seconds;
	time.tv_nsec = nanoseconds;
	nanosleep(&time , &time2);
}

/* below prevents compiler errors due to
this file not being executable */
int main(int argCount, char ** args){}
