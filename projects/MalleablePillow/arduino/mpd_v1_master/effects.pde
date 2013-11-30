//----------------------------------------------------
/* function that shows the state of the board (b) using the pummer
 * class to increase and decrease the intensity of each RGB light
 */
void showState()
{
  static boolean grow;
  byte lr, lg, lb;
  int sp;
  if (use_anger) {
    anger -= 3;  // decrease over time
    anger = constrain(anger, 0, 255);
    if (grow) {
      lr = anger; 
      lg = 64; 
      lb = 64-anger/4; 
      sp = 260-anger;
    }
    else {
      lr = anger/2; 
      lg = anger/4; 
      lb = 128-anger/2; 
      sp = 1790-anger*7;
    }
  }
  else {
	if (use_tilt){
		dpM = towardsZero(dpM,1); // towards zero over time
		drM = towardsZero(drM,1);
		lr = constrain(abs(dpM)*2.5, 0, 255);
		lg = constrain(abs(drM)*2.5, 0, 255);
		lb = 0;
		sp = 25;
	}
	else {
		dxM = towardsZero(dxM,1);
		dyM = towardsZero(dyM,1);
		dzM = towardsZero(dzM,1);
		lr = constrain(abs(dxM)*2.5, 0, 255);
		lg = constrain(abs(dyM)*2.5, 0, 255);
		lb = constrain(abs(dzM)*2.5, 0, 255);
		sp = 25;
	}
  }
//  pummer.loop();
//  if (pummer.done()) {
//    grow = !grow;
//    pummer.goal(lr, lg, lb, 25);
//  }
  if (anger)
    rgbLedRainbow(3, (300-anger), 20, ledBrightness, 6);
  else
	  snore(8);
  
}

int towardsZero(int value, int steps) {
  int r;
  if (value < 0)
    r = value + steps;
  else if (value > 0)
    r = value - steps;
  else
    r = value;
  return r;
}

//-----------------------------------------------------

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
	  //cal_flag = true;
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
  //Start over:
  else{
    timer_start = millis();
  }

  //Do the Knight Rider trick
  int n_steps = 3;
  for(int i = 0; i < n_rgbs; i++){
    // fade in
    for(int j = 1; j < n_steps; j++){
      myleds.SetGroupOf3(i, j*pwm_r/n_steps, j*pwm_g/n_steps, j*pwm_b/n_steps);
    }
    // fade out
    for(int j = n_steps; j > 0; j--){
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
    for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
      hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
      sat = 255;
      val = 255;
      hsv2rgb(hue, sat, val, &red, &green, &blue, maxBrightness); // convert hsv to rgb values
      myleds.SetGroupOf3(led, red, green, blue); // write rgb values
    }
    delay(delayVal);
    colorshift = colorshift + shiftStep;
  }
  else {
    colorshift = 0;
  }
}

