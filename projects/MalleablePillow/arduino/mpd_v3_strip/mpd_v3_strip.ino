/* ****************************************************

Arduino code for Microphone Test

**************************************************** */

//#include <CapSense.h>
//#include <HL1606strip.h>
#include <HL1606stripPWM.h>

// use -any- 3 pins!
#define STRIP_D 11 //4
#define STRIP_C 13 //3
#define STRIP_L 10 //2

int micPins[] = {A0, A1, A2};  // select the input pin for the mic

//int sensorPin = 7;   //Måske skal pin 9 og 10 byttes om,
//int sendPin = 8;     //jeg kan ikke huske den præcise opsætning
//int thresholdPin = A3;

const int n_mics = sizeof(micPins)/sizeof(int);
int analogValue[n_mics];
int base[n_mics];

int MIN_TIME_ON = 100; // minimum time for the led to be on
int MAX_THRESHOLD = 200;
int MIN_THRESHOLD[] = {30, 30, 30};
//int TOUCH_THRESHOLD = 20;
//int THRESHOLD = 75;

//CapSense cs = CapSense(sendPin,sensorPin);
//HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, 6);
HL1606stripPWM strip = HL1606stripPWM(12, STRIP_L);

void setup() {                
  // start serial port at 9600 bps:
  Serial.begin(19200);//9600);
  
  // ONLY FOR stripPWM
  strip.setPWMbits(3);
  strip.setSPIdivider(32);
  strip.setCPUmax(70);    // 70% is what we start at
  strip.begin();
  
  //printStripTiming();
  
}

