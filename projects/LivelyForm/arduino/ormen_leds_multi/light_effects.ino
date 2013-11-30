//---------------------------------------------------------------------------------------

void pulse_green() {
  for(int i = 0; i < nLeds/2; i++){
    pwm_values[i*2+1] = 0;
    pwm_values[i*2] = pwm;
  }
  pwm += dir;

  if(pwm >= maxBrightness/2 || pwm <= 10){
    dir *= -1;
  }
  delay(50);
}

//---------------------------------------------------------------------------------------

void pulse_red() {
  for(int i = 0; i < nLeds/2; i++){
    pwm_values[i*2+1] = pwm;
    pwm_values[i*2] = 0;
  }
  pwm += dir;

  if(pwm >= maxBrightness/2 || pwm <= 10){
    dir *= -1;
  }

  delay(50);
}

//--------------------------------------------------------------------------------------

void pulse_gold(){
  for(int i = 0; i < nLeds/2; i++){
    pwm_values[i*2+1] = pwm/3;
    pwm_values[i*2] = pwm;
  }
  pwm += dir;

  if(pwm >= maxBrightness/2 || pwm <= 10){
    dir *= -1;
  }

  delay(50);
}


//--------------------------------------------------------------------------------------

void cycle(){
  for(int i = 0; i < nLeds/2; i++){
    for(int j = 0; j < nLeds; j++){
      pwm_values[j] /= 3;              //Meget grov fade-effekt, kan godt laves bedre.
    }
    pwm_values[i*2+1] = maxBrightness/6;  //Red LEDs
    pwm_values[i*2] = maxBrightness;  //Green LEDs
    delay(130);
  }
}

//--------------------------------------------------------------------------------------

void colors(){
  //Set the colors
  //Section 1:
  if((millis() - touch_start) < cycle_time){
    if (DEBUG)
      Serial.println("Section 1");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = 0;      //Green LEDs
    }
  }
  //Section 2:
  else if((millis() - touch_start) < cycle_time*2){
    if (DEBUG)
      Serial.println("Section 2");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = map(millis()-(touch_start + cycle_time), 0, cycle_time,0,255);
    }
  }
  //Section 3:
  else if((millis() - touch_start) < cycle_time*3){
    if (DEBUG)
      Serial.println("Section 3");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = 255;  //Red LEDs
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 4:
  else if((millis() - touch_start) < cycle_time*4){
    if (DEBUG)
      Serial.println("Section 4");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = map(millis()-(touch_start + cycle_time*3), 0, cycle_time,255,0);
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 5:
  else if((millis() - touch_start) < cycle_time*5){
    if (DEBUG)
      Serial.println("Section 5");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = 0;  //Red LEDs
      led_colors[i*2] = 255;      //Green LEDs
    }
  }
  //Section 6:
  else if((millis() - touch_start) < cycle_time*6){
    if (DEBUG)
      Serial.println("Section 6");
    for(int i = 0; i < nLeds/2; i++){
      led_colors[i*2+1] = map(millis()-(touch_start + cycle_time*5), 0, cycle_time,0,255);
      led_colors[i*2] = map(millis()-(touch_start + cycle_time*5), 0, cycle_time,255,0);
    }
  }
  //Start over:
  else{
    touch_start = millis();
  }

  //Do the Knight Rider trick
  for(int i = 0; i < nLeds/2; i++){

    for(int j = 0; j < nLeds; j++){
      pwm_values[j] /= 1.5;              //Meget grov fade-effekt, kan godt laves bedre.
    }

    pwm_values[i*2+1] = map(led_colors[i*2+1],0,255,0,maxBrightness);
    pwm_values[i*2] = map(led_colors[i*2],0,255,0,maxBrightness);
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

//-------------------------------------------------------------------------------------
//Turns on LEDs according to how open the worm is.

void move(int input){
  input = map(input,1,counter_closed,140,0);
  pwm_values[0] = maxBrightness;
  pwm_values[1] = maxBrightness/3;

  for(int i = 2; i <= nLeds/2; i++){
    pwm_values[i*2-2] = (maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40);
    pwm_values[i*2-1] = ((maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40))/3;
  }
}

//---------------------------------------------------------------------------------------

void reset_leds(){
  if(timed_state == 0){
    leds_off();
  }
  else{
    for(int i = 0; i < nLeds; i++){
      pwm_values[i] = maxBrightness;
    }
  }
}

//---------------------------------------------------------------------------------------

void leds_off(){
  for(int i = 0; i < nLeds; i++){
    pwm_values[i] = 0;
  }
}

