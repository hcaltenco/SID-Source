#include <CapSense.h>

//#define COLOUR_SPEED 4000 // Time from one colour to next colour. Eg. from red to green...255,0,0 -> 0,255,0
//#define MAX_TIME_TO_FALL_A_SLEEP 15 //15000 //The maximum time, it takes for the box to fall a sleep again after having been touched

// CapSense object
CapSense cs_8_7 = CapSense(8,7);

// RGB Led Strips (PWM)
int r1Pin = 3;
int g1Pin = 5;
int b1Pin = 6;
int r2Pin = 9;
int g2Pin = 10;
int b2Pin = 11;
int colourValues[] = {
  0,0,0,0,0,0}; //r1,g1,b1,r2,g2,b2
int lightBrightness = 255;

// RGB Led Mode (on-off)
int r3Pin = 4; //12
int g3Pin = 2;  //2
int b3Pin = 12; //13
byte modeValues[3] = {
  LOW,HIGH,HIGH}; //r3,g3,b3

// Sensibility Slider  
int sensorPin = A0;
int sensorValue = 0;  //0 - 1023
unsigned long capaValue;
int capaValueState1 = 75;
int capaValueState2 = 75;
int capaValueState3 = 75;

// Mode Button
int modePin = A2;
int currentMode = 0;
boolean modeChanged = false;
int modeButton;
int countLOW;

// Global Led Color vars
int COLOUR_SPEED;
int offset;        // Colour offset
int colourShift;

//timers
int maxTimeToFallASleep;
unsigned long touchStarted, lastTimeTouched, touchLength;

/* Hardware Setup */
void setup()
{
  Serial.begin(9600);
  cs_8_7.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  //cs_8_7.set_CS_Timeout_Millis(200);
  pinMode(r1Pin, OUTPUT);
  pinMode(g1Pin, OUTPUT);
  pinMode(b1Pin, OUTPUT);
  pinMode(r2Pin, OUTPUT);
  pinMode(g2Pin, OUTPUT);
  pinMode(b2Pin, OUTPUT);
  
  pinMode(r3Pin, OUTPUT);
  pinMode(g3Pin, OUTPUT);
  pinMode(b3Pin, OUTPUT);

  analogWrite(r1Pin, 0);
  analogWrite(g1Pin, 0);
  analogWrite(b1Pin, 0);
  analogWrite(r2Pin, 0);
  analogWrite(g2Pin, 0);
  analogWrite(b2Pin, 0);
  
  // The Mode button
  pinMode(modePin, INPUT);
  //digitalWrite(modePin, HIGH); // enable pullup resistor
}

void loop()
{
  capaValue = CapaSense();
  //Serial.println(capaValue);

  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  
  modeButton = analogRead(modePin);
  //Serial.println(modeButton, DEC);
  
  if (modeButton == 0 && modeChanged == false) {
    countLOW ++;
    if (countLOW > 10){
      ChangeMode();
      modeChanged = true;
    }
  }
  else if (modeButton > 50) { //HIGH did not work
    modeChanged = false;
    countLOW = 0;
  }
  DisplayMode();

  Behavior();
}

void ChangeMode()
{
  currentMode ++;
  if (currentMode > 2) {
    currentMode = 0;
  }
  for (int i = 0; i < 3; i++) {
    if (i == currentMode) {
      modeValues[i] = LOW; // turn on corresp. mode
    }
    else {
      modeValues[i] = HIGH; // turn off other leds
    }
    //Serial.print(modeValues[i]);
  }
  //Serial.println();
}

long CapaSense()
{
  static int capaBuffer[3]; // Used to average the last 3 messurements of the capacitive sensor, to eliminate random changes
  capaBuffer[0] = capaBuffer[1];
  capaBuffer[1] = capaBuffer[2];
  capaBuffer[2] = cs_8_7.capSense(30);

  return (capaBuffer[0] + capaBuffer[1] + capaBuffer[2]) / 3;
}

