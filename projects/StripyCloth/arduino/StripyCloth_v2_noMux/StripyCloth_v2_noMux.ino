/* Stripy Cloth test code
 * by Hector Caltenco, Certec, LTH
 * June 2013
 * Uses:
 * - El Escudo Dos Shield from Sparkfun
 * - Mux Shield from Mayhew Labs
 * Code based on:
 * - Mux_Shield_AnalogIn_Example    http://mayhewlabs.com/arduino-mux-shield
 * - Test sketch for El Escudo Dos  Mike Grusin, SparkFun Electronics
*/

//Includes


//Give convenient names to the MUX shield control pins
//#define CONTROL0 5    
//#define CONTROL1 4
#define CONTROL0 4
#define CONTROL1 2

//Define the input pins in the Mux shield
const int PRESSPIN = A1;  
const int ACCELPIN = A0;  

//Define the EL wire pins: should have PWM output
const int ELPIN[] = {3, 6, 9};

//Define the speaker output pin: should have PWM output
const int SPEAKPIN = 7;

//Define the vibration output pin: should have PWM output
const int VIBPIN = 11;

//Define Status LED pins
#define STATPIN  10
//#define STATPIN1  13

//Define the number of pins for each input or output type
const int nPreSens = 5;
const int nAccSens = 3;
const int nWires   = sizeof(ELPIN)/sizeof(int);
const int nSamples = 10;

// thresholds
const int PRESS_THRES = 200;
const int ACCEL_THRES = 500;
const int ACCEL_HIGH  = 1500;
const int TIME_THRES  = 1000;
const int BRIGHT_LOW  = 50;
const int BRIGHT_HIGH = 200;
const int BRIGHT_MAX  = 230;
const int BRIGHT_STEP = 10;
const int BLINK_MIN   = 100;
const int BLINK_MAX   = 1000;
const int BLINK_THRES = 600;
const int BLINK_STEP  = 10;

//Create arrays for data from the the sensors
int press_array[nPreSens]; // up to 1023
int accel_array[nAccSens]; // up to 1023
int accel_base[nAccSens] = {512}; // half of 1023
byte brightness[nWires] = {0};
boolean thres_achieved[nWires] = {false};
int s_pitch = 300;

// last and current active sensors
int active_press;
int last_press;
int active_accel;
int last_accel;

// timers
unsigned long start_press;
unsigned long start_shake;

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

state current_state_a = IDLE;
state current_state_p = IDLE;
state last_state_a = IDLE;
state last_state_p = IDLE;


//--------------------------------------------------------------------------------------

void setup()
{
  //Set MUX control pins as outputs
  //pinMode(CONTROL0, OUTPUT);
  //pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL0, OUTPUT);
  
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

  //Open the serial port at 28800 bps
  Serial.begin(115200);
  
}

//------------------------------------------

void loop()
{
  // update last active sensors
  last_press = active_press;
  last_accel = active_accel;
  
  // update the last state
  last_state_a = current_state_a;
  last_state_p = current_state_p;
  
  // read sensors data
  long daq_time = readSensors();
  
  // find active sensors
  active_press = findActive(&press_array[0], nPreSens, PRESS_THRES);
  active_accel = milligee();
  
  // update state
  updateState();
  
  // run state functions
  switch(current_state_a)
  {
    case IDLE:
      //idle();
      break;
    
    case SWING:
      swing();
      break;
    
    case WAVE:
      wave();
      break;
  }

  switch(current_state_p)
  {
    case IDLE:
      idle();
      break;
    
    case PRESS:
      press();
      break;
    
    case KNEED:
      kneed();
      break;
  }
  
  // Print readings
  printReadings();
  
  // Print the overal performance
  Serial.print("elapsed time:\t");
  Serial.println(daq_time);
  
  // Print the output
  printWires();
  printSound();
  
  Serial.println();
  
  digitalWrite(STATPIN, thres_achieved[2]);
  //delay(daq_time*10);
  delay(100);
}



