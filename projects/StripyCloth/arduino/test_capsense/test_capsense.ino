#include <CapSense.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapSense   cs_4_2 = CapSense(6,0);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapSense   cs_4_6 = CapSense(6,1);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapSense   cs_4_8 = CapSense(6,11);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
//CapSense   cs_4_10= CapSense(4,10);       // 10M resistor between pins 4 &10, pin10 is sensor pin, add a wire and or foil
//CapSense   cs_4_12= CapSense(4,12);       // 10M resistor between pins 4 &12, pin12 is sensor pin, add a wire and or foil

void setup()                    
{
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capSense(30);
    long total2 =  cs_4_6.capSense(30);
    long total3 =  cs_4_8.capSense(30);
    //long total4 =  cs_4_10.capSense(30);
    //long total5 =  cs_4_12.capSense(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3
    //Serial.print(total3);                  // print sensor output 2
    //Serial.print("\t");
    //Serial.print(total4);                  // print sensor output 2
    //Serial.print("\t");
    //Serial.println(total5);                // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port 
}
