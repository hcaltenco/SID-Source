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

#include "Pummer.h"

Pummer::Pummer(int pinR, int pinG, int pinB, bool anode)
{
	pinMode(pR = pinR, OUTPUT);
	pinMode(pG = pinG, OUTPUT);
	pinMode(pB = pinB, OUTPUT);
	nR = nG = nB = 0;
	reverse = anode;
	show();
	goal(255, 255, 255);
}

Pummer::~Pummer()
{
	//Empty destructor
}

void Pummer::show()
{
	analogWrite(pR, reverse? (255-nR) : nR);
	analogWrite(pG, reverse? (255-nG) : nG);
	analogWrite(pB, reverse? (255-nB) : nB);
}

boolean Pummer::done()
{
	return last == when;
}

void Pummer::goal(byte r, byte g, byte b, int speed)
{
	lR = nR; lG = nG; lB = nB;
	wR = r; wG = g; wB = b;
	last = millis();
	when = last + speed;
}

void Pummer::loop()
{
	unsigned long now = millis();
	if (now > when)
	{
		if (last == when)
			return;
		nR = wR; nG = wG; nB = wB;
		last = when;
	}
	else
	{
		nR = map(now, last, when, lR, wR);
		nG = map(now, last, when, lG, wG);
		nB = map(now, last, when, lB, wB);
	}
	show();
}