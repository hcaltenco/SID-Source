//SLAVE MHMH
////////////////////////////////////////////////////// 
#include <Wire.h> 
#include <Accelerometer.h>
//#include <Pummer.h>
#include <MultiPWM.h>
#include <hsv2rgb.h>

#define SLAVE_ID 3 // 1, 2 or 3 (0 is reserved for master)
boolean use_anger = false; // anger flag is changed through master
boolean use_tilt = false;  // tilt flag is changed through master
boolean cal_flag = false;  // calibration flag is set by master

char  x,  y,  z,  g,  p,  r; // signed byte acceleration data
char dx, dy, dz, dg, dp, dr; // signed byte deviation from mean

float last_magn = 0;
int anger = 0;
int nB = 4;
int outlier = nB;
int o_delay;

/* create accelerometer and pummer objects for THIS slave */
Accelerometer accel = Accelerometer(0, 1, 2); //(Xpin,Ypin,Zpin);

////////////////////////////////////////////////////// 

#define ledBrightness 99
#define ledFreq 60
#define n_rgbs 3	// number of rgb leds

#if (SLAVE_ID == 1)
	int r1 = 4, g1 = 2, b1 = 3;
	int r2 = 5, g2 = 6, b2 = 7;
	int r3 = 8, g3 = 9, b3 = 10;
#else
	int r1 = 2, g1 = 3, b1 = 4;
	int r2 = 5, g2 = 6, b2 = 7;
	int r3 = 8, g3 = 9, b3 = 10;
#endif
int Pins[] = {r1,g1,b1,r2,g2,b2,r3,g3,b3};

unsigned long timer_start = 0;
int nPins = sizeof(Pins)/sizeof(int);

//Pummer pummer = Pummer(6,3,5,true); //(Rpin,Gpin,Bpin,common_anode?)
MultiPWM myleds = MultiPWM(Pins, nPins, true);

//////////////////////////////////////////////////////

void setup() 
{ 
  Wire.begin(SLAVE_ID);         // join i2c bus with address SLAVE_ID 
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  
  /* RGB led common annode pin */
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  myleds.Start(ledFreq, ledBrightness);
  myleds.SetAll(0);
} 
//----------------------------------------------------
void loop() 
{ 
//  showState();
  delay(20);
}

////////////////////////////////////////////////////// 
/* function that executes whenever data is requested by master
 * this function is registered as an event, see setup()
 */ 
void requestEvent()
{
  getAccelData();
  byte acc_data[] = {x, y, z, g, p, r};  // pack values into byte array
  Wire.send(acc_data, sizeof(acc_data)); // respond with packed message
}
//----------------------------------------------------
/* function that executes whenever data is received from master
 * this function is registered as an event, see setup()
 */ 
void receiveEvent(int howMany)
{
  float magn;
  cal_flag = recieveFromMaster(howMany);
  
  if (cal_flag == true) {
    if (use_tilt)
      accel.calibrate(2);
    else
      accel.calibrate();
  }
  else {
	  if (outlier < nB) {
		magn = getMagnitude();
		if (magn > last_magn && use_anger) {
			anger += (int) (magn/4);
		}
		last_magn = magn;
		delay(o_delay);
	  }
  }
  showState();
  printToSerial();
  //delay(20);
}

ISR(TIMER1_COMPA_vect) {
	myleds.HandleInterrupt();
}
