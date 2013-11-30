#include <MIDI.h>

const int sensPin[] = {0,1};       // the pin for the pot
const int MIDI_CHI = 4;        // MIDI input channel
const int MIDI_CHO = 1;        // MIDI output channel
const int WAKE_SENS = 0;       // Sensor to listen to for wakeup
const int avgrange = 10;       //Quantity of values to average (sample size)
int state = 8;                 //The initial state

// get the number of sensors
const int nSens = sizeof(sensPin)/sizeof(int);
byte p1[nSens]; // sensor value (0-127)
byte p2[nSens]; // sensor value (0-127)
//byte base[nSens]; // baseline value (0-127)
long t[nSens]; // a time stamp value (ms);

// constants and thresholds
int N = 5;     // a Number of times
int TL = 200; // a low time threshold 
int TH = 5000; // a high time threshold 
byte AL = 5;    // a low value threshold
byte AH = 40;   // a high value threshold

void setup()
{
  MIDI.begin();            	// Launch MIDI with default options
  Serial.begin(115200);         // (input channel is default set to 1)
  /*delay(100);
  for (s=0; s<nSens; s++) {
    base[s] = readSensor[s];
  }*/
}

void loop() {
  //Serial.println(state);
  switch (state) {
    /*case 1: // being disturbed
      tickle();
      break;
    case 2:
      boxing();
      break;
    case 4:
      suffocate();
      break; */
    case 6: // sleep
      sleeping();
      break;
    case 8: // normal
      normal();
      break;
  }
  delay(20);
  
}

//-------------------------------------------------
void tickle(int s) {
  //sendNote(7, p1[s], 10);
  Serial.println("Tickle");
}

void boxing(int s) {
  //sendNote(7, p1[s], 500);
  Serial.println("Boxing");
}

void suffocate(int s) {
  static byte counter = 0;
  byte pit = constrain(counter, 0, 127);
  if (counter > 126) {
    state = 8;
  }
  //sendNote(pit, p1[s], 0);
  Serial.println("Suffocate");
}

//-------------------------------------------------
void sleeping() {
  static boolean allow_wake = false;
  int pressed = checkForPress(WAKE_SENS, AH);
  
  if (pressed > 0) {
    allow_wake = true;
  //  Serial.println(allow_wake);
  }
  else if (pressed < 0) {
    allow_wake = false;
  //  Serial.println(allow_wake);
  }
  
  if (millis() - t[WAKE_SENS] > TH && allow_wake) {
    //Serial.println("awake");
    t[WAKE_SENS] = millis();
    state = 8; // wake up (normal)
  }
  /*Serial.print(millis() - t[WAKE_SENS]); Serial.print('\t');
  Serial.print(pressed); Serial.print('\t');
  Serial.println(allow_wake);*/
}

//-------------------------------------------------
void normal() {
  static int low_counter[nSens];
  static int high_counter[nSens];
  static boolean kept_pressed[nSens];
  for (int s=0; s<nSens; s++) {
    int pressed = checkForPress(s, AL);
    
    /*if (abs(pressed) > AH && millis() - t[s] < TH) {
      high_counter[s]++;
      if (pressed > AH) {
        kept_pressed[s] = true;
        //  Serial.println(allow_wake);
      }
      else if (pressed < 0) {
        kept_pressed[s] = false;
      //  Serial.println(allow_wake);
      }
      Serial.print ("boxing \t");
      Serial.println(p1[s]);
    }
    */
    if (abs(pressed) > AL && millis() - t[s] < TL) {
      low_counter[s]++;
      //kept_pressed[s] = false;
      /*Serial.print ("tickle \t");
      Serial.println(p1[s]);*/
      if (s == 0)
        sendControl(s+1, p1[s]);
      if (s == 1)
        sendNote(p1[s],100);
    }
    if (millis() - t[s] > TH) {
      low_counter[s] = 0;
    }
    if (millis() - t[s] > TL) {
      low_counter[s] = 0;
    }
    

    
    // Rules
    /*if (high_counter[s] > N) {
      //state = 2; // boxing
      low_counter[s] = 0;
      if (abs(pressed) > AH)
        boxing(s);
    }
    else if (low_counter[s] > N) {
      //state = 1; // tickle
      high_counter[s] = 0;
      if (abs(pressed) > AL)
        tickle(s);
    }
    else if (kept_pressed[s] && t[s] > TH) {
      //state = 4; // Suffocate
      t[s] = millis();
      if (kept_pressed[s])
        suffocate(s);
    }
    else if (!kept_pressed[s] && t[s] > TH*10) {
      //t[s] = millis();
      //state = 6;
    }
    //TODO: winding up and comfort
    else {
    //  sendControl(s+1, p1[s]);
      Serial.println(p1[s]);
    }
    */
  }
}

//-------------------------------------------------
int checkForPress(int s, int THRES) {
  int pressed = 0;
  //p[WAKE_SENS] = readSensor(WAKE_SENS)-base[WAKE_SENS];
  readSensor(s);

  if (abs(p1[s] - p2[s]) > THRES) {
    t[s] = millis();
    /*if (p1[s] - p2[s] > 0) {
      pressed = 1; // pressed
    }
    else {
      pressed = -1; // depressed
    }*/
    pressed = p1[s]- p2[s];
    p2[s] = p1[s];
  //  Serial.println(pressed);
  }
  return pressed;
}

//-------------------------------------------------
//byte readSensor(int s) {
void readSensor(int s) {
  long sumVal = 0;
  int avgVal;
  byte retVal;
  
  // read several times and average
  for(int i = 0; i < avgrange ; i++)
  {
    int sensVal = analogRead(sensPin[s]); 
    sumVal += sensVal;
    delay(1);
  }
  // average over number of samples
  avgVal = sumVal/avgrange;
  
  // convert sonar (s=0) reading to cm and constrain as byte between 0 - 127
  if (s < 2) {
    retVal = constrain(map(avgVal*2.54/2, 30, 20, 0, 127), 0, 127);
  }
  // for other sensors (0-255) constrain to 0-127
  else {
    retVal = constrain(avgVal/2, 0, 127);
  }
  p1[s] = retVal; // store value in global array
}

//-------------------------------------------------
/*void sendMIDIcommand(byte p, byte v) {
  MIDI.sendNoteOn(v, 127, MIDI_CHO);
  //MIDI.sendControlChange(p, v, MIDI_CHO);
  delay(100);
  MIDI.sendNoteOff(p, 0, MIDI_CHO);
  
}*/

void sendNote(byte p, byte v) {
  static byte prevNote = 0;
  byte playNote = map(p, 0, 127, 40, 90);
  MIDI.sendNoteOff(prevNote, 0, MIDI_CHO);
  /*if (wait != 0) {
    delay(wait);
    MIDI.sendNoteOff(p, v, MIDI_CHO);
  }*/
  MIDI.sendNoteOn(playNote, v, MIDI_CHO);
  prevNote = playNote;
}

void sendControl(byte n, byte v) {
  MIDI.sendControlChange(n, v, MIDI_CHO);
}
