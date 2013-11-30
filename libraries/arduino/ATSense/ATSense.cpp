/*
 ATSense.c v.01 - Arduino Touché Sensing Library based on:
 Advanced Touch Sensing Program by DZL: 
 http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/
 -------------------------------------------------------------------
 Library Modification by Héctor Caltenco - Arduino 1.0 compatibility
 
 ****************************************************************************************
  Illutron take on Disney style capacitive touch sensor using only passives and Arduino
  Dzl 2012
 ****************************************************************************************
                               10n
  PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
                |            |
               3.3k          |
                |            V 1N4148 diode
               GND           |
                             |
 Analog 0 ---+------+--------+
             |      |
           100pf   1MOmhm
             |      |
            GND    GND
*/

//#include <avr/io.h>
//#if ARDUINO >= 100
//#include "Arduino.h"
/*#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif
*/
#include "ATSense.h"


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

ATSense::ATSense()
{
	TCCR1A = 0b10000010;        //-Set up frequency generator
	TCCR1B = 0b00011001;        //-+
	ICR1   = 110;
	OCR1A  = 55;

	//error = 1;		// error will fire if pins are invalid

	// get pin mapping and port for send Pin - from PinMode function in core
	pinMode(9,	OUTPUT);//-Signal generator pin
	pinMode(8, OUTPUT);//-Sync (test) pin
	pinMode(14, INPUT);
/*#ifdef NUM_DIGITAL_PINS
	if (sendPin >= NUM_DIGITAL_PINS) error = -1;
	if (receivePin >= NUM_DIGITAL_PINS) error = -1;
#endif
	*/
	for(int i = 0; i < N; i++)  //-Preset results
		results[i] = 0;			//-+

}	

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void ATSense::sense()
{
	//if (error < 0) return;            // bad pin

	for(unsigned int d=0; d<N; d++)
	{
		int v=analogRead(0);    //-Read response signal
		CLR(TCCR1B,0);          //-Stop generator
		TCNT1=0;                //-Reload new frequency
		ICR1=d;                 // |
		OCR1A=d/2;              //-+
		SET(TCCR1B,0);          //-Restart generator

		results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results

		freq[d] = d;
	}

	//PlottArray(1,freq,results); 

	TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)
	
	//return result;
}

void ATSense::showScope(void)
{
	plotArray(1,freq,results);
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void ATSense::sendData(int Command, unsigned int yValue,unsigned int xValue)
{
	/* >=================================================================< 
	y = 01010100 11010100    (x & y are 2 Byte integers)
	yMSB      yLSB      send seperately -> reciever joins them
	>=================================================================<  */

	byte yLSB=lowByte(yValue);
	byte yMSB=highByte(yValue);
	byte xLSB=lowByte(xValue);
	byte xMSB=highByte(xValue);        


	/* >=================================================================< 
	Only the very first Byte may be a zero, this way allows the computer 
	to know that if a Byte recieved is a zero it must be the start byte.
	If data bytes actually have a value of zero, They are given the value 
	one and the bit in the zeroByte that represents that Byte is made 
	high.  
	>=================================================================< */   

	byte zeroByte = 128;                                   // 10000000

	if(yLSB==0){ yLSB=1; zeroByte=zeroByte+1;}        // Make bit 1 high 
	if(yMSB==0){ yMSB=1; zeroByte=zeroByte+2;}        // make bit 2 high
	if(xLSB==0){ xLSB=1; zeroByte=zeroByte+4;}        // make bit 3 high
	if(xMSB==0){ xMSB=1; zeroByte=zeroByte+8;}        // make bit 4 high


	/* >=================================================================< 
	Calculate the remainder of: sum of all the Bytes divided by 255 
	>=================================================================< */

	byte Checksum = (Command + yMSB + yLSB + xMSB + xLSB + zeroByte) % 255;

	if( Checksum !=0 ){
		Serial.write(byte(0));            // send start bit 
		Serial.write(byte(Command));      // command eg: Which Graph is this data for

		Serial.write(byte(yMSB));         // Y value's most significant byte  
		Serial.write(byte(yLSB));         // Y value's least significant byte   
		Serial.write(byte(xMSB));         // X value's most significant byte  
		Serial.write(byte(xLSB));         // X value's least significant byte  

		Serial.write(byte(zeroByte));     // Which values have a zero value
		Serial.write(byte(Checksum));     // Error Checking Byte
	}
}  




void ATSense::plotArray(unsigned int Cmd,float Array1[],float Array2[])
{
	sendData(Cmd+1, 1,1);                        // Tell PC an array is about to be sent                      
	delay(1);
	for(int x=0;  x < N;  x++){     // Send the arrays 
		sendData(Cmd, round(Array1[x]),round(Array2[x]));
		//delay(1);
	}

	sendData(Cmd+2, 1,1);                        // Confirm arrrays have been sent
}