void Behavior()
{
  int capaValueState1 = map(sensorValue, 0, 1023, 50, 1000);
  
  
  static int state = 1;  //State 1 = The box is sleeping, and not beeing touched; state3 = the box is beeing touched; state4 = the box is falling a sleep after having beeing touced for a given period of time
  int startColourSpeed;
  int endColourSpeed;
  
  switch(currentMode)
  {
    case 0: //original
      startColourSpeed = 3000;
      endColourSpeed   = 3000;
      maxTimeToFallASleep = 1500;
      break;
    case 1: //slow to fast
      startColourSpeed = 6000;
      endColourSpeed   = 300;
      maxTimeToFallASleep = 200;
      break;
    case 2:
      startColourSpeed = 100;
      endColourSpeed   = 2000;
      maxTimeToFallASleep = 200;
      break;
  }
  
  switch(state)
  {
  case 1: //Sleeping
    {
      if(capaValue <= capaValueState1) //The box is not beeing touched after sleeping
      {
        state = 1;
        offset = 0;
      }
      else // The box is beeing touched
      {
        state = 3;
        touchStarted = millis();
        lastTimeTouched = millis();
        COLOUR_SPEED = startColourSpeed;
      }
    }
    break;
    /*case 2:
     {
     Behavior2();
     }
     break;*/
  case 3: // Beeing touced
    {
      if(capaValue > capaValueState1) // The box is beeing touched
      {
        int MAX_TOUCH_LENGTH = 10000;
        state = 3;
        lastTimeTouched = millis();
        touchLength = lastTimeTouched - touchStarted;
        
        if (touchLength < MAX_TOUCH_LENGTH) {
          COLOUR_SPEED = round(map(touchLength, 0, MAX_TOUCH_LENGTH, startColourSpeed, endColourSpeed));
        }
        else {
          COLOUR_SPEED = endColourSpeed;
        }
      }
      else //The box is not beeing touched
      {
        state = 4;
      }
    }
    break;
  case 4: // Falling a sleep
    {
      touchLength = lastTimeTouched - touchStarted;
      if(capaValue > capaValueState1) // The box is beeing touched again
      {
        state = 3;
        if(millis() - lastTimeTouched > 500) //The box has not been touched for at least 0.5 sec
        {
          ChangeOffset(1400);
        }
        lastTimeTouched = millis();
      }
      else //The box is not beeing touched
      {
        if( millis() - lastTimeTouched > touchLength || millis() - lastTimeTouched > maxTimeToFallASleep) // Stay in state 4, as long time as the box has been touched, but max maxTimeToFallASleep milliseconds
        {
          state = 1;
        }
      }
    }
    break;
  }


  switch(state)
  {
  case 1:
    {
      Behavior1();
    }
    break;
    /*case 2:
     {
     Behavior2();
     }
     break;*/
  case 3:
    {
      Behavior3();
    }
    break;
  case 4:
    {
      Behavior4();
    }
  }

  ChangeLedStrips();
}

void Behavior1() //nothing is close to the box
{
  static long lastIncrement = 0;
  static float intensity = 0.0;
  intensity = millis();
  intensity /= 1000.0;
  colourValues[0] = map( cos(intensity)*100, -100, 100, 10, 50 ); //Right Red
  colourValues[1] = map( cos(intensity)*100, -100, 100, 0, 10 );  //Right Green
  colourValues[2] = 0;
  colourValues[3] = colourValues[0];  //Left Red
  colourValues[4] = 0;
  colourValues[5] = colourValues[1];  //Left Blue

  lightBrightness = 255;
  Serial.write((byte)0); // Release motor to keep temperature down
  Serial.println();
}

void Behavior2() //Something is close to the box
{
  //CapaValues between capaValueState1 - capaValueState2
  lightBrightness = map(capaValue, capaValueState1, capaValueState2, 50, 255);
  lightBrightness = constrain(lightBrightness, 50, 255);
  cycleColours();
}

void Behavior3() //The box is being touched
{
  lightBrightness = 255;
  cycleColours();
  byte motorSpeed = map(COLOUR_SPEED, 0, 6000, 10, 1);
  Serial.write(motorSpeed); //Turn motor
  Serial.println();
}

void Behavior4() //The box has recently been touched, and is "going back to sleep"
{
  touchLength = lastTimeTouched - touchStarted;
  if(touchLength > maxTimeToFallASleep)
  {
    touchLength = maxTimeToFallASleep;
  }
  cycleColours();
  
  lightBrightness = map(millis() - lastTimeTouched, 0, touchLength, 255, 50); // Slowly turn down the lights
  Serial.write((byte)0); // Release motor to keep temperature down
  Serial.println();
}

