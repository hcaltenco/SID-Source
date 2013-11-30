/* Pummer:
* A simple RGB color-interpolating helper class.
*
* When creating one, tell it which three output pins to drive PWM signals.
* If your RGB device is common-anode, it can reverse the PWM for you.
* Don't forget to limit current to each LED with a resistor (e.g., 220ohm).
*
* At any time, tell it what color to become by calling the goal() method,
* and how fast to transition to that color.
*
* Call the pummer's loop() method occasionally to let it set the PWM
* outputs to the LEDs.
*/

#ifndef Pummer_h
#define Pummer_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Pummer
{
public:
	Pummer(int pinR, int pinG, int pinB, bool anode=false);
	~Pummer();

	void show();
	boolean done();
	void goal(byte r, byte g, byte b, int speed=500);
	void loop();

private:
	byte lR, lG, lB;
	byte nR, nG, nB;
	byte wR, wG, wB;
	int pR, pG, pB;
	unsigned long last, when;
	boolean reverse;
};
#endif