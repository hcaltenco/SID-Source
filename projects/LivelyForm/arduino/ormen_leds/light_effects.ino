/*
Light effects:

//--------------------------------------------------------------------------------------------------

void pulse(){
  for(int i = 0; i < 14; i++){
    pwm_values[i] = pwm;
  }
  pwm += dir;
  delay(30);

  if(pwm > maxBrightness){
    dir *= -1;
  }

  if(pwm < 0){
    dir *= -1;
  }
}

//--------------------------------------------------------------------------------------------------

void pulse_gold(){
  for(int i = 0; i < 7; i++){
    pwm_values[i*2] = pwm;
    pwm_values[i*2-1] = (pwm/3);
  }
  pwm += dir;
  delay(30);

  if(pwm > maxBrightness){
    dir *= -1;
  }

  if(pwm < 0){
    dir *= -1;
  }
}

//--------------------------------------------------------------------------------------------------

void pulse_green(){
  for(int i = 0; i < 7; i++){
    pwm_values[i*2] = pwm;
  }
  pwm += dir;
  delay(30);

  if(pwm > maxBrightness){
    dir *= -1;
  }

  if(pwm < 0){
    dir *= -1;
  }
}

//--------------------------------------------------------------------------------------------------

void pulse_red(){
  for(int i = 0; i < 7; i++){
    pwm_values[i*2-1] = pwm;
  }
  pwm += dir;
  delay(30);

  if(pwm > maxBrightness){
    dir *= -1;
  }

  if(pwm < 0){
    dir *= -1;
  }
}

//--------------------------------------------------------------------------------------------------

void move(int input){
  input = map(input,1,199,140,0);
  pwm_values[0] = maxBrightness;
  pwm_values[1] = maxBrightness;

  for(int i = 2; i <= 7; i++){
    pwm_values[i*2-2] = (maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40);
    pwm_values[i*2-1] = (maxBrightness/40)*constrain((input-(120/6)*(i-2)),0,40);
  }
}

//--------------------------------------------------------------------------------------------------

void cycle(){
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 14; j++){
      pwm_values[j] /= 3;              //Meget grov fade-effekt, kan godt laves bedre.
    }
    pwm_values[i*2+1] = maxBrightness/4;  //Red LEDs
    pwm_values[i*2] = maxBrightness;  //Green LEDs
    delay(130);
  }
}
*/
