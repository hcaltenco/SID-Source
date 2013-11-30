#include <AFMotor.h>
#include <Wire.h>
#include <Encoder.h>

#define ENC_A 2 //14 
#define ENC_B 3 //15
//#define ENC_PORT PINC 

AF_DCMotor motor(4);
Encoder myEnc(ENC_A, ENC_B);

unsigned long time_since_touch = 0;
unsigned long pause_timer = 0;
unsigned long first_touch = 0;

int pause = 100;
int potPin = 16;
int openPin = 10;
int closePin = 9;
int resetPin = 11;
int redLED = A1; //3;
int greenLED = A0; //2;

boolean state = LOW;
int on = 1;
int off = -1;
int motorSpeed = 255;
int timed_state = 0;
int rot_counter = 0;
//int last_counter = 1;
int potVal = 0;
int max_pause = 200;           //Time to wait after last touch until curling up
int counter_closed = 150;        //Counter number when curled completely up (also change it in "ormen_leds")

boolean DEBUG = false;
boolean open_bool = false;
boolean close_bool = false;
boolean press_bool = false;
boolean reset_bool = false;

//--------------------------------------------------------------

void setup() {
  Serial.begin (115200);
  Wire.begin();        // join i2c bus (address optional for master)
  delay(200);
  
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(potPin, INPUT);  

  //Encoder setup
  /*pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH); 
  pinMode(ENC_B, INPUT); 
  digitalWrite(ENC_B, HIGH); 
  */
  
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
  encoder();
  
  if(reset_bool && digitalRead(resetPin)){
    delay(300);
    reset_bool = false;
    runReset();
  }
  
  switch(state){
  case LOW:
    noTouch();
    break;

  case HIGH:
    touch();
    break;
  }
  //delay(100);
}

//--------------------------------------------------------------

void noTouch(){
  encoder();
  data();

  if(millis() - time_since_touch > pause){
    timed_state = 0;
    first_touch = millis();

    if(rot_counter <= counter_closed){
      motor.run(BACKWARD);
    }
    else{
      motor.run(RELEASE);
    }

  } 
  else{
    motor.run(RELEASE);
  }
}

//--------------------------------------------------------------

void touch(){
  encoder();
  data();

  if(rot_counter >= 0){
    motor.run(FORWARD);
  } 
  else{
    motor.run(RELEASE);
  }

  timed_state = 1;
  time_since_touch = millis();
  pause = constrain((millis() - first_touch),0,max_pause);
}

//--------------------------------------------------------------

void data(){  
  //Receive from sensor board
  Wire.requestFrom(3, 1);
  //char c[1] = {0};
  while(Wire.available())    // slave may send less than requested 
  {
    state = Wire.read();
  }
  /*if (1 <= sizeof(c)) {
    state = c[0];
  }
  else {
    Serial.println("incomplete data recieved");
  }*/
 
  //state = digitalRead(openPin);
  
  //Send to LED board
  char s[6] = {0}; 
  sprintf(s, "%d %d %d", rot_counter, timed_state, on);
  Wire.beginTransmission(2);
  Wire.write(s);
  Wire.endTransmission();
}





