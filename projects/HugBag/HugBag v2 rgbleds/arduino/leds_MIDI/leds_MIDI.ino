#include <Accelerometer.h>
#include <MIDI.h>
#include "hsv2rgb.h"
 
#define REDPIN    5
#define GREENPIN  3
#define BLUEPIN   6

#define FADESPEED   5     // make this higher to slow down
#define FILTERSPEED 0.8

#define MIDICHO     1
#define PITCH_CTRL  4
#define ROLL_CTRL   5

byte ledstrip[3] = {0};

//Accelerometer accel = Accelerometer(2, 1, 0);
Accelerometer accel = Accelerometer(2, 1, 0, 4, 3);

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  MIDI.begin(); // Launch MIDI with default options
  MIDI.setHandleControlChange(HandleControlChange);  // Connect the Handle function to the library
  Serial.begin(115200);         // (input channel is default set to 1)

  accel.calibrate(2, 67); // calibrate on z axis compensating for 3G -> 100*2/3
}
 
 
void loop() {
  MIDI.read();
  accel.update();
  
  //send accelerometer data to control change
  sendAccelData();
  
  // fade gradually if no MIDI control changes recieved
  for (int i = 0; i < sizeof(ledstrip); i++) {
    if (ledstrip[i] > 0){
      ledstrip[i] = ledstrip[i] - 1;
    }
  }
  
  //accel.dump();
  writeLEDs();
  delay(FADESPEED);
}

void HandleControlChange(byte channel, byte number, byte value) { 
  // value comes from 0 to 127
  static int hue = 0;   //0-360
  static byte sat = 255; //0-255
  static byte val = 255; //0-255
  
  // Do whatever you want when you receive a Control Change.
  switch (number) {
    case 3: //depth
      val = map(value, 0, 127, 64, 255) * FILTERSPEED + val * (1-FILTERSPEED); 
      break;
    case 1: // amplitude
      sat = map(value, 0, 127, 128, 255) * FILTERSPEED + sat * (1-FILTERSPEED);
      break;
    case 2: // phase
      hue = map(value, 0, 127, 0, 360) * FILTERSPEED + hue * (1-FILTERSPEED);
      break;
  }
  
  hsv2rgb(hue, sat, val, &ledstrip[0], &ledstrip[1], &ledstrip[2], 255); // convert hsv to rgb values

}

void sendAccelData() {
  byte midiPitch = abs(map(accel.pitch(), -90, 90, -127, 127));
  byte midiRoll =  abs(map(accel.roll() , -90, 90, -127, 127));
  
  if (midiPitch > 3)
    MIDI.sendControlChange(PITCH_CTRL, midiPitch, MIDICHO);
  if (midiRoll > 3)
    MIDI.sendControlChange(ROLL_CTRL,  midiRoll,  MIDICHO);

}
void writeLEDs() {
  analogWrite(REDPIN,   ledstrip[0]);
  analogWrite(GREENPIN, ledstrip[1]);
  analogWrite(BLUEPIN,  ledstrip[2]);
}
