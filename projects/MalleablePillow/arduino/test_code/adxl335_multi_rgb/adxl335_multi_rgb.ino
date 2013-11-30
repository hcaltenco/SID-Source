/*
 * Sleeping Arduino - unless you jostle it!
 *
 * If left alone, make a light pummer "snore" in peaceful colors.  If
 * agitated by shaking the device, breath faster in hotter colors.
 *
 * A basic example sketch that reads from analog three-pin three-axis
 * accelerometers, such as the common ADXL330 chip found at Seeedstudio
 * or SparkFun online vendors.
 *
 * In addition, this sketch outputs PWM signals to three LEDs, such as
 * a self-contained RGB LED package or three independently wired LEDs,
 * one each of red, green and blue suggested.
 *
 * Optionally, wiring a switch from digital pin 8 to ground will give
 * this sketch a chance to "calibrate" the accelerometer.  Not required
 * but useful, since every accelerometer varies slightly.
 *
 * Released (cc) Creative Commons Attribution Only
 * Ed Halley
 * [ e d @ h a l l e y . c c ]
 *
 */

#include <math.h>
//#include <Pummer.h>
#include <Accelerometer.h>
#include <MultiPWM.h>
//#include "hsv2rgb.h"

/*
 * Example Program
 *
 * Sleeping Arduino - unless you jostle it!
 *
 * If you wire a button from ground to pin 8, you can press it
 * once when the device is at rest on a level table, to get
 * somewhat better calibration data.  We do not try to save the
 * calibration into EEPROM, but that would be handy for more
 * permanent uses of an accelerometer.
 *
 */

boolean grow = true;
boolean use_anger = true;
boolean use_tilt = true;

//-----------------------------------------------------
/* calibration button configuration */
#define cal_pin 11
/* led array configuration */
#define ledBrightness 99
#define ledFreq 60
#define n_rgbs 3	// number of rgb leds

int r1 =  4, g1 = 2, b1 = 3;
int r2 =  7, g2 = 5, b2 = 6;
int r3 = 10, g3 = 8, b3 = 9;
int Pins[] = {r1,g1,b1,r2,g2,b2,r3,g3,b3};
//-----------------------------------------------------
/* no need to modify these */
unsigned long timer_start = 0;
int acc_byte[3];
int anger = 0;
int tilt = 0;
int div_prnt = 0;
int nPins = sizeof(Pins)/sizeof(int);
//-----------------------------------------------------
/* objects from library classes */
//Pummer pummer = Pummer(11,9,10,true); //(5, 6, 3, true);
//Pummer pummer = Pummer(4,2,3,true); //(5, 6, 3, true);
Accelerometer accel = Accelerometer(0, 1, 2); //(3,2,1,5,4);
MultiPWM myleds = MultiPWM(Pins, nPins, true);

//-----------------------------------------------------

void setup()
{
  Serial.begin(9600);

  /* the calibration button */
  pinMode(cal_pin, INPUT); 
  digitalWrite(cal_pin, HIGH); // internal pullup
  
  /* RGB led common annode pin 
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH); */
  
  myleds.Start(ledFreq, ledBrightness);
  myleds.SetAll(0);
}

//-----------------------------------------------------
void loop() {
  static int cycle_time;
  
  accel.update();
  if (LOW == digitalRead(cal_pin)) {
    accel.calibrate(2);
    Serial.println("device calibrated");
  }
  Serial.print("Anger: "); Serial.print(anger); Serial.print ("\t");
  accel.dump(); 
  
  /* use tilt (pitch or roll) angle to anger the device
   * get more and more annoyed at high pitch and roll angles,
   * fall back asleep at flat surface
   */
  if (use_tilt)
  {
    tilt = (int) sqrt(accel.pitch()*accel.pitch() + accel.roll()*accel.roll());
    if (tilt > 70)
      anger = (int) tilt * 2.5;
    else
      anger -= 5;
  }
  /* use acceleration changes to anger the device
   * get more and more annoyed at high gee forces,
   * get instantly annoyed at zero gee force (freefall),
   * fall back asleep at normal gee forces
   */
  else
  {
    if (accel.milligee() > 1800)
      anger += 25; //+5
    else if (accel.milligee() < 200)
      anger += 150; //=255
    else // if (accel.milligee() < 1100)
      anger -= 5; // -1
  }
  anger = max(0, min(anger, 255));

  /* show the state of mind with our pummer
   * if using anger warmer colors when angry (by tilting or jostling)
   * if not using anger, RGB color proportional to xyz acceleration vectors
   */
  if (anger) {
    //Increase speed of colorchanging
    //showAnger(1000-anger*2);
    //myleds.OneByOneSlow();
    rgbLedRainbow(3, (300-anger), 20, ledBrightness, 6);
    //rgbLedRainbow(3, 100, 20, 255, 6);
  }
  else {
//	delay(50);
    snore(8);
  }
}

//-----------------------------------------------------

ISR(TIMER1_COMPA_vect) {
	myleds.HandleInterrupt();
}
