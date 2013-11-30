/*
This is the HugBag code using HL1606-based digital LED strips. 
It uses my modified Adafruits HL1606strip library to control 
the addressable leds. Blue and green addresses are interchanged

The strip is controlled by analog read of a stretch sensor.

Hector Caltenco
SID project
2012-05-23
*/


// HL1606strip is an adaptation of LEDstrip from  http://code.google.com/p/ledstrip/
#include "HL1606strip.h"

// use -any- 3 pins!
#define STRIP_D 4
#define STRIP_C 3
#define STRIP_L 2

// select the input pin for the potentiometer
int potPin = A2;

// Pin S is not really used in this demo since it doesnt use the built in PWM fade
// The last argument is the number of LEDs in the strip. Each chip has 2 LEDs, and the number
// of chips/LEDs per meter varies so make sure to count them! if you have the wrong number
// the strip will act a little strangely, with the end pixels not showing up the way you like
HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, 32);


void setup(void) {
  Serial.begin(9600);
}

void loop(void) { 
  int raw_val = analogRead(potPin);    // read the value from the sensor 
  int val = map(raw_val, 0, 512, 0, 255); //map it for a max of 255
  
  Serial.println(val); // print in serial port
  
  if (val > 250) {
    // a colorcycle party!
    rainbowParty(60);
  }
  else if (val > 225) {
    chaseSingle(RED, 5000/val);
  }
  else if (val > 200) {
    chaseSingle(YELLOW, 5000/val);
  }
  else if (val > 175) {
    chaseSingle(GREEN, 5000/val);
  }
  else if (val > 150) {
    chaseSingle(TEAL, 5000/val);
  }
  else if (val > 125) {
    chaseSingle(BLUE, 5000/val);
  }
  else if (val > 100) {
    chaseSingle(VIOLET, 5000/val);
  }
  else if (val > 75) {
    chaseSingle(WHITE, 5000/val);
  }
  else {
    stripOff();
    delay(100);
    //chaseSingle(BLUE,5000/val);
  }
}

/**********************************************/



