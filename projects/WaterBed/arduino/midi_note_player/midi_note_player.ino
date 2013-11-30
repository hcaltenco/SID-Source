/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */
 
 #include <MIDI.h>

const int sensorPin = A0;   // select the input pin for the potentiometer
const int ledPin = 13;      // select the pin for the LED
const int MIDI_CHI = 4;     // MIDI input channel
const int MIDI_CHO = 1;     // MIDI output channel
int sensorValue = 0;        // variable to store the value coming from the sensor
unsigned long sensorFreq = 0;
byte pitchValue, velocValue;

const boolean useMIDI = true;

void setup() {
  
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT:
  if (useMIDI) {
    MIDI.begin();             // Launch MIDI with default options
  }
  
  Serial.begin(115200);       // Start serial communication
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  if (sensorValue > 340) {
    digitalWrite(ledPin, HIGH);
    unsigned long time = pulseIn(sensorPin, HIGH, 5000);
    if (time > 0)
      sensorFreq = 100000/time;
    /*else
      sensorFreq = 0;*/
  }
  else{
    digitalWrite(ledPin, LOW);
    sensorFreq = 0;
  }
  
  velocValue = constrain(map(sensorValue, 0, 670, -127, 127), 0, 127);
  pitchValue = constrain(map(sensorFreq, 0, 335, 0, 127), 0, 127);
  if (useMIDI) {
    
    if (velocValue > 10) {
      /*byte pNote = map(pitchValue, 0, 127, 40, 90);
      byte vNote = map(velocValue, 0, 127, 50, 127);
      MIDI.sendNoteOn(pNote, vNote, MIDI_CHO);*/
      byte pNote = map(velocValue, 0, 127, 40, 90);
      MIDI.sendNoteOn(pNote, 100, MIDI_CHO);
    }
    /*else {

    }*/
  }
  else {
    Serial.print(sensorValue);
    Serial.print("\t");
    Serial.println(sensorFreq); 
  }
  
  
  // stop the program for for <sensorValue> milliseconds:
  delay(10);                  
}
