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
#include <Pummer.h>
#include <Accelerometer.h>
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
boolean use_anger = false;
boolean use_tilt = true;
int acc_byte[3];
int anger = 0;
int tilt = 0;
int div_prnt = 0;

Pummer pummer = Pummer(6,3,5,true); //(5, 6, 3, true);
Accelerometer accel = Accelerometer(0, 1, 2); //(3,2,1,5,4);

//-----------------------------------------------------
void setup()
{
  Serial.begin(9600);

  /* the calibration button */
  pinMode(8, INPUT); 
  digitalWrite(8, HIGH); // internal pullup
  
  /* RGB led common annode pin */
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH); 
}
//-----------------------------------------------------
void loop() { 
  delay(20);
  accel.update();
  if (LOW == digitalRead(8))
    accel.calibrate();
  if (--div_prnt <= 0) { 
    div_prnt = 8; 
    accel.dump(); 
  } // print every 8th loop

  /* use tilt (pitch or roll) angle to anger the device
   * get more and more annoyed at high pitch and roll angles,
   * fall back asleep at flat surface
   */
  if (use_tilt)
  {
    tilt = (int) sqrt(accel.pitch()*accel.pitch() + accel.roll()*accel.roll());
    if (tilt > 50)
      anger = (int) tilt * 2.5;
    else
      anger -= 1;
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
  pummer.loop();
  if (pummer.done())
  {
    grow = !grow;
    if (use_anger)
    {
      if (grow)
        pummer.goal(anger, 64, 64-anger/4, 260-anger);
      else
        pummer.goal(anger/2, anger/4, 128-anger/2, 1790-anger*7);
    }
    else
    {
      for (int i=0; i<3; i++) {
        if (abs(accel.accel(i)) > 25)
          acc_byte[i] = (int) abs(accel.accel(i))*2.5;
        else
          acc_byte[i] = 0;
      }
      /*if (grow)
       pummer.goal(acc_byte[0], acc_byte[1], acc_byte[2], 350-anger);
       else
       pummer.goal(acc_byte[0], acc_byte[1], acc_byte[2], 2000-anger*7); */
      pummer.goal(acc_byte[0], acc_byte[1], acc_byte[2], 25);
    }
  } 
}

