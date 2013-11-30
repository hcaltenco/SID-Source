/*
 ATSense.h v.01 - Arduino Touché Sensing Library based on:
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

// ensure this library description is only included once
#ifndef ATSense_h
#define ATSense_h


//#if ARDUINO >= 100
#include "Arduino.h"
/*#else
#include "WProgram.h"
#endif
*/
#include <inttypes.h>
#include <avr/io.h>
#include<avr/interrupt.h> 

//How many frequencies
#define N 160

// Bit Set/Clear macros
#define SET(x,y) (x |=(1<<y))		
#define CLR(x,y) (x &= (~(1<<y)))   
#define CHK(x,y) (x & (1<<y))       
#define TOG(x,y) (x^=(1<<y))   

// library interface description
class ATSense
{
  // user-accessible "public" interface
  public:
  // variables
	float results[N];	//-Filtered result buffer
	float freq[N];		//-Filtered result buffer
  
  // methods
	ATSense();
	void sense(void);
	void showScope(void);
	
  // library-accessible "private" interface
  private:
  // variables
	int error;
	
  // methods
	void sendData(int Command, unsigned int yValue,unsigned int xValue);
	void plotArray(unsigned int Cmd,float Array1[],float Array2[]);
};

#endif
