/* ****************************************************

Arduino code for Malleable Pillow
Hector Caltenco
Certec, LTH
2013-03-25

**************************************************** */

#include "SPI.h"
#include "WS2801.h"

// use -any- 3 pins!
#define STRIP_D 2 //4
#define STRIP_C 3 //3
#define n_leds 20
#define n_ledgroups 5

int micPins[] = {A0, A1, A2, A3, A6, A7, A9};

const int n_mics = sizeof(micPins)/sizeof(int);
int analogValue[n_mics];
int base[n_mics];

//int n_ledgroups = round(n_leds/(n_mics));
int ledgroup[n_mics][n_ledgroups] = {{0,1,2,3,4},{3,4,9,10,10},{9,10,11,12,13},{12,13,17,18,19},{13,14,15,16,17},{7,8,13,14,15},{5,6,7,8,0}};

int MIN_TIME_ON = 100; // minimum time for the led to be on
//int THRES = 90;
int THRESHOLD[] = {100, 70, 100, 80, 100, 90, 70};

int ANGER_SPEED = 10;
int FADE_SPEED = 5;

WS2801 strip = WS2801(n_leds, STRIP_D, STRIP_C);

void setup() {                
  Serial.begin(19200);//9600);
  strip.begin();
  strip.show(); // turn off leds
}

void loop() {
  static unsigned long time_on[n_mics];
  static byte anger[n_mics];
  
  /* read microphone levels and find the most active mic */
  int maxVal = 0;
  int iMax;
  for (int i = 0; i < n_mics; i++) {
    int sensValue = analogRead(micPins[i]);
    base[i] = 0.8 * base[i] + 0.2 * sensValue;
    analogValue[i] = constrain(sensValue - base[i], -512, 512);
    
    /* find the most active microphone */
    if (abs(analogValue[i]) > maxVal) {
      maxVal = abs(analogValue[i]);
      iMax = i;
    }
  }
  
  /* turn leds of active mic if over threshold */
  if (abs(analogValue[iMax]) > THRESHOLD[iMax]) {
    // turn on red led fast
    anger[iMax] = constrain(anger[iMax] + ANGER_SPEED*abs(analogValue[iMax])/THRESHOLD[iMax], 0, 255);
    // timestamp
    time_on[iMax] = millis();
  }
  
  /* display led 'i' status */
  for (int i=0; i<n_mics; i++) {
    // turn leds down slowly
    if ((millis() - time_on[i]) > MIN_TIME_ON) {
      anger[i] = constrain(anger[i] - FADE_SPEED, 0, 255);
    }
    // send values through serial
    Serial.print(analogValue[i], DEC);
    Serial.print(",\t");
    Serial.print(anger[i], DEC);
    Serial.print(";\t");
  }
  Serial.println();

  // Anger leds for most activated mi
  for (int j=0; j<n_ledgroups; j++) { 
    if (anger[iMax] > 200) {
      strip.setPixelColor(ledgroup[iMax][j], anger[iMax], 1000-anger[iMax]*4, 0);
      }
    else if (anger[iMax] > 150) {
      strip.setPixelColor(ledgroup[iMax][j], anger[iMax]*4-600, anger[iMax], 0);
    }
    else if (anger[iMax] > 100) {
      strip.setPixelColor(ledgroup[iMax][j], 0, anger[iMax], 300-anger[iMax]*2);
    }
    else if (anger[iMax] > 50) {
      strip.setPixelColor(ledgroup[iMax][j], 0, anger[iMax]*2-100, anger[iMax]);
    }
    else {
      strip.setPixelColor(ledgroup[iMax][j], 0, 0, anger[iMax]);
    }
  }
  
  // show the ledstrip colors
  strip.show();
  // pause for 10 milliseconds:
  delay(10);
}