void ChangeOffset(int change)
{
  offset += change;
}

void NegateColours()
{
  if(colourShift == 0)
  {
    colourShift = COLOUR_SPEED * 3 / 2;
  }
  else
  {
    colourShift = 0;
  }
}

void cycleColours()
{
  static long cycleStart;
  long now = millis() - cycleStart;
  int rightState = ( (now - (offset/2)) + colourShift ); //% (COLOUR_SPEED * 3);
  int leftState  = ( (now + (offset/2)) + colourShift ); //% (COLOUR_SPEED * 3);
  
  //RIGHT LED STRIP
  if(rightState < COLOUR_SPEED) // RIGHT R -> G
  {
    colourValues[0] = map(rightState, 0, COLOUR_SPEED, 255, 0);
    colourValues[1] = map(rightState, 0, COLOUR_SPEED, 0, 255);
    colourValues[2] = 0;
  }
  else if(rightState < COLOUR_SPEED * 2) // RIGHT G -> B
  {
    colourValues[1] = map(rightState, COLOUR_SPEED, COLOUR_SPEED * 2, 255, 0);
    colourValues[2] = map(rightState, COLOUR_SPEED, COLOUR_SPEED * 2, 0, 255);
    colourValues[0] = 0;
  }
  else if(rightState < COLOUR_SPEED * 3) // RIGHT B -> R
  {
    colourValues[2] = map(rightState, COLOUR_SPEED * 2, COLOUR_SPEED * 3, 255, 0);
    colourValues[0] = map(rightState, COLOUR_SPEED * 2, COLOUR_SPEED * 3, 0, 255);
    colourValues[1] = 0;
  }
  else
  {
    cycleStart = millis();
  }

  //LEFT LED STRIP
  if(leftState < COLOUR_SPEED) // LEFT R -> G
  {
    colourValues[3] = map(leftState, 0, COLOUR_SPEED, 255, 0);
    colourValues[4] = map(leftState, 0, COLOUR_SPEED, 0, 255);
    colourValues[5] = 0;
  }
  else if(leftState < COLOUR_SPEED * 2) // LEFT G -> B
  {
    colourValues[4] = map(leftState, COLOUR_SPEED, COLOUR_SPEED * 2, 255, 0);
    colourValues[5] = map(leftState, COLOUR_SPEED, COLOUR_SPEED * 2, 0, 255);
    colourValues[3] = 0;
  }
  else if(leftState < COLOUR_SPEED * 3) // LEFT B -> R
  {
    colourValues[5] = map(leftState, COLOUR_SPEED * 2, COLOUR_SPEED * 3, 255, 0);
    colourValues[3] = map(leftState, COLOUR_SPEED * 2, COLOUR_SPEED * 3, 0, 255);
    colourValues[4] = 0;
  }
  else
  {
    cycleStart = millis();
  }
}

void ChangeLedStrips()
{
  analogWrite(r1Pin, colourValues[0] * lightBrightness/255);
  analogWrite(g1Pin, colourValues[1] * lightBrightness/255);
  analogWrite(b1Pin, colourValues[2] * lightBrightness/255);
  analogWrite(r2Pin, colourValues[3] * lightBrightness/255);
  analogWrite(g2Pin, colourValues[4] * lightBrightness/255);
  analogWrite(b2Pin, colourValues[5] * lightBrightness/255);
}

void DisplayMode()
{
  digitalWrite(r3Pin, modeValues[0]);
  digitalWrite(g3Pin, modeValues[1]);
  digitalWrite(b3Pin, modeValues[2]);
}

void PrintColourValues()
{
  Serial.println();
  Serial.print(colourValues[0]);
  Serial.print("\t");
  Serial.print(colourValues[1]);
  Serial.print("\t");
  Serial.print(colourValues[2]);
  Serial.print("\t");
  Serial.print(colourValues[3]);
  Serial.print("\t");
  Serial.print(colourValues[4]);
  Serial.print("\t");
  Serial.println(colourValues[5]);
}

