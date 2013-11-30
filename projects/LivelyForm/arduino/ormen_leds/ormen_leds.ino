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
int reset = 0;

int leds[] = {
  2,3,4,5,7,8,9,10,11,12,14,15,16,17};
int led_colors[14] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pwm_values[14];

//--------------------------------------------------------------------------------------------------

void setup()   {                
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent);
  
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);

  Serial.begin(115200);

  for(int i = 2; i < 18; i++){
    if(i != 6 || i != 13){
      pinMode(i, OUTPUT);
    }
  }

  for(int i = 0; i < 14; i++){
    pwm_values[i] = 0;
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

  for(int i = 0; i < 14; i++){
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
  
  if(reset == 1){
    switch(timed_state){
    case 0:
      noTouch();
      break;

    case 1:
      touch();
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
  for(int i = 0; Wire.available(); i++)    // slave may send less than requested 
  {
    c[i] = Wire.read();                 // receive a byte as character 
  }
  sscanf(c, "%d %d %d", &rot_counter, &timed_state, &reset);
  if (DEBUG)
    Serial.println(rot_counter);
}

//--------------------------------------------------------------------------------------------------
//When nobody is nearby. Curled up and pulsing slowly.

void noTouch(){

  if(rot_counter >= counter_closed){      //Curled up completely, pulse LEDs
    //Pulse LEDs
    for(int i = 0; i < 7; i++){
      pwm_values[i*2+1] = (pwm/3);
      pwm_values[i*2] = pwm;
    }
    pwm += dir;

    if(pwm >= maxBrightness/2 || pwm <= 10){
      dir *= -1;
    }

    delay(50);
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

void colors(){
  //Set the colors
  //Section 1:
  if((millis() - touch_start) < cycle_time){
    if (DEBUG)
      Serial.println("Section 1");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = 0;      //Green LEDs
    }
  }
  //Section 2:
  else if((millis() - touch_start) < cycle_time*2){
    if (DEBUG)
      Serial.println("Section 2");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = map(millis()-(touch_start + cycle_time), 0, cycle_time,0,255);      //Green LEDs
    }
  }
  //Section 3:
  else if((millis() - touch_start) < cycle_time*3){
    if (DEBUG)
      Serial.println("Section 3");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 4:
  else if((millis() - touch_start) < cycle_time*4){
    if (DEBUG)
      Serial.println("Section 4");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = map(millis()-(touch_start + cycle_time*3), 0, cycle_time,255,0);  //Red LEDs
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 5:
  else if((millis() - touch_start) < cycle_time*5){
    if (DEBUG)
      Serial.println("Section 5");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = 0;  //Red LEDs
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 6:
  else if((millis() - touch_start) < cycle_time*6){
    if (DEBUG)
      Serial.println("Section 6");
    for(int i = 0; i < 7; i++){
      led_colors[i*2+1] = map(millis()-(touch_start + cycle_time*5), 0, cycle_time,0,255);  //Red LEDs
      led_colors[i*2] = map(millis()-(touch_start + cycle_time*5), 0, cycle_time,255,0);      //Green LEDs
    }
  }
  //Start over:
  else{
    touch_start = millis();
  }

  //Do the Knight Rider trick
  for(int i = 0; i < 7; i++){

    for(int j = 0; j < 14; j++){
      pwm_values[j] /= 1.5;              //Meget grov fade-effekt, kan godt laves bedre.
    }

    pwm_values[i*2+1] = map(led_colors[i*2+1],0,255,0,maxBrightness);    //Red LEDs
    pwm_values[i*2] = map(led_colors[i*2],0,255,0,maxBrightness);      //Green LEDs
    delay(cycle_speed);
  }

  //Increase speed of colorchanging
  if(cycle_time > max_speed){
    cycle_time -= 20;
  }
  if (DEBUG) {
    Serial.print("Cycle time is: ");
    Serial.println(cycle_time);
  }
}

//--------------------------------------------------------------------------------------------------
//Turns on LEDs according to how open the worm is.

void move(int input){
  input = map(input,1,counter_closed,140,0);
  pwm_values[0] = maxBrightness;
  pwm_values[1] = maxBrightness/3;

  for(int i = 2; i <= 7; i++){
    pwm_values[i*2-2] = (maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40);
    pwm_values[i*2-1] = ((maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40))/3;
  }
}

//--------------------------------------------------------------------------------------------------

void reset_leds(){
  if(timed_state == 0){
    for(int i = 0; i < 14; i++){
      pwm_values[i] = 0;
    }
  }
  else{
    for(int i = 0; i < 14; i++){
      pwm_values[i] = maxBrightness;
    }
  }
}


