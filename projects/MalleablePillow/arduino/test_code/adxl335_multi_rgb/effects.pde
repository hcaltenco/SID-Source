#include <hsv2rgb.h>

void snore(int snore_speed) {
  static byte pwm_r, pwm_g, pwm_b=160;
  static boolean grow = false;
  if (grow) {
    if (32 < pwm_b) {
      pwm_g = pwm_g + snore_speed;
      pwm_b = pwm_b - snore_speed*2;
    }
    else
      grow = !grow;
  }
  else {
    if (0 < pwm_g) {
      pwm_g = pwm_g - snore_speed;
      pwm_b = pwm_b + snore_speed*2;
    }
    else
      grow = !grow;
  }
  for(int i = 0; i < n_rgbs; i++){
    //SetPWMOf3(i, pwm_r, pwm_g, pwm_b);
	myleds.SetGroupOf3(i, pwm_r, pwm_g, pwm_b);
    delay(100);
  }
}

//-----------------------------------------------------

void showAnger(int cycle_time){
  //int cycle_speed = 150;           //The speed of the Knight Rider effect
  //Set the colors
  byte pwm_r, pwm_g, pwm_b;
  //Section 1:
  if((millis() - timer_start) < cycle_time){
    Serial.println("Section 1");
    pwm_r = map(millis()-(timer_start), 0, cycle_time, 0, 255); //255
    pwm_g = 0;
    pwm_b = 0;
  }
  //Section 2:
  else if((millis() - timer_start) < cycle_time*2){
    Serial.println("Section 2");
    pwm_r = 255;
    pwm_g = map(millis()-(timer_start + cycle_time), 0, cycle_time, 0, 255); //128
    pwm_b = 0;
  }
  //Section 3:
  else if((millis() - timer_start) < cycle_time*3){
    Serial.println("Section 3");
    pwm_r = 255;
    pwm_g = 255;
    pwm_b = 0;
  }
  //Section 4:
  else if((millis() - timer_start) < cycle_time*4){
    Serial.println("Section 4");
    pwm_r = map(millis()-(timer_start + cycle_time*3), 0, cycle_time, 255, 0); //128
    pwm_g = 255;
    pwm_b = 0;
  }
  //Section 5:
  else if((millis() - timer_start) < cycle_time*5){
    Serial.println("Section 5");
    pwm_r = 0;
    pwm_g = map(millis()-(timer_start + cycle_time*4), 0, cycle_time, 255, 0); //255
    pwm_b = 0;
  }
  //Section 6:
//  else if((millis() - timer_start) < cycle_time*6){
//    Serial.println("Section 6");
//    pwm_r = 128; //map(millis()-(timer_start + cycle_time*5), 0, cycle_time, 0, 255);
//    pwm_g = 128; //map(millis()-(timer_start + cycle_time*5), 0, cycle_time, 255, 0);
//    pwm_b = 0;
//  }
  //Start over:
  else{
    timer_start = millis();
  }

  //Do the Knight Rider trick
  int n_steps = 3;
  for(int i = 0; i < n_rgbs; i++){
    // fade in
    for(int j = 1; j < n_steps; j++){
      //SetPWMOf3(i, j*pwm_r/n_steps, j*pwm_g/n_steps, j*pwm_b/n_steps);
		myleds.SetGroupOf3(i, j*pwm_r/n_steps, j*pwm_g/n_steps, j*pwm_b/n_steps);
    }
    // fade out
    for(int j = n_steps; j > 0; j--){
      //SetPWMOf3(i, j*pwm_r/n_steps, j*pwm_g/n_steps, j*pwm_b/n_steps);
		myleds.SetGroupOf3(i, j*pwm_r/n_steps, j*pwm_g/n_steps, j*pwm_b/n_steps);
    }
    delay(cycle_time/10);
    //delay(cycle_speed);
  }
}

//-----------------------------------------------------

void rgbLedRainbow(int numRGBLeds, int delayVal, int shiftStep, int maxBrightness, int rainbowWidth){
  // Displays a rainbow spread over all LED's, which shifts in hue.
  int hue, sat, val; 
  unsigned char red, green, blue;
  static int colorshift;
  if (colorshift < 360) {
  //SetPWMOfAll(0);
  //for(int cycle=0;cycle<numCycles;cycle++){ // shift the raibom numCycles times
  //  for(int colorshift=0;colorshift<360;colorshift=colorshift+shiftStep){ // Shift over full color range (like the hue slider in photoshop)
      for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
        hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
        sat = 255;
        val = 255;
        hsv2rgb(hue, sat, val, &red, &green, &blue, maxBrightness); // convert hsv to rgb values
        //SetPWMOf3(led, red, green, blue); // write rgb values
		myleds.SetGroupOf3(led, red, green, blue);
      }
      delay(delayVal);
      colorshift = colorshift + shiftStep;
  //  } 
  }
  else {
    colorshift = 0;
  }
}

