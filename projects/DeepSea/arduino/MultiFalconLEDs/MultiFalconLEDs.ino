#include <string.h>
#include "hsv2rgb.h"

#define REDPIN    6
#define GREENPIN  3
#define BLUEPIN   5

#define FADESPEED   10     // make this higher to slow down
#define FILTERSPEED 0.8

#define MIDICHO     1
#define PITCH_CTRL  4
#define ROLL_CTRL   5

byte ledstrip[3] = {0};
char fd[100]; //falcon data

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  Serial.begin(9600);         // (input channel is default set to 1)
}


void loop() {

  // fade gradually if no changes recieved
  for (int i = 0; i < sizeof(ledstrip); i++) {
    if (ledstrip[i] > 0){
      ledstrip[i] = ledstrip[i] - 1;
    }
  }

  // Display LED colors
  writeLEDs();
  delay(FADESPEED);
}

int recieveFalconData()
{
  //unsigned char c[100];
  unsigned int index = 0;
  int full_lines = 0;
    // send data only when you receive data:
  while(Serial.available()) {
    byte b = Serial.read();
    if(b == '\n')
    {
      full_lines++;
      index = 0;
      //break;
    } 
    else
    {
      fd[index] = b;
      index ++;
    }
  }
  
  if (full_lines > 0)
  {
    char *p = fd;
    char *str;
    while((str = strtok_r(p, ";", &p)) != NULL)
    {
      //Do something with the data
      if (str == 
    }
  }
  
  return full_lines;
}

void lightWithVector(byte x, byte y, byte z) {
  // value comes from 0 to 127
  static int hue = 0;   //0-360
  static byte sat = 255; //0-255
  static byte val = 255; //0-255

  double amp = sqrt((x*x)+(y*y));
  double theta = atan2(y, x);

  val = constrain(z,0,255);
  sat = constrain(amp,0,255);
  hue = constrain(theta*180/3.1415,0,360);
  /*
  if (val < 90)
    val = 0;
  if (hue > 359)
    hue = 0;
  */
  hsv2rgb(hue, sat, val, &ledstrip[0], &ledstrip[1], &ledstrip[2], 255); // convert hsv to rgb values
  /*Serial.print(hue);
  Serial.print("\t");
  Serial.print(sat);
  Serial.print("\t");
  Serial.print(val);
  Serial.println();*/
}

void writeLEDs() {
  analogWrite(REDPIN,   ledstrip[0]);
  analogWrite(GREENPIN, ledstrip[1]);
  analogWrite(BLUEPIN,  ledstrip[2]);
}

