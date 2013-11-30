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
 * If you wire a button from ground to pin 8, you can press it
 * once when the device is at rest on a level table, to get
 * somewhat better calibration data.  We do not try to save the
 * calibration into EEPROM, but that would be handy for more
 * permanent uses of an accelerometer.
 *
 * Released (cc) Creative Commons Attribution Only
 * Ed Halley
 * [ e d @ h a l l e y . c c ]
 *
 */

#include <Accelerometer.h>
#include <Pummer.h>

void loop() { ; } // we do our own loop below

void setup()
{
    Serial.begin(9600);

    boolean grow = true;
    int anger = 0;
    Pummer pummer = Pummer(5, 6, 3, true);
    Accelerometer accel = Accelerometer(3, 2, 1, 5, 4);

    pinMode(8, INPUT); digitalWrite(8, HIGH); // internal pullup

    int div = 0;
    while (1)
    {
        delay(20);
        accel.update();
        if (LOW == digitalRead(8))
            accel.calibrate();
        if (--div <= 0) { div = 8; accel.dump(); } // print every 8th loop

        // get more and more annoyed at high gee forces,
        // get instantly annoyed at zero gee force (freefall),
        // fall back asleep at normal gee forces
        //
        if (accel.milligee() > 1800)
            anger += 5;
        else if (accel.milligee() < 200)
            anger = 255;
        else if (accel.milligee() < 1100)
            anger -= 1;
        anger = max(0, min(anger, 255));

        // show the state of mind with our pummer
        pummer.loop();
        if (pummer.done())
        {
            grow = !grow;
            if (grow)
                pummer.goal(anger, 64, 64-anger/4, 350-anger);
            else
                pummer.goal(anger/2, anger/4, 128-anger/2, 2000-anger*7);
        }
    }
}
