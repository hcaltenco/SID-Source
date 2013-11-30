/*
 * Arduino Touche Sensing Library Demo Sketch
 * Hector Caltenco 2012 
 * Based on the Advanced Touch Sensing Program by DZL: 
 * http://www.instructables.com/id/Touche-for-Arduino-Advanced-touch-sensing/
 * -------------------------------------------------------------------
 * Library Modification by Héctor Caltenco - Arduino 1.0 compatibility
 * 
 ****************************************************************************************
 * Illutron take on Disney style capacitive touch sensor using only passives and Arduino
 * Dzl 2012
 ****************************************************************************************
 *                               10n
 *  PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
 *                |            |
 *               3.3k          |
 *                |            V 1N4148 diode
 *               GND           |
 *                             |
 * Analog 0 ---+------+--------+
 *             |      |
 *           100pf   1MOmhm
 *             |      |
 *            GND    GND
 */

#include <ATSense.h>

ATSense   touche = ATSense();

void setup()                    
{
   Serial.begin(115200);
}

void loop()                    
{
    touche.sense();
    //touche.showScope();
    for (int i=1; i<160; i++) {
      Serial.print(touche.results[i]);
      Serial.print('\t');
    }
    Serial.println();
    delay(5);
}
