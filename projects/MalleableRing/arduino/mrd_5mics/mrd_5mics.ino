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

#define n_leds 64

//int micPins[] = {A3, A1, A2, A4, A5};  // select the input pin for the mic
int micPins[] = {A5, A4, A2, A1, A3};

//int sensorPin = 7;   //Måske skal pin 9 og 10 byttes om,
//int sendPin = 8;     //jeg kan ikke huske den præcise opsætning
//int thresholdPin = A3;

const int n_mics = sizeof(micPins)/sizeof(int);
int analogValue[n_mics];
int base[n_mics];

int n_ledgroups = round(n_leds/(2*n_mics));

int MIN_TIME_ON = 100; // minimum time for the led to be on
int THRES = 85;
int THRESHOLD[] = {THRES, THRES, THRES, THRES, THRES};
//int TOUCH_THRESHOLD = 20;

int ANGER_SPEED = 20;
int FADE_SPEED = 5;

//CapSense cs = CapSense(sendPin,sensorPin);
//HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, 6);
HL1606stripPWM strip = HL1606stripPWM(n_leds, STRIP_L);

void setup() {                
  // start serial port at 9600 bps:
  Serial.begin(19200);//9600);
  
  // ONLY FOR stripPWM
  strip.setPWMbits(5);
  strip.setSPIdivider(16);
  strip.setCPUmax(70);    // 70% is what we start at
  strip.begin();
  
  printStripTiming();
  
}

void loop() {
  static unsigned long time_on[n_mics];
  static byte anger[n_mics];
  
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
    
  }
  
  /* if touching allow to anger device */
  //if (capValue > TOUCH_THRESHOLD) {
    /* turn leds of active mic if over threshold */
    if (abs(analogValue[iMax]) > THRESHOLD[iMax]) {
      // turn on red led fast
      anger[iMax] = constrain(anger[iMax] + ANGER_SPEED*abs(analogValue[iMax])/THRESHOLD[iMax], 0, 255);
      // timestamp
      time_on[iMax] = millis();
    }
  //}
  
  
  /* display led status */
  for (int i = 0; i < n_mics; i++ ) {
    if ((millis() - time_on[i]) > MIN_TIME_ON) {
      // turn leds down slowly
      anger[i] = constrain(anger[i] - FADE_SPEED, 0, 255);
    }
    
    // led state display
    int MP = n_leds/2; // middlepoint
    int nlg = n_ledgroups;
    int et = 0;
    
    if (i== n_mics - 1)
    {
      //nlg = nlg + 1;
      et = 2;
    }
        
    if (anger[i] > 200) {
      for (int j=-nlg-et; j<0; j++) { 
        strip.setLEDcolorPWM((MP+j)-nlg*i, anger[i], 1000-anger[i]*4, 0);
      }
      for (int j=0; j<nlg+et; j++) {
        strip.setLEDcolorPWM((MP+j)+nlg*i, anger[i], 1000-anger[i]*4, 0);
      }
    }
    else if (anger[i] > 150) {
      for (int j=-nlg-et; j<0; j++) { 
        strip.setLEDcolorPWM((MP+j)-nlg*i, anger[i]*4-600, anger[i], 0);
      }
      for (int j=0; j<nlg+et; j++) {
        strip.setLEDcolorPWM((MP+j)+nlg*i, anger[i]*4-600, anger[i], 0);
      }
    }
    else if (anger[i] > 100) {
      for (int j=-nlg-et; j<0; j++) { 
        strip.setLEDcolorPWM((MP+j)-nlg*i, 0, anger[i], 300-anger[i]*2);
      }
      for (int j=0; j<nlg+et; j++) {
        strip.setLEDcolorPWM((MP+j)+nlg*i, 0, anger[i], 300-anger[i]*2);
      }
    }
    else if (anger[i] > 50) {
      for (int j=-nlg-et; j<0; j++) { 
        strip.setLEDcolorPWM((MP+j)-nlg*i, 0, anger[i]*2-100, anger[i]);
      }
      for (int j=0; j<nlg+et; j++) {
        strip.setLEDcolorPWM((MP+j)+nlg*i, 0, anger[i]*2-100, anger[i]);
      }
    }
    else {
      for (int j=-nlg-et; j<0; j++) { 
        strip.setLEDcolorPWM((MP+j)-nlg*i, 0, 0, anger[i]);
      }
      for (int j=0; j<nlg+et; j++) {
        strip.setLEDcolorPWM((MP+j)+nlg*i, 0, 0, anger[i]);
      }
    }
    // send values through serial
    Serial.print(analogValue[i], DEC);
    Serial.print(",\t");
    Serial.print(anger[i], DEC);
    Serial.print(";\t");
  }
  Serial.println();
  
  // send capsense value through serial
  /*Serial.print(capValue, DEC);
  Serial.print(",");
  Serial.println(TOUCH_THRESHOLD);*/
  
  // pause for 10 milliseconds:
  delay(10);
}

void printStripTiming() {
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


