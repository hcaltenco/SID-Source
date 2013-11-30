//master MHMH
////////////////////////////////////////////////////// 
#include <Wire.h>
#include <Statistic.h> 
#include <Accelerometer.h>
//#include <Pummer.h>
#include <MultiPWM.h>
#include <hsv2rgb.h>

#define nB 4 // number of arduino boards counting the master
#define MASTER_ID 0 // the ID number of this board on the i2c bus
#define CAL_PIN 11 // the calibration pin

boolean use_anger = true; // use anger or just data diferences
boolean use_tilt = true; // use tilt or acceleration differences

char  x[nB],  y[nB],  z[nB],  g[nB],  p[nB],  r[nB]; // data arrays
char dx[nB], dy[nB], dz[nB], dg[nB], dp[nB], dr[nB]; // dev arrays
char  dxM, dyM, dzM, dgM, dpM, drM;  // dev data for master
float xAv, yAv, zAv, gAv, pAv, rAv;  // averages
float xSD, ySD, zSD, gSD, pSD, rSD;  // standard deviations

float magn[nB];
char o_delay[nB];
float last_magn = 0.0; 
int outlier = nB;
int anger = 0;
boolean cal_flag = true;

/* create class objects for the master */
Accelerometer accel = Accelerometer(0, 1, 2); //(Xpin,Ypin,Zpin);
Statistic xs, ys, zs, gs, ps, rs;       // statistics objects

//////////////////////////////////////////////////////

#define ledBrightness 99
#define ledFreq 60
#define n_rgbs 3	// number of rgb leds

int r1 =  4, g1 = 2, b1 = 3;
int r2 =  7, g2 = 5, b2 = 6;
int r3 = 10, g3 = 8, b3 = 9;
int Pins[] = {r1,g1,b1,r2,g2,b2,r3,g3,b3};

unsigned long timer_start = 0;
int nPins = sizeof(Pins)/sizeof(int);

//Pummer pummer = Pummer(6,3,5,true); //(Rpin,Gpin,Bpin,common_anode?)
MultiPWM myleds = MultiPWM(Pins, nPins, true);
//////////////////////////////////////////////////////
void setup() 
{ 
  Wire.begin();        // join i2c bus (address optional for master) 
  Serial.begin(9600);  // start serial for output

  /* the calibration button */
  pinMode(CAL_PIN, INPUT); 
  digitalWrite(CAL_PIN, HIGH); // internal pullup
  
  /* RGB led common annode pin */
  //pinMode(4, OUTPUT);
  //digitalWrite(4, HIGH);

    myleds.Start(ledFreq, ledBrightness);
	myleds.SetAll(0);
} 
//----------------------------------------------------
void loop() 
{ 
  /* set calibration flag if button pressed */
  if (LOW == digitalRead(CAL_PIN))
	  cal_flag = true;
  
  if (cal_flag) {
    if (use_tilt) {
      accel.calibrate(2);
	}
    else {
      accel.calibrate();
	}
    byte flags[] = {true, use_anger, use_tilt};
    for (int b=0; b<nB; b++) {
      sendToSlave(b, flags, sizeof(flags));
    }
	Serial.println("device calibrated");
	cal_flag = false;
  }
  
  /* first grab data from the master and add to stats */
  getAccelData(MASTER_ID);
  addToStats(MASTER_ID); // add statistics data for master 

  /* resquest data from each slave (s) and add to stats */
  for (int s = 1; s < nB; s++) {
    recieveFromSlave(s, 6); // recieve data
    addToStats(s);          // add to statistic objects
  }
  
  /* calculate the means and standard deviations */
  updateStats();
  
  /* find the deviation and deviation's magnitude of   
     acceleration data for each board depending on use_tilt */
  //float magn[nB];              // accel magnitudes
  //Statistic magns;             // magnitude statistics
  for (int b = 0; b < nB; b++) {
    findDeviation(b);
    magn[b] = getMagnitude(b); // includes use_tilt
  //  magns.add(magn[b]);        
  }
    
  /* find the outlier depending on the magnitude */
  //outlier = findOutlierSD(magn, magns.average(), magns.pop_stdev(), 1.5);
  //outlier = findOutlierMAD(magn, 2);
  outlier = findOutlier(magn, 25);
  findDelays(outlier);
  
  /* send the data and flags array to the corresponding slave
     or use it for the master */
//  if (0 <= outlier && outlier < nB) { //a slave was the outlier
    byte sendval[] = {dx[outlier], dy[outlier], dz[outlier], 
                      dg[outlier], dp[outlier], dr[outlier],
					  outlier, 0};
//	for (int i=0; i<3; i++){
	for (int b=1; b<nB; b++) {
//		if (o_delay[b]==0) {
//			if (b > 0) {
		sendval[7] = o_delay[b]*125;
		sendToSlave(b, sendval, sizeof(sendval));
//			}
			//else {
			//	updateDevs(outlier);
			//	if (magn[outlier] >= last_magn && use_anger)
			//	  anger += (int) (magn[outlier]/4);
			//	last_magn = magn[outlier];
			//}
//		}
//		o_delay[b]--;
//		delay(100);
//	}
//	}
  }
  //if (outlier == MASTER_ID) { // master was the outlier
  if (outlier < nB) { // there was an outlier
    updateDevs(outlier);
    if (magn[outlier] >= last_magn && use_anger)
      anger += (int) (magn[outlier]/4);
    last_magn = magn[outlier];
	
    delay(o_delay[MASTER_ID]*125);
  }

  showState();
  
  printToSerial();  
  clearStats();
  //magns.clear();
  delay(20); 
}

//-----------------------------------------------------

ISR(TIMER1_COMPA_vect) {
	myleds.HandleInterrupt();
}

