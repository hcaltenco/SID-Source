/* Accelerometer:
* Receive input from a 3-axis device, and perform some useful calculations.
*
* Specify the three axis pins, and the VCC and GND pins, using analog pin
* numbers.  These are usually adjacent on the common breakout boards.
*
* Call the accelerometer's update() method occasionally to update the
* current values from the hardware.
*
* Get the axis acceleration features with the axis() method, or other useful
* calculations such as milligee(), pitch() and roll().
*
* Note that some functions like pitch() and roll() use floating point math,
* and can therefore really increase the size of the program on the chip.
* You can save about 2000 bytes if you don't need any floating point math.
*/

#ifndef Accelerometer_h
#define Accelerometer_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Accelerometer
{
public:
	Accelerometer(int pinX, int pinY, int pinZ, int pinVCC, int pinGND);
	Accelerometer(int pinX, int pinY, int pinZ);
	~Accelerometer();

	void update();
	void dump();
	void calibrate();
	void calibrate(int axis);
	void calibrate(int axis, int newscale);
	int milligee();
	int accel(int axis);
	int roll();
	int pitch();

private:
	int p[3]; // which analog pins
	int a[3]; // acceleration, zero-based
	int b[3]; // acceleration bias/calibration information
	int g, t, r; // cached copies of calculations
	int scale; // scaling factor between ADC and gravity

};

#endif