void loop() {
  static unsigned long time_on;
  static byte anger[n_mics];
  //static byte anger_b[n_mics];
  //int total_anger[n_mics];

  static int THRESHOLD[n_mics]; //= MIN_THRESHOLD;
  //int TOUCH_THRESHOLD = analogRead(thresholdPin);
  
  //Read capacitive sensor here and determine if touch (set state = 1) or !touch (set state = 0)
  //long capValue =  100; //cs.capSense(30);
  
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
  //if (capValue > TOUCH_THRESHOLD) {
    /* turn leds of active mic if over threshold */
    if (abs(analogValue[iMax]) > THRESHOLD[iMax]) {
      // turn on red led fast
      anger[iMax] = constrain(anger[iMax] + 3*abs(analogValue[iMax])/THRESHOLD[iMax], 0, 255);
      // turn down blue led slow
      // anger_b[iMax] = constrain(anger_b[iMax] - analogValue[iMax]/THRESHOLD, 0, 255);
      // timestamp
      time_on = millis();
    }
    /*if (analogValue[iMax] < -THRESHOLD[iMax]) {
      // turn on blue led fast
      anger_b[iMax] = constrain(anger_b[iMax] - 3*analogValue[iMax]/THRESHOLD[iMax], 0, 255);
      // turn down red led slow
      // anger_r[iMax] = constrain(anger_r[iMax] + analogValue[iMax]/THRESHOLD, 0, 255);
      // timestamp
      time_on = millis();
    }*/
  //}
  
  /* Adjust threshold if too much noise */
  //int NoiseThres = THRESHOLD;
  if (abs(analogValue[0]) > 2*THRESHOLD[0] && (abs(analogValue[1]) > 2*THRESHOLD[1] && abs(analogValue[2]) > 2*THRESHOLD[2]))
  {
    // turn off leds if too much current being consumed 
    for (int i = 0; i < n_mics; i++)
    {
      // turn leds down fast
      anger[i] = constrain(anger[i]/5, 0, 255);
      //anger_b[i] = constrain(anger_b[i]/5, 0, 255);
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
      anger[i] = constrain(anger[i] - 1, 0, 255);
      //anger_b[i] = constrain(anger_b[i] - 1, 0, 255);
    }
    
    // led state display
    /*if (anger[i] > THRESHOLD[i]){
      strip.setLEDcolor(2*i,RED);
      //strip.setLEDcolor(2*i+1,BLUE);
    }
    else
    {
      strip.setLEDcolor(2*i,BLACK);
    }
    */
    
    if (anger[i] > 200) {
      strip.setLEDcolorPWM(5-2*i, anger[i], 1000-anger[i]*4, 0);
      strip.setLEDcolorPWM(6+2*i, anger[i], 1000-anger[i]*4, 0);
      //delay(100);
      strip.setLEDcolorPWM(4-2*i, anger[i], 1000-anger[i]*4, 0);
      strip.setLEDcolorPWM(7+2*i, anger[i], 1000-anger[i]*4, 0);
    }
    else if (anger[i] > 150) {
      strip.setLEDcolorPWM(5-2*i, anger[i]*4-600, anger[i], 0);
      strip.setLEDcolorPWM(7+2*i, anger[i]*4-600, anger[i], 0);
      //delay (100);
      strip.setLEDcolorPWM(4-2*i, anger[i]*4-600, anger[i], 0);
      strip.setLEDcolorPWM(6+2*i, anger[i]*4-600, anger[i], 0);
    }
    else if (anger[i] > 100) {
      strip.setLEDcolorPWM(5-2*i, 0, anger[i], 300-anger[i]*2);
      strip.setLEDcolorPWM(7+2*i, 0, anger[i], 300-anger[i]*2);
      //delay (100);
      strip.setLEDcolorPWM(4-2*i, 0, anger[i], 300-anger[i]*2);
      strip.setLEDcolorPWM(6+2*i, 0, anger[i], 300-anger[i]*2);
    }
    else if (anger[i] > 50) {
      strip.setLEDcolorPWM(5-2*i, 0, anger[i]*2-100, anger[i]);
      strip.setLEDcolorPWM(7+2*i, 0, anger[i]*2-100, anger[i]);
      //delay (100);
      strip.setLEDcolorPWM(4-2*i, 0, anger[i]*2-100, anger[i]);
      strip.setLEDcolorPWM(6+2*i, 0, anger[i]*2-100, anger[i]);
    }
    else {
      strip.setLEDcolorPWM(4-2*i, 0, 0, anger[i]);
      strip.setLEDcolorPWM(7+2*i, 0, 0, anger[i]);
      /*if (anger[i] > 10) {
        delay(100);
      }*/
      strip.setLEDcolorPWM(5-2*i, 0, 0, anger[i]);
      strip.setLEDcolorPWM(6+2*i, 0, 0, anger[i]);
    }
    // send values through serial
    Serial.print(analogValue[i], DEC);
    Serial.print(",\t");
    Serial.print(anger[i], DEC);
    //if (i < n_mics-1)
    //  Serial.print(",");
    //else
      Serial.print(";\t");
  }
  //strip.writeStrip();
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
  /*Serial.print(capValue, DEC);
  Serial.print(",");
  Serial.println(TOUCH_THRESHOLD);*/
  // pause for 10 milliseconds:
  Serial.println();
  delay(10);
}

/*void printStripTiming() {
  // print out what the timing is (for debugging)
  double time = strip.numLEDs();    // each LED
  time *= 8;              // 8 bits of data for each LED;
  time *= strip.getSPIdivider();  // larger dividers = more time per bit
  time *= 1000;           // time in milliseconds
  time /= F_CPU;          // multiplied by how long it takes for one instruction (nverse of cpu)
  
  Serial.print("Time per LED strip write: "); 
  Serial.print(time); Serial.println(" millis");
  
  time *= 100;
  time /= strip.getCPUmax();
  
  Serial.print("Time allowed per interrupt ");
  Serial.print(time);
  Serial.println(" millis");
  
  // get that in Hz
  time = 1000 / time;
  Serial.print("Interrupt freq: "); 
  Serial.print(time);
  Serial.println(" Hz");

  // Now find the final 'color cycle' frequency
  Serial.print("Color cycle freq: "); 
  Serial.print(time / (1 << strip.getPWMbits()));
  Serial.println(" Hz");
  // Try to keep the color frequency above 60 Hz (flickery). 100 Hz or higher looks good to most people
}
*/

