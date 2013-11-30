/*
All 6 analog input pins are available. They can also be used as digital pins (pins #14 thru 19)
 
 Digital pin 2, and 13 are not used.
 
 The following pins are in use only if the DC/Stepper noted is in use:
 Digital pin 11: DC Motor #1 / Stepper #1 (activation/speed control)
 Digital pin 3: DC Motor #2 / Stepper #1 (activation/speed control)
 Digital pin 5: DC Motor #3 / Stepper #2 (activation/speed control)
 Digital pin 6: DC Motor #4 / Stepper #2 (activation/speed control)
 
 The following pins are in use if any DC/steppers are used
 Digital pin 4, 7, 8 and 12 are used to drive the DC/Stepper motors via the 74HC595 serial-to-parallel latch
 
 The following pins are used only if that particular servo is in use:
 Digitals pin 9: Servo #1 control
 Digital pin 10: Servo #2 control
 */

#include <AFMotor.h>

AF_Stepper motor(200, 2);

void setup()
{
  Serial.begin(9600);
  motor.setSpeed(250);  /* <-- HENRIK: Her ændres hastigheden på motoren (0-255)*/
}

boolean fullRead = false;
int index = 0;
int dataIn[8];

void loop()
{
  while (Serial.available())
  {
    byte b = Serial.read();
    if(b == '\n')
    {
      fullRead = true;
      index = 0;
      break;
    } 
    else
    {
      if (b != 0)
        dataIn[index] = map(b, 1, 255, 1, 20);
      else
        dataIn[index] = b;
      index++;
    }
  }

  if(fullRead)
  {
    fullRead = false;
    if(dataIn[0] > 0)
    {
      //motor.setSpeed(dataIn[0]);
      //motor.step(1, FORWARD, DOUBLE);
      motor.step(dataIn[0], FORWARD, DOUBLE);
    }
    if(dataIn[0] < 0)
    {
      //motor.setSpeed(-1*dataIn[0]);
      //motor.step(1, BACKWARD,DOUBLE);
      motor.step(-1*dataIn[0], BACKWARD,DOUBLE);
    }
    if(dataIn[0] == 0)
    {
      motor.release();
    }
  }
}

