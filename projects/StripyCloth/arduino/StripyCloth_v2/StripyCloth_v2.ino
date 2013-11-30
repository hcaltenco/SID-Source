/* Stripy Cloth test code
 * by Hector Caltenco, Certec, LTH
 * December 2012
 * Uses:
 * - El Escudo Dos Shield from Sparkfun
 * - Mux Shield from Mayhew Labs
 * Code based on:
 * - Mux_Shield_AnalogIn_Example    http://mayhewlabs.com/arduino-mux-shield
 * - Test sketch for El Escudo Dos  Mike Grusin, SparkFun Electronics
 * - CapitiveSense Library Demo     Paul Badger 2008
*/

//Includes
//#include <CapSense.h>


//Give convenient names to the MUX shield control pins
//#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

//Define the input pins in the Mux shield
const int PRESSPIN = A0;  
const int ACCELPIN = A1;  

//Define the capsense pins -> cannot be used by EL Escudo
//const int CSTXPIN = 12;
//const int CSRXPIN[] = {0, 1, 11};

//Define the EL wire pins: should have PWM output
const int ELPIN[] = {5, 6, 9};

//Define the speaker output pin: should have PWM output
const int SPEAKPIN = 13;

//Define Status LED pins
#define STATPIN  10
//#define STATPIN1  13

//Define the number of pins for each input or output type
const int nPreSens = 5;
const int nAccSens = 3;
//const int nCapSens = sizeof(CSRXPIN)/sizeof(int);
const int nWires   = sizeof(ELPIN)/sizeof(int);
const int nSamples = 10;

// thresholds
//const int CAPS_THRES  = 600;
const int PRESS_THRES = 200;
const int ACCEL_THRES = 500;
const int TIME_THRES  = 1000;
const int BRIGHT_LOW  = 50;
const int BRIGHT_HIGH = 200;
const int BRIGHT_MAX  = 255;
const int BRIGHT_STEP = 10;
const int BLINK_MIN   = 100;
const int BLINK_MAX   = 1000;
const int BLINK_THRES = 600;
const int BLINK_STEP  = 10;

//Create arrays for data from the the sensors
int press_array[nPreSens]; // up to 1023
int accel_array[nAccSens]; // up to 1023
int accel_base[nAccSens] = {512}; // half of 1023
//int caps_array[nCapSens]; // up to 1023
//long caps_base[nCapSens] = {0};
//long caps_max[nCapSens] = {0};
byte brightness[nWires] = {0};
boolean thres_achieved[nWires] = {false};

// last and current active sensors
int active_caps;
int active_press;
int last_caps;
int last_press;
int active_accel;
int last_accel;

// timers
unsigned long start_touch;
unsigned long start_press;
unsigned long start_shake;

// Capsense Objects: 10M resistor between pins TX and RX
//CapSense cs[] = {
//  CapSense(CSTXPIN, CSRXPIN[0]),
//  CapSense(CSTXPIN, CSRXPIN[1]),
//  CapSense(CSTXPIN, CSRXPIN[2])
//};

// StripyCloth states
enum state{
  IDLE = 0,
  TOUCH,
  CARESS,
  PRESS,
  KNEED,
  SWING,
  WAVE
};

state current_state = IDLE;
state last_state = IDLE;


//--------------------------------------------------------------------------------------

void setup()
{
  //Set MUX control pins as outputs
  //pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  
  // Set ELWire pins as outputs
  for (int i=0; i<nWires; i++) {
    pinMode(ELPIN[i], OUTPUT);
  }
  
  // Set StatusLED pins as outputs
  pinMode(STATPIN, OUTPUT);     
  
  //Calibrate the accelerometer
  for (int i=0; i<nAccSens; i++)
  {
    setControlPins(i);
    accel_base[i] = analogRead(ACCELPIN);
  }

  //Calibrate the capsense
//  for (int i=0; i<nCapSens; i++)
//  {
//    cs[i].set_CS_Timeout_Millis(500);
//    caps_base[i] = cs[i].capSense(nSamples);
//    caps_max[i]  = caps_base[i]*3;
//  }
  
  //Open the serial port at 28800 bps
  Serial.begin(115200);
  
}

//------------------------------------------

void loop()
{
  // update last active sensors
  last_caps  = active_caps;
  last_press = active_press;
  last_accel = active_accel;
  
  // update the last state
  last_state = current_state;
  
  // read sensors data
  long daq_time = readSensors();
  
  // find active sensors
  //active_caps  = findActive(&caps_array[0], nCapSens, CAPS_THRES);
  active_press = findActive(&press_array[0], nPreSens, PRESS_THRES);
  active_accel = milligee();
  
  // update state
  updateState();
  
  // run state function
  switch(current_state)
  {
    case IDLE:
      idle();
      break;
    
    case TOUCH:
      //touch();
      break;
    
    case CARESS:
      //caress();
      break;
      
    case PRESS:
      press();
      break;
    
    case KNEED:
      kneed();
      break;
    
    case SWING:
      swing();
      break;
    
    case WAVE:
      swing();
      if (active_press)
        kneed();
      //else if (active_caps)
      //  caress();
      break;
      
  }
  
  
  // Print readings
  printReadings();
  
  // Print the overal performance
  Serial.print("elapsed time:\t");
  Serial.println(daq_time);
  
  // Print the state
  Serial.print("state: \t");
  Serial.println(current_state);
  
  // Print the output
  Serial.print("Wire brighness: \t");
  printWires();
  
  //delay(daq_time*10);
  delay(100);
}



