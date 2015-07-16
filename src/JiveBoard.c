#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#include <linux/input.h>
#include <linux/uinput.h>

#define MAX_KEY 226
#define BUFFER_KEY KEY_LEFTSHIFT
#define DEBUG 1

int interface, ctl;
int key_blacklist[] = {0,84,120,181,182,195,196,197,198,199};

int getKeyCodeFromChar( char in );

int main(int argc, char ** args) {

	if(DEBUG) printf("Opening Device...\n");
	interface = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	//Make Interface
	if(interface < 0) { //Check if device was made
		fprintf(stderr, "Device Opening Failed (ERR# %d)...\n", interface);
		exit(EXIT_FAILURE);
		//Something went terribly wrong
	}

	if(DEBUG) printf("Setting EVBIT...\n");
	ctl = ioctl( interface, UI_SET_EVBIT, EV_KEY );
	//Turn interface to key-mode

	if(DEBUG) printf("Loading Key Support...\n");
	for(int i = 0; i <= MAX_KEY; i++) {
		int isBlacklisted = 0;
		for(int j = 0; j < sizeof(key_blacklist) / sizeof(int) && !isBlacklisted; j++) {
			isBlacklisted += (key_blacklist[j] == i);
		}
		if(!isBlacklisted) {
			ctl = ioctl(interface, UI_SET_KEYBIT, i);
		}
	}

	if(DEBUG) printf("Building Device Description....\n");
	struct uinput_user_dev uidev;
	memset(&uidev, 0, sizeof(uidev));
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-test");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor = 0x1234;
	uidev.id.product = 0xfedc;
	uidev.id.version = 1;

	ctl = write(interface, &uidev, sizeof(uidev));
	ctl = ioctl(interface, UI_DEV_CREATE);

	/*
	printf("Writing Test Keys...\n");
	for(int i = 'a'; i <= 'z'; i++) {
		printf("(%d)\n", i);
		struct input_event ev;
		memset(&ev, 0, sizeof(ev));
		ev.type = EV_KEY;
		ev.code = getKeyCodeFromChar((char) i);
		ev.value = 1;
		ctl = write(interface, &ev, sizeof(ev));
		ev.value = 0;
		ctl = write(interface, &ev, sizeof(ev));
		ev.code = BUFFER_KEY;
		for(int j = 0; j < 3; j++) {
			ev.value = 1;
			ctl = write(interface, &ev, sizeof(ev));
			ev.value = 0;
			ctl = write(interface, &ev, sizeof(ev));
		}
		sleep(1);
	}
	*/

	if(DEBUG) printf("Destroying Device...");
	ctl = ioctl(interface, UI_DEV_DESTROY);

}

int getKeyCodeFromChar( char in ) {
	in = tolower(in);
	switch(in) {
		case 'a': return KEY_A;
		case 'b': return KEY_B;
		case 'c': return KEY_C;
		case 'd': return KEY_D;
		case 'e': return KEY_E;
		case 'f': return KEY_F;
		case 'g': return KEY_G;
		case 'h': return KEY_H;
		case 'i': return KEY_I;
		case 'j': return KEY_J;
		case 'k': return KEY_K;
		case 'l': return KEY_L;
		case 'm': return KEY_M;
		case 'n': return KEY_N;
		case 'o': return KEY_O;
		case 'p': return KEY_P;
		case 'q': return KEY_Q;
		case 'r': return KEY_R;
		case 's': return KEY_S;
		case 't': return KEY_T;
		case 'u': return KEY_U;
		case 'v': return KEY_V;
		case 'w': return KEY_W;
		case 'x': return KEY_X;
		case 'y': return KEY_Y;
	}
	return KEY_UNKNOWN;
}
