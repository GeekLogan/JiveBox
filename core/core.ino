/*
    Author: Logan Walker (GeekLogan)
 Date: 30 January 2015
 Version: 0.01 Pre-Alpha
 Description: Do some stuff with sound
 */

//define constants using define for compiler-level simplification

#define ledPin 13 //Pin for output LED
#define analogInPos 0 //Pin for positive half of analog input
#define analogInNeg 1 //Pin for negitive half of analog input
#define digitalOutPos 5 //Pin for positive half of digital output (PWM)
#define digitalOutNeg 6 //Pin for negitive half of digital output (PWM)

int inPos = 0;
int inNeg = 0; 
int outPos = 0;
int outNeg = 0;

void setup() {
  // declare the ledPin as an OUTPUT
  pinMode(ledPin, OUTPUT);  
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  analogReference(INTERNAL);
  delay(1000);
  digitalWrite(ledPin, LOW);
  Serial.println("Code is setup!");  
}

void loop() {
  inPos = analogRead(analogInPos);
  inNeg = analogRead(analogInNeg);

  //Add Sound Edit Code Here
  outPos = inPos;
  outNeg = inNeg;

  analogWrite(digitalOutPos, outPos / 4);
  analogWrite(digitalOutNeg, outNeg / 4);
}

