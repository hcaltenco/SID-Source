/******************************************************************************
 * This example uses shift registers to PWM many outputs in software. All
 * shift registers are placed in series, so they can be driven with 3 pins.
 * A touch_start interrupt updates all PWM outputs, based on a global array of
 * PWM values called ledStates.
 * The outputs can be inverted by a #define. Comment this to disable inverting.
 * The interrupt load determines the maximum number of LED's and PWM resolution.
 * 
 * The following calcuations apply:
 * Interrupt time = Number of outputs * 18 + 100. (=worst case, *17 if outputs are 0)
 * Interrupt frequency = led frequency * PWM resolution
 * Interrupt load = interrupt_time * interrupt_freq / clock frequency.
 * This example:
 * 72 Leds, 60 Hz, 100 levels:
 * Interrupt frequency = 6 kHz, Interrupt time = 1396 clock cycles, load = 0.52
 *
 * Elco Jacobs, E-atelier Industrial Design TU/e, 3 November 2010.
 *****************************************************************************/

#include <Wire.h> 

#define maxBrightness 99
#define ledFreq 60
#define nLeds 14
#define nSens 4

boolean DEBUG = false;

static unsigned char pwm_counter;

int R1 = 17;
int G1 = 16;
int R2 = 15;
int G2 = 14;
int R3 = 12;
int G3 = 11;
int R4 = 10;
int G4 = 9;
int R5 = 8;
int G5 = 7;
int R6 = 5;
int G6 = 4;
int R7 = 3;
int G7 = 2;

int dir = 1;
int pwm = 10;
int rot_counter = 0;             //Holds the value read from the rotary encoder
int timed_state = 0;             //State that tells if the worm is touched or not
int cycle_speed = 120;           //The speed of the Knight Rider effect
int cycle_time = 5000;           //Initial time between colorchanges
int max_speed = 500;             //Minimum time between colorchanges;
int counter_closed = 150;        //Counter number when curled completely up (also change it in "ormen_motor")
unsigned long touch_start = 0;
unsigned long speed_timer = 0;
boolean reset = true;

int leds[] = {
  G7,R7,G6,R6,G5,R5,G4,R4,G3,R3,G2,R2,G1,R1};

int led_colors[nLeds] = {0};
int pwm_values[nLeds] = {0};
int touch_sensor = 0;

//--------------------------------------------------------------------------------------------------

void setup()   {                
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent);
  
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);

  Serial.begin(115200);

  for(int i = 0; i < nLeds; i++){
    pinMode(leds[i], OUTPUT);
  }

  /* Setup timer: configure and enable touch_start for a compare and match A interrupt.
   * Configuring the timer is done by setting registry bits to the correct setting. */

  /* Configure touch_start in CTC mode: clear the timer on compare match 
   * See the Atmega328 Datasheet 15.9.2 for an explanation on CTC mode.
   * See table 15-4 in the datasheet. */

  bitSet(TCCR1B,WGM12);
  bitClear(TCCR1B,WGM13);
  bitClear(TCCR1A,WGM11);
  bitClear(TCCR1A,WGM10);


  /*  Select clock source: internal I/O clock, without a prescaler
   *  This is the fastest possible clock source for the highest accuracy.
   *  See table 15-5 in the datasheet. */

  bitSet(TCCR1B,CS10);
  bitClear(TCCR1B,CS11);
  bitClear(TCCR1B,CS12);

  /* The timer will generate an interrupt when the value we load in OCR1A matches the timer value.
   * One period of the timer, from 0 to OCR1A will therefore be (OCR1A+1)/(timer clock frequency).
   * We want the frequency of the timer to be (LED frequency)*(number of brightness levels)
   * So the value we want for OCR1A is: timer clock frequency/(LED frequency * number of bightness levels)-1 */
  
  OCR1A = round(16E6/(ledFreq*(maxBrightness+1)))-1;
  
  /* Finally enable the timer interrupt 
  /* See datasheet  15.11.8) */
  bitSet(TIMSK1,OCIE1A);
  touch_start = millis();
}

//--------------------------------------------------------------------------------------------------

/* Install the Interrupt Service Routine (ISR) for touch_start compare and match A.
 * We can define a function on the interrupt vector that corresponds to this interrupt source.
 * See table  11-1 for the interrupt vectors */
ISR(TIMER1_COMPA_vect) {

  for(int i = 0; i < nLeds; i++){
    digitalWrite(leds[i], pwm_values[i] <= pwm_counter);
  }

  pwm_counter++;

  if(pwm_counter > maxBrightness){
    pwm_counter = 0;
  }
}

//--------------------------------------------------------------------------------------------------
//Manipulate values in pwm_values[] here.

void loop(){
  
  if(!reset){
    switch(timed_state){
    case 0:
      noTouch();
      break;

    case 1:
      touch();
      break;
      
    case 2:
      keep();
      break;
    }
  } 
  else{
    reset_leds();
  }
}

//--------------------------------------------------------------------------------------------------
//Receive and convert data from master.

void receiveEvent(int howMany){
  char c[16] = {0};
//  char touch_str[6] = {0};
  int i = 0;
  while (Wire.available())
  {
      c[i] = Wire.read();                 // receive a byte as character
      i++;
  }
  sscanf(c, "%d %d %d %d", &rot_counter, &timed_state, &touch_sensor, &reset);
    
  if (DEBUG) {
    Serial.print(rot_counter);
    Serial.print('\t');
    Serial.print(timed_state);
    Serial.print('\t');
    Serial.print(reset);
    Serial.print('\t');
    Serial.print(touch_sensor);
    Serial.println();
  }
}

//--------------------------------------------------------------------------------------------------
//When nobody is nearby. Curled up and pulsing slowly.

void noTouch(){

  if(rot_counter >= counter_closed){ //Curled up completely, pulse LEDs
    if (touch_sensor > 0) {
      cycle();
    }
    else {
      pulse_green();
    }
  }
  else{                      //Curling up, light LEDs according to rotary encoder
    move(rot_counter);
  }

  touch_start = millis();    //Reset timer for measuring beginning of touch 
  cycle_time = 5000;         //Reset cycle speed for colorchanges
}

//--------------------------------------------------------------------------------------------------
//When somebody touches it. Opening and Knight-Rider. Fade colors faster by by time.

void touch(){
  if(rot_counter > 0){      //Opening up and lighting LEDs according to rotary encoder
    move(rot_counter);
  }
  else{               //Fully open and doing Knight Rider and changing colors
    colors();
  }
}

//--------------------------------------------------------------------------------------------------
//Multiple sensors are touched

void keep(){
  if(rot_counter > 20){      //Opening up and lighting LEDs according to rotary encoder
    move(rot_counter);
  }
  else{               //Fully open and doing Knight Rider and changing colors
    colors();
  }
}


