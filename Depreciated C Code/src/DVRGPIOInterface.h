#include <stdio.h>
#include <wiringPi.h>

#define OEPINCOUNT 4
#define BUTTONPINCOUNT 8
#define LIGHTCOUNT 23

#define CLOCKPIN 9
#define DATAPIN 8

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

