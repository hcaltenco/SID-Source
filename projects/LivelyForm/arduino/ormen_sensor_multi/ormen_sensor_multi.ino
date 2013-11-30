#include <Wire.h>
#include <CapSense.h>

const boolean DEBUG = false;

const int potPin = 14;
long capValue = 0;
int potVal = 0;
int touchLimit = 0;

long calib_timer = 0;
boolean calib_allow = false;

CapSense cs[] = {
//  CapSense(4,2),
  CapSense(4,6),
  CapSense(4,12),
  CapSense(4,10),
//  CapSense(4,8),
};
const int nSens = sizeof(cs)/sizeof(CapSense);

boolean state[nSens] = {false};


//--------------------------------------------------------------

void setup() {
  digitalWrite(A4, LOW);   // turn off internal pullups of i2c
  digitalWrite(A5, LOW);   // external 10K pullups exist
  
  Wire.begin(3);           // join i2c bus with address #3
  Wire.onRequest(requestEvent);
  
  for (int i = 0; i < nSens; i++) {
  //  cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  //  cs[i].set_CS_Timeout_Millis(50);
  }
  
  Serial.begin (115200);
}

//--------------------------------------------------------------

void loop() {
  delay(500);        //Not necessary
  if (abs(calib_timer - millis()) > 20000 && calib_allow) {
    calib_timer = millis();
    calib_allow = false;
    /*for (int i = 0; i < nSens; i++) {
      cs[i].reset_CS_AutoCal();
    }
    if (DEBUG)
      Serial.println("Capsense recalibrated");
      */
  }
  //requestEvent();
}

//--------------------------------------------------------------

void requestEvent()
{
  //Serial.println("enter request event");
  int potVal = analogRead(potPin);
  touchLimit = potVal*5;
  
  //Read capacitive sensor here and determine if 
  //touch (set state = 1) or !touch (set state = 0)
  //capValue = cs_9_10.capSense(30);
  for (int i = 0; i < nSens; i++) {
    if (i == 1)
      capValue = 0;
    else
      capValue = cs[i].capSense(20);
    //delay(5);
    if(capValue > touchLimit){
      state[i] = true;
      calib_timer = millis();
      calib_allow = true;
    //  break;
    } 
    else{
      state[i] = false;
    }
    if (DEBUG) {
      Serial.print(capValue);
      Serial.print(",");
      Serial.print(state[i]);
      Serial.print("\t");
    }
  }
  if (DEBUG) {
    Serial.print(touchLimit);
    //Serial.print("\t");
    //Serial.print(state);
    Serial.println();
  }
  //Sensor state is sent to the master here
  Wire.write(state,nSens);
}

