/**********************************************/
// scroll a rainbow!
void rainbowParty(uint8_t wait) {
  uint8_t i, j;

  for (i=0; i< strip.numLEDs(); i+=6) {
    // initialize strip with 'rainbow' of colors
    strip.setLEDcolor(i, RED);
    strip.setLEDcolor(i+1, YELLOW);
    strip.setLEDcolor(i+2, GREEN);
    strip.setLEDcolor(i+3, TEAL);
    strip.setLEDcolor(i+4, BLUE);
    strip.setLEDcolor(i+5, VIOLET);
 
  }
  strip.writeStrip();   
  
  for (j=0; j < strip.numLEDs(); j++) {

    // now set every LED to the *next* LED color (cycling)
    uint8_t savedcolor = strip.getLEDcolor(0);
    for (i=1; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i-1, strip.getLEDcolor(i));  // move the color back one.
    }
    // cycle the first LED back to the last one
    strip.setLEDcolor(strip.numLEDs()-1, savedcolor);
    strip.writeStrip();
    delay(wait);
  }
}

/**********************************************/
// turn everything off (fill with BLACK)
void stripOff(void) {
  // turn all LEDs off!
  for (uint8_t i=0; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i, BLACK);
  }
  strip.writeStrip();   
}

/**********************************************/
// have one LED 'chase' around the strip
void chaseSingle(uint8_t color, uint8_t wait) {
  uint8_t i;
  
  // turn everything off
  for (i=0; i< strip.numLEDs(); i++) {
    strip.setLEDcolor(i, BLACK);
  }

  for (i=0; i < strip.numLEDs(); i++) {
    strip.setLEDcolor(i, color);
    if (i != 0) {
      // make the LED right before this one OFF
      strip.setLEDcolor(i-1, BLACK);
    }
    strip.writeStrip();
    delay(wait);  
  }
  // turn off the last LED before leaving
  strip.setLEDcolor(strip.numLEDs() - 1, BLACK);
}

/**********************************************/
// fill the entire strip, with a delay between each pixel for a 'wipe' effect
void colorWipe(uint8_t color, uint8_t wait) {
  uint8_t i;
  
  for (i=0; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i, color);
      strip.writeStrip();   
      delay(wait);
  }
}

/**********************************************/

unsigned int advanceSingle(int led_step) {
  static int last_on = -1;
  int new_on;
  int led_to_light;
  
  // set led to light according to direction
  if (led_step > 0)
    led_to_light = 2;
  else
    led_to_light = 1;

  // turn last led off
  strip.setLEDcolor(last_on, BLACK);
  
  // select new led to turn on
  new_on = last_on + led_step;
  if (new_on >= strip.numLEDs())
    new_on = 0;
  else if (new_on < 0)
    new_on = 15;
  last_on = new_on;
  
  // select color and light led;
  int color = chooseColor(new_on, led_to_light);
  strip.setLEDcolor(new_on, color);
  strip.writeStrip();
  
  return new_on;
}

/**********************************************/
// scroll a rainbow!
void playerParty(int player, int wait, int how_long) {
  int start_led = player * 4;
  
  // write a color list that will by cycled
  int colorList[] = {RED, YELLOW, GREEN, TEAL, BLUE, VIOLET};
  int nColors = sizeof(colorList)/sizeof(int);
  
  long t = millis();
  
  while (millis() - t < (long) how_long) {
    for (int j = 0; j < 4; j++) {
      // now set every LED to the *next* LED color (cycling)
      int saved_color = colorList[0];
      for (int i=1; i < nColors; i++) {
        colorList[i-1] = colorList[i];  // move the color back one.
      }
      colorList[nColors-1] = saved_color;
      
      // assign color to led
      strip.setLEDcolor(start_led + j, colorList[j]);
      
    }
    strip.writeStrip();
    delay(wait);
  }
}


