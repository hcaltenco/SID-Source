#include <AFMotor.h>
#include <Wire.h>
#include <Encoder.h>

#define ENC_A 2 //14 
#define ENC_B 3 //15
#define nSens 3

AF_DCMotor motor(4);
Encoder myEnc(ENC_A, ENC_B);

unsigned long time_since_touch = 0;
unsigned long pause_timer = 0;
unsigned long first_touch = 0;

//int potPin = 16;
int openPin = 10;
int closePin = 9;
int resetPin = 11;
int redLED = A1; //3;
int greenLED = A0; //2;

//int on = 1;
//int off = -1;
unsigned int state = 0;
unsigned int last_state = 0;
unsigned int touch_sensor = 0;
boolean touch_state[nSens] = {false};
boolean touch_last[nSens] = {false};
//boolean timed_state = false;
unsigned int touch_sum = 0;

int pause = 100;
int motorSpeed = 255;
int rot_counter = 0;
//int last_counter = 1;
int potVal = 0;
int max_pause = 500;           //Time to wait after last touch until curling up
int counter_closed = 150;        //Counter number when curled completely up (also change it in "ormen_leds")
int keep_pos = 0;
int dir = -1;

boolean DEBUG = false;
boolean open_bool = false;
boolean close_bool = false;
boolean press_bool = false;
boolean reset_bool = false;

//--------------------------------------------------------------

void setup() {
  Serial.begin (115200);
  
  // control box leds setup
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // i2c setup address optional for master
  digitalWrite(A4, LOW); 
  digitalWrite(A5, LOW);
  Wire.begin();          
  
  //Motor setup
  pinMode(openPin, INPUT);
  pinMode(closePin, INPUT);
  motor.setSpeed(motorSpeed);  
  motor.run(RELEASE);
  
  Serial.println("Start");
  runReset();
}

//--------------------------------------------------------------

void loop() {
  // read the encoder position and sensor data
  encoder();
  data();
  
  // if request reset
  if(reset_bool && digitalRead(resetPin)){
    delay(300);
    reset_bool = false;
    runReset();
  }
  
  // DLF state from sensor states
  updateState();
  
  // do something depending on the state
  switch(state){
  case 0:
    noTouch();
    break;

  case 1:
    touch();
    if (DEBUG) {
      Serial.print("touch \t");
      for (int i=0; i < nSens; i++)
        Serial.print(touch_state[i]);
      Serial.println();
    }
    break;
    
  case 2:
    keep();
    if (DEBUG) {
      Serial.print("keep \t");
      Serial.print(keep_pos, DEC);
      Serial.print("\t");
      for (int i=0; i < nSens; i++)
        Serial.print(touch_state[i]);
      Serial.println();
    }
    break;
  }
  
  delay(10);
}

//--------------------------------------------------------------

void updateState() {
  touch_sum = 0;
  boolean touch_change = false;
  boolean neighboring = false;
  for (int i = 0; i < nSens; i++) {
    touch_sum += touch_state[i];
    if (i > 0) {
      if ((touch_state[i] == 1 && touch_state[i-1] == 1)) {
        neighboring = true;
      }
    }
    if (touch_state[i] != touch_last[i]) {
      touch_change = true;
      touch_last[i] = touch_state[i];
      touch_sensor = i + 1;
    }
  }
  
  if (touch_change) {
    state = 1; // touch single (change)
  }
  else if (touch_sum > 2) {
    state = 2; // touched multi (constant)
    if (last_state != state)
      keep_pos = rot_counter;
  }
  else if (touch_sum > 1 && !neighboring) {
    state = 2; // touched multi (constant)
    if (last_state != state)
      keep_pos = rot_counter;
  }
  else{
    state = 0; // idle
  }
  last_state = state;
}

//--------------------------------------------------------------

void noTouch(){
  if(millis() - time_since_touch > pause){
    //timed_state = false;
    first_touch = millis();

    if(rot_counter <= counter_closed){
      motor.run(BACKWARD);
    }
    else{
      motor.run(RELEASE);
    }
    
    if (touch_sum == 0)
      touch_sensor = 0;
  } 
  else {
    if (rot_counter > 0){
      motor.run(FORWARD);
    }
    else {
      motor.run(RELEASE);
    }
  }
}

//--------------------------------------------------------------

void touch(){
  //timed_state = true;
  time_since_touch = millis();
  pause = constrain((millis() - first_touch),0,max_pause);

  if(rot_counter >= 0){
    motor.run(FORWARD);
  } 
  else{
    motor.run(RELEASE);
  }
}

//--------------------------------------------------------------

void keep() {
  if (dir > 0) {
    if (rot_counter < keep_pos+1) {
      motor.run(BACKWARD);
    }
    else {
      dir = -1;
      if (keep_pos > 5) {
        keep_pos = keep_pos -5;
      }
    }
  }
  else {
    if (rot_counter > keep_pos-1) {
      motor.run(FORWARD);
    }
    else {
      dir = 1;
      if (keep_pos > 5) {
        keep_pos = keep_pos -5;
      }
    }
  }
}
