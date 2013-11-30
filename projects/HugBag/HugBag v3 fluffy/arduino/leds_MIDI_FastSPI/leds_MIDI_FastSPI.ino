#include <Accelerometer.h>
#include <MIDI.h>
//#include <TimerOne.h>
//#include <LPD6803.h>
#include <FastSPI_LED.h>
//#include <Encoder.h>
#include "hsv2rgb.h"
#include "ledpos.h"
 
#define FADESPEED   1// make this higher to slow down
#define FILTERSPEED 0.5

#define MIDICHO     1
#define PITCH_CTRL  4
#define ROLL_CTRL   5

//#define ENC_A 2 //14 
//#define ENC_B 3 //15


//int rot_counter = 0;
//int slow_counter = 0;

long timesincetouch = 0;

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
//const int dataPin = 2;       // 'yellow' wire
//const int clockPin = 3;      // 'green' wire
const int nLEDs = 100;

// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

// Set the first variable to the NUMBER of pixels. 20 = 20 pixels in a row
// Timer 1 is also used by the strip to send pixel clocks
//LPD6803 strip = LPD6803(nLEDs, dataPin, clockPin);

// create our local ledcolor array
byte mystrip[nLEDs][3];
byte color[] = {63,63,63};

//Setup the accelerometer
Accelerometer accel = Accelerometer(2, 1, 0, 4, 3);

//Encoder myEnc(ENC_A, ENC_B);

void setup() {
  // start with 50% CPU usage. up this if the strand flickers or is slow
  /*strip.setCPUmax(75);  
  strip.begin();
  strip.show();
  */
  //pinMode(6,OUTPUT);
  //digitalWrite(6,LOW);
  
  FastSPI_LED.setLeds(nLEDs);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  FastSPI_LED.setCPUPercentage(10); // Optimal:50, Low number: faster, High Number: more colors
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
  
  MIDI.begin(); // Launch MIDI with default options
  MIDI.setHandleControlChange(HandleControlChange);  // Connect the Handle function to the library
  Serial.begin(115200);         // can be up to 256000

  accel.calibrate(2, 67); // calibrate on z axis compensating for 3G -> 100*2/3
}
 
 
void loop() {
  
  // read the encoder position and sensor data
  //encoder();
  
  MIDI.read();
  accel.update();
  
  //send accelerometer data to control change
  //sendAccelData();
  
  // fade gradually if no MIDI control changes recieved
  if (millis() - timesincetouch > 10) {
    for (int i = 0; i < nLEDs; i++) {
      for (int c = 0; c < 3; c++) {
        if (mystrip[i][c] > 0){
          mystrip[i][c] -= 1;
        }
      }
    }
  }
  
  //accel.dump();
  writeLEDs();
  delay(FADESPEED);
}

void HandleControlChange(byte channel, byte number, byte value) {
  timesincetouch = millis();
  
  // value comes from 0 to 127
  static int hue = 0;   //0-360
  static byte sat = 255; //0-255
  static byte val = 255; //0-255
  
  static byte ledPos[] = {0,0};
  static byte d = 0;
  float x;
  
  
  static byte r, g, b;
  
  // Do whatever you want when you receive a Control Change.
  switch (number) {
    case 1: // X
      //sat = map(value, 0, 127, 128, 255) * FILTERSPEED + sat * (1-FILTERSPEED);
      ledPos[0] = value * FILTERSPEED + ledPos[0] * (1-FILTERSPEED);
      break;
    case 2: // Y
      //hue = map(value, 0, 127, 0, 360) * FILTERSPEED + hue * (1-FILTERSPEED);
      ledPos[1] = value * FILTERSPEED + ledPos[1] * (1-FILTERSPEED);
      break;
    case 3: //size (A)
      //val = map(value, 0, 127, 64, 255) * FILTERSPEED + val * (1-FILTERSPEED);
      //d = value * FILTERSPEED + d * (1-FILTERSPEED);
      x = sqrt(((float)value*127*127)/(100*3.1416));
      d = value * FILTERSPEED + d * (1-FILTERSPEED);
      break;
    case 8: // Total Volume
      val = map(value, 0, 127, 64, 255) * FILTERSPEED + val * (1-FILTERSPEED);
    case 4: 
      color[1] = value;
      break;
    case 5: 
      color[2] = value;
      break;
    case 6: 
      color[0] = value;
      break;
      
  }
  
  /*color[0] = 160;
  color[1] = g;
  color[2] = b;
  */
  for (int i = 0; i < nLEDs; i++) {
    if (abs(ledPos[0] - pos[i][0]) < d && abs(ledPos[1] - pos[i][1]) < d) {
      //hsv2rgb(hue, sat, val, &mystrip[i][0], &mystrip[i][1], &mystrip[i][2], 255); // convert hsv to rgb values
      for (int c = 0; c < 3; c++) {
        mystrip[i][c] = color[c];
        //Serial.print(color[c]);
        //Serial.print('\t');
      }
    }
    //Serial.println();
  }
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
  memset(leds, 0, nLEDs * 3);
  for (int i=0; i<nLEDs; i++) {
      leds[i].r = mystrip[i][0];
      leds[i].g = mystrip[i][1];
      leds[i].b = mystrip[i][2];
  }
  FastSPI_LED.show();
}

//--------------------------------------------------------------

/*void encoder() {
  long tmpdata = myEnc.read();
  if (tmpdata != rot_counter) {
    //last_counter = rot_counter;
    rot_counter = tmpdata;
    slow_counter = constrain(rot_counter/5, 0, 100);
    for (int i = 0; i < nLEDs; i++) {
      if (slow_counter == i)
        mystrip[i][1] = 200;
      else
        mystrip[i][1] = 0;
    }
      Serial.print("rot_counter: ");
      Serial.println(slow_counter, DEC);
    
  }
}
*/

//--------------------------------------------------------------

