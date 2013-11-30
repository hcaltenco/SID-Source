/* ****************************************************

Arduino code for Microphone Test

**************************************************** */

#include <CapSense.h>

int rl[] = {9, 6, 10};          // select the pin for the red LEDs
int bl[] = {3, 11, 5};        // select the pin for the blue LEDs
int micPins[] = {A0, A1, A2};  // select the input pin for the mic

int sensorPin = 7;   //Måske skal pin 9 og 10 byttes om,
int sendPin = 8;     //jeg kan ikke huske den præcise opsætning
int thresholdPin = A3;

const int n_mics = sizeof(micPins)/sizeof(int);
int analogValue[n_mics];
int base[n_mics];

int MIN_TIME_ON = 100; // minimum time for the led to be on
int MAX_THRESHOLD = 200;
int MIN_THRESHOLD[] = {40, 30, 50};
//int TOUCH_THRESHOLD = 20;
//int THRESHOLD = 75;

CapSense cs = CapSense(sendPin,sensorPin);

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for (int i=0; i<3; i++) {
    pinMode(rl[i], OUTPUT);
    pinMode(bl[i], OUTPUT);
  }
  
  // turn off CapSense autocalibrate 
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  
  // start serial port at 9600 bps:
  Serial.begin(19200);//9600);
}

void loop() {
  static unsigned long time_on;
  static byte anger_r[n_mics];
  static byte anger_b[n_mics];
  //int total_anger[n_mics];

  static int THRESHOLD[n_mics]; //= MIN_THRESHOLD;
  int TOUCH_THRESHOLD = analogRead(thresholdPin);
  
  //Read capacitive sensor here and determine if touch (set state = 1) or !touch (set state = 0)
  long capValue =  cs.capSense(30);
  
  int maxVal = 0;
  int iMax;
  for (int i = 0; i < n_mics; i++) {
    int sensValue = analogRead(micPins[i]);
    base[i] = 0.8 * base[i] + 0.2 * sensValue;
    analogValue[i] = constrain(sensValue - base[i], -512, 512);
    
    /* find the most active microphone */
    if (abs(analogValue[i]) > maxVal) {
      maxVal = abs(analogValue[i]);
      iMax = i;
    }
    
  //  total_anger[i] = anger_r[i] + anger_b[i];
  }
  
  /* if touching allow to anger device */
  if (capValue > TOUCH_THRESHOLD) {
    /* turn leds of active mic if over threshold */
    if (analogValue[iMax] > THRESHOLD[iMax]) {
      // turn on red led fast
      anger_r[iMax] = constrain(anger_r[iMax] + 3*analogValue[iMax]/THRESHOLD[iMax], 0, 255);
      // turn down blue led slow
      // anger_b[iMax] = constrain(anger_b[iMax] - analogValue[iMax]/THRESHOLD, 0, 255);
      // timestamp
      time_on = millis();
    }
    else if (analogValue[iMax] < -THRESHOLD[iMax]) {
      // turn on blue led fast
      anger_b[iMax] = constrain(anger_b[iMax] - 3*analogValue[iMax]/THRESHOLD[iMax], 0, 255);
      // turn down red led slow
      // anger_r[iMax] = constrain(anger_r[iMax] + analogValue[iMax]/THRESHOLD, 0, 255);
      // timestamp
      time_on = millis();
    }
  }
  
  /* Adjust threshold if too much noise */
  //int NoiseThres = THRESHOLD;
  if (abs(analogValue[0]) > THRESHOLD[0] && (abs(analogValue[1]) > THRESHOLD[1] && abs(analogValue[2]) > THRESHOLD[2]))
  {
    /* turn off leds if too much current being consumed */
    for (int i = 0; i < n_mics; i++)
    {
      // turn leds down fast
      anger_r[i] = constrain(anger_r[i]/5, 0, 255);
      anger_b[i] = constrain(anger_b[i]/5, 0, 255);
      //}
      if (THRESHOLD[i] < MAX_THRESHOLD)
        THRESHOLD[i] += 50;
    }
  }
  else if (abs(analogValue[0]) < MIN_THRESHOLD[0] && (abs(analogValue[1]) < MIN_THRESHOLD[1] && abs(analogValue[2]) < MIN_THRESHOLD[2]))
  {
    if ((millis() - time_on) > 5 * MIN_TIME_ON) {
    for (int i = 0; i < n_mics; i++)
    {
      if (THRESHOLD[i] > MIN_THRESHOLD[i])
        THRESHOLD[i] -= 10;
      }
    }
  }
  
  /* display led status */
  for (int i = 0; i < n_mics; i++ ) {
    if ((millis() - time_on) > MIN_TIME_ON) {
      // turn leds down slowly
      anger_r[i] = constrain(anger_r[i] - 1, 0, 255);
      anger_b[i] = constrain(anger_b[i] - 1, 0, 255);
    }
    
    // led state display
    analogWrite(rl[i], anger_r[i]);
    analogWrite(bl[i], anger_b[i]);
    
    // send values through serial
    Serial.print(analogValue[i], DEC);
    Serial.print(",");
    Serial.print(THRESHOLD[i], DEC);
    //if (i < n_mics-1)
    //  Serial.print(",");
    //else
      Serial.print(";");
  }
  // send threshold values through serial
  /*for (int i = 0; i < n_mics; i++ ) {
    Serial.print(THRESHOLD[i], DEC);
    if (i < n_mics-1)
      Serial.print(",");
    else
      Serial.print(";");
  }
  */
  // send capsense value through serial
  Serial.print(capValue, DEC);
  Serial.print(",");
  Serial.println(TOUCH_THRESHOLD);
  // pause for 10 milliseconds:
  delay(10);
}


