#include <stdio.h>
#include <wiringPi.h>

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#include <linux/input.h>
#include <linux/uinput.h>

#define UINPUT_MODULE_LOCATION "/dev/uinput"
#define MAX_KEY 226
#define BUFFER_KEY KEY_ENTER
#define BUFFER_SIZE 1
#define DEBUG 0

#define OEPINCOUNT 4
#define BUTTONPINCOUNT 8
#define LIGHTCOUNT 23

#define CLOCKPIN 9
#define DATAPIN 8
#define HDDPIN 7

int interface, ctl;
int key_blacklist[] = {0,84,120,181,182,195,196,197,198,199};

int OEOut[] = {7,0,2,3};
int ButtonsIn[] = {12,13,14,11,10,6,5,4};
int status[BUTTONPINCOUNT * OEPINCOUNT];
int lightStatus[LIGHTCOUNT];

void writeLights();
void setLight(int pin, int in);
int mapLight(int id);
void clearAllOE();
int mapkey(int oe, int qpin);
void updateGPIO();
void setupGPIO();

int getKeyCodeFromChar( char in );
int writeCode( int keycode, int status );
void toggleKey( int keycode );
void toggleChar( char in );

void initUINPUT();
void destroyUINPUT();
char mapKeyToChar(int in);

int main(int argc, char ** args) {
	setupGPIO();
	initUINPUT();
	while(1) {
		updateGPIO();
		delay(1);
	}
}

void initUINPUT() {
	if(DEBUG) printf("Opening Device...\n");
	interface = open(UINPUT_MODULE_LOCATION, O_WRONLY | O_NONBLOCK);
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
}

void destroyUNINPUT() {
	if(DEBUG) printf("Destroying Device...");
	ctl = ioctl(interface, UI_DEV_DESTROY);
}

void writeLights() {
	digitalWrite(CLOCKPIN, LOW);
	for(int i = LIGHTCOUNT; i >= 0; i--) {
		digitalWrite(DATAPIN, lightStatus[i]);
		digitalWrite(CLOCKPIN, HIGH);
		digitalWrite(CLOCKPIN, LOW);
	}
}

void setLight(int pin, int in) {
	if(pin < 0 || pin >= LIGHTCOUNT) return;
	lightStatus[pin] = in;
	writeLights();
}

int mapLight(int id) {
	if(id >= 16) {
		if(id <= 18) return(26 - id);
		if(id <= 23) return(id - 8);
		if(id <= 26) return(26 - id);
		if(id <= 31) return(id - 24);
	}
	return -1;
}

void clearAllOE() {
	for(int i = 0; i < OEPINCOUNT; i++)
		digitalWrite(OEOut[i], HIGH);
}

int mapkey(int oe, int qpin) {
	return (BUTTONPINCOUNT * oe) + qpin;
}

void updateGPIO() {
	for(int j = 0; j < OEPINCOUNT; j++) {
		clearAllOE();
		digitalWrite(OEOut[j], LOW);
		for(int k = 0; k < BUTTONPINCOUNT; k++) {
			if(k == 0) delayMicroseconds(1);
			int id = mapkey(j,k);
			int new = digitalRead(ButtonsIn[k]);
			if(status[id] != new) {
				status[id] = new;
				int lightId = mapLight(id);
				if(new) {
					if(DEBUG) printf("Button Up!  ");
					setLight(lightId, LOW);
					toggleChar('u');
				} else {
					if(DEBUG) printf("Button Down!");
					setLight(lightId, HIGH);
					toggleChar('d');
				}
				toggleChar( mapKeyToChar(id) );
				if(DEBUG) {
					printf(" (%d) [%d] <", id, lightId);
					for(int i = 0; i < LIGHTCOUNT; i++) {
						printf("%d", lightStatus[i]);
					}
					printf("> \n");
				}
			}
		}
	}
}

void setupGPIO() {
	wiringPiSetup();
	pinMode(HDDPIN, OUTPUT);
	digitalWrite(HDDPIN, HIGH);
	for(int i = 0; i < OEPINCOUNT; i++) {
		pinMode(OEOut[i], OUTPUT);
	}
	clearAllOE();
	for(int i = 0; i < BUTTONPINCOUNT; i++) {
		int pin = ButtonsIn[i];
		pinMode(pin, INPUT);
		pullUpDnControl(pin, PUD_DOWN);
	}
	pinMode(DATAPIN, OUTPUT);
	pinMode(CLOCKPIN, OUTPUT);
	for(int i = 0; i < BUTTONPINCOUNT * OEPINCOUNT; i++) {
		status[i] = HIGH;
	}
	for(int i = 0; i < LIGHTCOUNT; i++) {
		lightStatus[i] = LOW;
	}
	delay(10);
	setLight(22, HIGH);
	delay(10);
	writeLights();
}

void toggleChar( char in ) {
	toggleKey( getKeyCodeFromChar( in ) );
}

void toggleKey( int keycode ) {
	writeCode( keycode, 1 );
	writeCode( keycode, 0 );
	for( int i = 0; i < BUFFER_SIZE; i++) {
		writeCode( BUFFER_KEY, 1 );
		writeCode( BUFFER_KEY, 0 );
	}
}


int writeCode( int keycode, int status ) {
	struct input_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = EV_KEY;
	ev.code = keycode;
	ev.value = status;
	return write( interface, &ev, sizeof(ev) );
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
		case 'z': return KEY_Z;

		case '1': return KEY_1;
		case '2': return KEY_2;
		case '3': return KEY_3;
		case '4': return KEY_4;
		case '5': return KEY_5;
		case '6': return KEY_6;
		case '7': return KEY_7;
		case '8': return KEY_8;
		case '9': return KEY_9;
		case '0': return KEY_0;
 	}
	return KEY_UNKNOWN;
}

char mapKeyToChar(int in) {
	switch(in) {
		case 0: return '1';
		case 1: return 'v';
		case 2: return 'u';
		case 3: return '2';
		case 4: return '0';
		case 5: return '4';
		case 6: return '3';
		case 7: return '5';
		case 8: return 'r';
		case 9: return 'w';
		case 10: return 'q';
		case 11: return 'x';
		case 12: return 's';
		case 13: return 'y';
		case 14: return 't';
		case 15: return 'z';
		case 16: return 'f';
		case 17: return 'm';
		case 18: return 'e';
		case 19: return 'n';
		case 20: return 'g';
		case 21: return 'o';
		case 22: return 'h';
		case 23: return 'p';
		case 24: return 'b';
		case 25: return 'i';
		case 26: return 'a';
		case 27: return 'j';
		case 28: return 'c';
		case 29: return 'k';
		case 30: return 'd';
		case 31: return 'l';
	}
	return ' '; //fail if id out of above ranges
}
