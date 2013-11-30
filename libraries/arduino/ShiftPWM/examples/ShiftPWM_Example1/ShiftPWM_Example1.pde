/******************************************************************************
 * This example shows how to use the ShiftPWM library to PWM many outputs.
 * All shift registers are chained, so they can be driven with 3 pins from the arduino.
 * A timer interrupt updates all PWM outputs according to their duty cycle setting.
 * The outputs can be inverted by making ShiftPWM_invertOutputs true.
 * 
 * How the library works:
 * The ShiftPWM class keeps a setting for the duty cycle for each output pin, which
 * can be set using the provided functions. It also keeps a counter which it compares 
 * to these duty cycles. This timer continuously runs from 0 to the maximum duty cycle.
 * 
 * A timer interrupt is configured by ShiftPWM.Start(pwmFrequency,maxBrightness).
 * The interrupt frequency is set to pwmFrequency * (maxBrightness+1).
 * Each interrupt all duty cycles are compared to the counter and the corresponding pin
 * is written 1 or 0 based on the result. Then the counter is increased by one.
 * 
 * The duration of the interrupt depends on the number of shift registers (N).
 * T = 112 + 43*N 
 * 
 * The load of the interrupt function on your program can be calculated:
 * L = Interrupt frequency * interrupt duration / clock frequency
 * L = F*(Bmax+1)*(112+43*N)/F_CPU
 * Quick reference for load:
 * 3 registers  255 maxBrightness 75Hz  load = 0.29
 * 6 registers  255 maxBrightness 75Hz  load = 0.45
 * 24 registers 100 maxBrightness 75Hz  load = 0.54
 * 48 registers  64 maxBrightness 75Hz  load = 0.66
 * 96 registers  32 maxBrightness 75Hz  load = 0.66
 * 
 * A higher interrupt load will mean less computional power for your main program,
 * so try to keep it as low as possible and at least below 0.9.
 * 
 * The following functions are used:
 * 
 * ShiftPWM.Start(int ledFrequency, int max_Brightness)		Enable ShiftPWM with desired frequency and brightness levels
 * ShiftPWM.SetAmountOfRegisters(int newAmount)			Set or change the amount of output registers. Can be changed at runtime.
 * ShiftPWM.PrintInterruptLoad()				Print information on timer usage, frequencies and interrupt load
 * ShiftPWM.OneByOneSlow()  				        Fade in and fade out all outputs slowly
 * ShiftPWM.OneByOneFast()					Fade in and fade out all outputs fast
 * ShiftPWM.SetOne(int pin, unsigned char value)		Set the duty cycle of one output
 * ShiftPWM.SetAll(unsigned char value)				Set all outputs to the same duty cycle
 * 
 * ShiftPWM.SetGroupOf2(int group, unsigned char v0, unsigned char v1);
 * ShiftPWM.SetGroupOf3(int group, unsigned char v0, unsigned char v1, unsigned char v2);
 * ShiftPWM.SetGroupOf4(int group, unsigned char v0, unsigned char v1, unsigned char v2, unsigned char v3);
 * ShiftPWM.SetGroupOf5(int group, unsigned char v0, unsigned char v1, unsigned char v2, unsigned char v3, unsigned char v4);
 * 		--> Set a group of outputs to the given values. SetGroupOf3 is useful for RGB LED's. Each LED will be a group.
 * 
 * Debug information for wrong input to functions is also send to the serial port,
 * so check the serial port when you run into problems.
 * 
 * (c) Elco Jacobs, E-atelier Industrial Design TU/e, July 2011.
 * 
 *****************************************************************************/
//#include <Servo.h>
#include <SPI.h>
#include "hsv2rgb.h"


//Data pin is MOSI (atmega168/328: pin 11. Mega: 51) 
//Clock pin is SCK (atmega168/328: pin 13. Mega: 52)
const int ShiftPWM_latchPin=8;
const bool ShiftPWM_invertOutputs = 1; // if invertOutputs is 1, outputs will be active low. Usefull for common anode RGB led's.

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!


unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 6;

void setup()   {                
  pinMode(ShiftPWM_latchPin, OUTPUT);  
  SPI.setBitOrder(LSBFIRST);
  // SPI_CLOCK_DIV2 is only a tiny bit faster in sending out the last byte. 
  // SPI transfer and calculations overlap for the other bytes.
  SPI.setClockDivider(SPI_CLOCK_DIV4); 
  SPI.begin(); 

  Serial.begin(9600);


  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.Start(pwmFrequency,maxBrightness);  
}



void loop()
{    
  // Print information about the interrupt frequency, duration and load on your program
  ShiftPWM.SetAll(0);
  ShiftPWM.PrintInterruptLoad();

  // Fade in and fade out all outputs one by one fast. Usefull for testing your circuit
  ShiftPWM.OneByOneFast();

  // Fade in all outputs
  for(int j=0;j<maxBrightness;j++){
    ShiftPWM.SetAll(j);  
    delay(20);
  }
  // Fade out all outputs
  for(int j=maxBrightness;j>=0;j--){
    ShiftPWM.SetAll(j);  
    delay(20);
  }

  // Fade in and out 2 outputs at a time
  for(int output=0;output<numRegisters*8-1;output++){
    ShiftPWM.SetAll(0);
    for(int brightness=0;brightness<maxBrightness;brightness++){
      ShiftPWM.SetOne(output+1,brightness);
      ShiftPWM.SetOne(output,maxBrightness-brightness);
      delay(1);
    }
  }

  //  A moving rainbow for RGB leds:
  rgbLedRainbow(numRegisters*8/3, 5, 3, maxBrightness, numRegisters*8/3); // Fast, over all LED's
  rgbLedRainbow(numRegisters*8/3, 10, 3, maxBrightness, numRegisters*8/3*4); //slower, wider than the number of LED's

  // Fade in and fade out all outputs slowly. Usefull for testing your circuit
  ShiftPWM.OneByOneSlow();  
}

void rgbLedRainbow(int numRGBLeds, int delayVal, int numCycles, int maxBrightness, int rainbowWidth){
  // Displays a rainbow spread over all LED's, which shifts in hue.
  int hue, sat, val; 
  unsigned char red, green, blue;

  ShiftPWM.SetAll(0);
  for(int cycle=0;cycle<numCycles;cycle++){ // shift the raibom numCycles times
    for(int colorshift=0;colorshift<360;colorshift++){ // Shift over full color range (like the hue slider in photoshop)
      for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
        hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
        sat = 255;
        val = 255;
        hsv2rgb(hue, sat, val, &red, &green, &blue, maxBrightness); // convert hsv to rgb values
        ShiftPWM.SetGroupOf3(led, red, green, blue); // write rgb values
      }
      delay(delayVal);
    } 
  }  
}


