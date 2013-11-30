#include <MIDI.h>

int ledPin = 9;   		// LED pin on Arduino board
int sensorPin = 0;              // the pin for the pot
int MIDI_CHI = 4;              // MIDI input channel
int MIDI_CHO = 1;              // MIDI output channel
int sensorValue = 0;
int prevNote = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  MIDI.begin();            	// Launch MIDI with default options
  Serial.begin(115200);            	// (input channel is default set to 1)  
}
void loop() {
  sensorValue = analogRead(sensorPin);
  analogWrite(ledPin, sensorValue/4);

  // send MIDI commands or print to the serial port
  byte potNote = sensorValue/8;
  if (abs(potNote - prevNote) > 5) {
    sendMIDIcommand(16, potNote);
    prevNote = potNote;
  }
}

void sendMIDIcommand(byte p, byte v) {
  MIDI.sendNoteOn(v, 127, MIDI_CHO);
  //MIDI.sendControlChange(p, v, MIDI_CHO);
  /*Serial.write(176);
   Serial.write(p);
   Serial.write(v);*/
  delay(100);
  MIDI.sendNoteOff(p, 0, MIDI_CHO);
  
}



