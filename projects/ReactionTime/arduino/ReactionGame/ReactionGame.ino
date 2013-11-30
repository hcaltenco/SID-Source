/*
This is the HugBag code using HL1606-based digital LED strips. 
 It uses my modified Adafruits HL1606strip library to control 
 the addressable leds. Blue and green addresses are interchanged
 
 The strip is controlled by analog read of a stretch sensor.
 
 Hector Caltenco
 SID project
 2012-05-23
 */


// HL1606strip is an adaptation of LEDstrip from  http://code.google.com/p/ledstrip/
#include "HL1606strip.h"

// use -any- 3 pins!
#define STRIP_D 4
#define STRIP_C 3
#define STRIP_L 2

// select the input pin for the buttons
int sPins[] = {6, 7, 9, 10};
const int nSens = sizeof(sPins)/sizeof(int);

// global state variables
boolean allow_press = false;
boolean change_dir = false;
boolean already_pressed = false;

// time_change is the number of milliseconds to add upon
// failure or subtract upon success.
// colorswitch_delay is the amount of time that the LED stays
// on. This value has time_change added to/subtracted from it.
// So that the user knows which LED was lit up when they hit
// the button, push_pause defines the number of milliseconds
// that the LED will stay on after the button is pressed.
unsigned int time_change       =  100 ;
unsigned int initial_delay     = 800;
unsigned int max_delay         = 1000;
unsigned int push_pause        = 1000;
unsigned int win_pause         = 10000 ;
unsigned int ledswitch_delay[nSens];

// Pin S is not really used in this demo since it doesnt use the built in PWM fade
// The last argument is the number of LEDs in the strip. Each chip has 2 LEDs, and the number
// of chips/LEDs per meter varies so make sure to count them! if you have the wrong number
// the strip will act a little strangely, with the end pixels not showing up the way you like
HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, 16);


void setup(void) {
  //Serial.begin(9600);
  
  // generate random numbers according to random noise from unconnected pin A0
  randomSeed(analogRead(0));
  
  // push button pins
  for (int i=0; i<nSens; i++) {
    pinMode(sPins[i], INPUT);
    ledswitch_delay[i] = initial_delay;
  }
  
  // led strip off before stargint
  stripOff();
}

/**********************************************/

void loop(void) {
  // static variables
  static int last_player = 0;
  static int led_steps = 1;
  
  unsigned long t = millis();

  // turn on leds one by one
  change_dir = false;
  int curr_led = advanceSingle(led_steps);
  
  // get current player
  int player = getCurrentPlayer(curr_led);
  if (player != last_player) {
    already_pressed = false;
    last_player = player;
  }
  
  // check if button is pressed every 10 milliseconds
  while (millis() - t < ledswitch_delay[player]) {
    int pressed = checkButtonPressed(player, curr_led);
    if (pressed) {
      if (change_dir) {
        led_steps = -1 * led_steps;
      }
      already_pressed = true;
      delay(push_pause);
    }
    delay (10);
  }
}

/**********************************************/

boolean checkButtonPressed(int player, int curr_led) {
  boolean button_pressed = false;
  
  if (digitalRead(sPins[player]) == LOW && already_pressed == false) {
    if (allow_press) {
      if (ledswitch_delay[player] > time_change) {
        strip.setLEDcolor(curr_led, WHITE);
      }
      else {
        playerParty(player, time_change, win_pause);
        for (int i = 0; i < sizeof(ledswitch_delay)/sizeof(int); i++) {
          ledswitch_delay[i] = initial_delay;
        }
        stripOff();
      }
      ledswitch_delay[player] -= time_change;
    }
    else {
      strip.setLEDcolor(curr_led, YELLOW);
      if (ledswitch_delay[player] < max_delay) {
        ledswitch_delay[player] += time_change;
      }
    }
    button_pressed = true;
    strip.writeStrip();
  }
  return button_pressed;
}

/**********************************************/

int getCurrentPlayer(int currLed) {
  double player = currLed / 4;
  return floor(player);
}

/**********************************************/

int chooseColor(int new_on, int led_to_light){
  int color;
  
  if (new_on % 4 == led_to_light) {
    if (random(100) > 80) {
      color = BLUE;
      change_dir = true;
    }
    else {
      color = RED;
      allow_press = true;
    }
  }
  else{
    color = GREEN;
    allow_press = false;
  }
  return color;
}


