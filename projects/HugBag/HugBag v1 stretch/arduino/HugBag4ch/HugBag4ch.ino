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

// select the input pin for the sensors
int sPins[] = {A0, A1, A2, A3};
const int nSens = sizeof(sPins)/sizeof(int);
int cal_val[nSens];

int LO_THRES = 50;
int HI_THRES = 250;

// Pin S is not really used in this demo since it doesnt use the built in PWM fade
// The last argument is the number of LEDs in the strip. Each chip has 2 LEDs, and the number
// of chips/LEDs per meter varies so make sure to count them! if you have the wrong number
// the strip will act a little strangely, with the end pixels not showing up the way you like
HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, 32);


void setup(void) {
  Serial.begin(9600);
  calibrate();
}

void loop(void) {
  // check the most loose sensor and its value
  int val[nSens];
  int minVal = 0;
  int minSens = nSens;
  for (int i=0; i<nSens; i++) {
    int raw_val = analogRead(sPins[i]);    // read the value from the sensor 
    val[i] = cal_val[i] - raw_val; //map(raw_val, 0, 512, 0, 255); //map it for a max of 255
    if (val[i] > minVal) {
      minVal = val[i];
      minSens = i;
    }
    // print all sensors info
    Serial.print(val[i]);
    Serial.print('\t');
  }
  Serial.println(); // print in serial port
  
  // choose the color depending on which sensor is loose
  int sensColor = chooseColor(minSens);
  
  // color the ledstrip
  if (minVal > HI_THRES) {
    //rainbowParty(60);
    //cal_val[minSens]--;
  }
  else if (minVal > LO_THRES) {
    //chaseSingle (sensColor, 3000/minVal);
    //cal_val[minSens]--;
  }
  else {
    // adjust calibration if not touched
    for (int i=0; i<nSens; i++) {
      if (val[i] < -LO_THRES/2) {
        cal_val[i]++;
      }
      else if (val[i] > LO_THRES/2) {
        cal_val[i]--;
      }
    }
    // turn led strip off
    stripOff();
    delay(100);
  }
  
}

/**********************************************/

void calibrate() {
  for (int i=0; i<nSens; i++) {
    cal_val[i] = analogRead(sPins[i]);    // read the value from the sensor 
  }
}

/**********************************************/

int chooseColor(int minSens){
  int sensColor;
  switch(minSens) {
    case 0:
      sensColor = RED;
      break;
    case 1:
      sensColor = YELLOW;
      break;
    case 2:
      sensColor = GREEN;
      break;
    case 3:
      sensColor = BLUE;
      break;
  }
  return sensColor;
}

