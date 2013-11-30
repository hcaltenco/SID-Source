/*
 Lively Friend Code v.2
 Alexandra Abalada and Hector Caltenco
 April 2013
  
 Lively Friend components:
 * Music Instrument Shield
 * 4 pressure sensors in A0, A1, A3, A4
 * 2 flex bend sensors in A2, A5
 
 Usage
 Pressure sensors control volume for each insrument
 Bend Sensor in A2 chooses instruments 0 and 1
 Bend Sensor in A5 chooses instruments 3 and 4
  
 created March 2013
 modified 04 May 2013
 
 Based on Music instrument shield example code
 
 https://www.sparkfun.com/tutorials/302
 
 */
 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);

  //Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); //0xB0 is channel message, set channel volume to near max (127)
  talkMIDI(0xB0, 0, 0x78); //Default bank select drums
  //B0 means bakn select, type of instrument
  //0 default bank
  //0x78 means the percursion's bank

}

void loop() {
  // read the sensor:
  int sensorReading0 = analogRead(A0); 
  int sensorReading1 = analogRead(A1);
  int sensorReading2 = analogRead(A2);
  int sensorReading3 = analogRead(A3);
  int sensorReading4 = analogRead(A4);
  int sensorReading5 = analogRead(A5);


  //instrumetns' initial value
  static byte instrument0 = 80;//39;
  static byte instrument1 = 61;
  static byte instrument2 = 81;
  static byte instrument3 = 55;

  // map the volume to the range of the analog input.
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int volume0 = map(sensorReading0, 0, 960, 40, 127);
  int volume1 = map(sensorReading1, 0, 960, 40, 127);
  int volume2 = map(sensorReading3, 0, 960, 40, 127);
  int volume3 = map(sensorReading4, 0, 960, 40, 127);
  
  // map the pitch (or instrument) range of the bend sensor input
  // the minimum note is 27 and maximum 87 for the percussions
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int thisNote0 = map(sensorReading2, 150, 350, 27, 87);
  int thisNote1 = map(sensorReading5, 150, 350, 27, 87);


  // play the note for the first instrument pair:
  //make the logic between the sensors
  if (sensorReading0>10) {
    talkMIDI(0xC0, instrument0, 0); //Set instrument number. 0xC0 is a 1 data byte command
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0, instrument0, volume0);
    delay(50);  
    noteOff(0, instrument0, volume0);
  }

  if (sensorReading1>10) {
    talkMIDI(0xC0, instrument1, 0); //Set instrument number. 0xC0 is a 1 data byte command
    noteOn(0, instrument1, volume1);
    delay(50);  
    noteOff(0,instrument1, volume1);
  }
  if (sensorReading2>320 || sensorReading2<300) {
    //talkMIDI(0xC0, thisPitch2, 0); //Set instrument number. 0xC0 is a 1 data byte command
    instrument0 = constrain(thisNote0*0.8, 27,66);
    instrument1 = constrain(thisNote0*1.2, 35,87);
    //noteOn(0, thisPitch2, 120);
    //delay(50);  
    //noteOff(0,thisPitch2, 120);
  }

  // play the note for the second instrument pair:
  //make the logic between the sensors
  if (sensorReading3>10) {
    talkMIDI(0xC0, instrument2, 0); //Set instrument number. 0xC0 is a 1 data byte command
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0, instrument2, volume2);
    delay(50);  
    noteOff(0, instrument2, volume2);
  }

  if (sensorReading4>10) {
    talkMIDI(0xC0, instrument3, 0); //Set instrument number. 0xC0 is a 1 data byte command
    noteOn(0, instrument3, volume3);
    delay(50);  
    noteOff(0,instrument3, volume3);
  }
  if (sensorReading5>320 || sensorReading5<300) {
    //talkMIDI(0xC0, thisPitch2, 0); //Set instrument number. 0xC0 is a 1 data byte command
    instrument2 = constrain(thisNote1*0.8, 27,66);
    instrument3 = constrain(thisNote1*1.2, 35,87);
    //noteOn(0, thisPitch2, 120);
    //delay(50);  
    //noteOff(0,thisPitch2, 120);
  }
  
  // print all the information
  Serial.print (sensorReading0);
  Serial.print (',');
  Serial.print (volume0);
  Serial.print (',');
  Serial.print (instrument0);
  Serial.print ('\t');

  Serial.print (sensorReading1);
  Serial.print (',');
  Serial.print (volume1);
  Serial.print (',');
  Serial.print (instrument1);
  Serial.print ('\t');

  Serial.print (sensorReading2);
  Serial.print (',');
  Serial.print (thisNote0);
  Serial.print ('\t');

  Serial.print (sensorReading3);
  Serial.print (',');
  Serial.print (volume2);
  Serial.print (',');
  Serial.print (instrument2);
  Serial.print ('\t');

  Serial.print (sensorReading4);
  Serial.print (',');
  Serial.print (volume3);
  Serial.print (',');
  Serial.print (instrument3);
  Serial.print ('\t');

  Serial.print (sensorReading5);
  Serial.print (',');
  Serial.print (thisNote1);
  Serial.println ();
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}




