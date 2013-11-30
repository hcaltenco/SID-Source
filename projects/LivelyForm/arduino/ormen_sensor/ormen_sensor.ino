#include <Wire.h>
#include <CapSense.h>

boolean DEBUG = true;

int sensorPin = 10;   //Måske skal pin 9 og 10 byttes om,
int sendPin = 9;     //jeg kan ikke huske den præcise opsætning
boolean state = LOW;
long capValue = 0;
int potVal = 0;
int touchLimit = 0;
int potPin = 14;

CapSense cs_9_10 = CapSense(9,10);

//--------------------------------------------------------------

void setup() {
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  Wire.begin(3);        // join i2c bus with address #3
  //Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  //cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  Serial.begin (115200);
}

//--------------------------------------------------------------

void loop() {
  delay(500);        //Not necessary
}

//--------------------------------------------------------------

void requestEvent()
{
  int potVal = analogRead(potPin);
  touchLimit = potVal*3; //*20
  
  //Read capacitive sensor here and determine if 
  //touch (set state = 1) or !touch (set state = 0)
  capValue =  cs_9_10.capSense(30);

  if(capValue > touchLimit){
    state = HIGH;
  } 
  else{
    state = LOW;
  }
  if (DEBUG) {
    Serial.println(touchLimit);
    Serial.println(capValue);
    Serial.println();
  }
  //Sensor state is sent to the master here
  //char s[16];
  //sprintf(s, "%d", state);
  Wire.write(state);
}

