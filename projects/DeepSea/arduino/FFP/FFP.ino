#include <3DPro.h>
#include <FFPJoystick.h>
#include <includes.h>


FFPJoystick myTest;

boolean autocenterset = false;

int wavelength = 33;
int effectID = 0;

boolean shouldContinue = true;


void setup()
{
//sei();
myTest.SetupHardware();
//myTest.EnableAutoCenter();
delay(1000);
//myTest.forceTest();
//Serial.print("started");//calling Serial.print seems to screw things up here
}
void loop()
{
  myTest.Poll();
delay(100);
if(myTest.Button == 1)
{
        wavelength++;
}
if(myTest.Button > 1)
{
     wavelength--;
}
      wavelength = constrain(wavelength, 0, 127);
      if(effectID != 2)
        effectID = myTest.forceTest(wavelength);
      else
        myTest.updateWaveLength(effectID,wavelength);
        Serial.print(wavelength);
        Serial.println();
    delay(1000);        

  /*  if(!autocenterset && myTest.X > 400)
    {
      myTest.EnableAutoCenter();
      autocenterset = true;
    }
    if(autocenterset && myTest.X <= 400)
    {
      myTest.DisableAutoCenter();
      autocenterset = false;
    }*/
}

