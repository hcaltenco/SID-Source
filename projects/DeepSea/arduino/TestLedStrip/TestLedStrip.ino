
//#include <CapSense.h>
#include "hsv2rgb.h"
 
#define REDPIN    3
#define GREENPIN  6
#define BLUEPIN   5

#define FADESPEED   5     // make this higher to slow down
#define FILTERSPEED 0.8

#define MINTHRES   3000
#define MAXTHRES   10000

byte ledstrip[3] = {0};
long capValue = 0;
long capBase = 0;

//CapSense cs = CapSense(4,2);

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //cs.set_CS_Timeout_Millis(200);
  
  //capBase = cs.capSense(30);
  
  Serial.begin(115200);         // (input channel is default set to 1)
}
 
 
void loop() {
  static int hue;
  static byte val;
  static long capRaw;
 
  /*capRaw = cs.capSense(30) * 0.2 + 0.8 * capRaw;
  
  if (capRaw > capBase)
    capBase = 0.99 * capBase + 0.01 * capRaw;
  else
    capBase = 0.8 * capBase + 0.2 * capRaw;
  
  capValue = constrain(abs(capRaw - capBase), 0, MAXTHRES)*0.8 + capValue * 0.2;
  */
  if (capValue > MINTHRES) {
    //hue = constrain(map(capValue, MINTHRES, MAXTHRES, 0, 360), 0, 360);
    val = constrain(map(capValue, MINTHRES, MAXTHRES, 0, 255), 0, 255);
  }
  else {
    //hue = 0;
    val = 0;
  }
  
  hue = hue + capValue / MINTHRES;
  
  if (hue > 360)
    hue = hue % 360;
  
  hsv2rgb(hue, 255, val, &ledstrip[0], &ledstrip[1], &ledstrip[2], 255); // convert hsv to rgb values
  
  // fade gradually if no MIDI control changes recieved
  for (int i = 0; i < sizeof(ledstrip); i++) {
    if (ledstrip[i] > 0){
      ledstrip[i] = ledstrip[i] - 1;
    }
  }
  
  if (capValue > MAXTHRES) {
    capValue = MINTHRES;
  }
  else {
    capValue++;
  }
  
  //Serial.print(capRaw); Serial.print('\t');
  Serial.print(capValue); Serial.print('\t');
  //Serial.print(capBase); Serial.print('\t');
  Serial.print(hue);      Serial.print('\t');
  Serial.println(val);
  
  //accel.dump();
  writeLEDs();
  delay(FADESPEED);
}


void writeLEDs() {
  analogWrite(REDPIN,   ledstrip[0]);
  analogWrite(GREENPIN, ledstrip[1]);
  analogWrite(BLUEPIN,  ledstrip[2]);
}
