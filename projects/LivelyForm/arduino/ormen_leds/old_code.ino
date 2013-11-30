/*

//--------------------------------------------------------------------------------------------------
//When somebody is near. Opening and lighting up.

void vicinity(){
  v_pwm = map(rot_counter,1,199,maxBrightness,0);
  for(int i = 0; i < 7; i++){
    pwm_values[i*2+1] = pwm;
    pwm_values[i*2] = pwm;
  }

}

//--------------------------------------------------------------------------------------------------

void colors(){
  //Set the colors
  if((millis()-timer1) > cycle_speed){
    state++;
    if(state > 5){
      state = 0;
    }
    timer1 = millis();
  }

  //Serial.print("State: ");
  //Serial.println(state);

  if((millis()-timer2) > cycle_speed/20){
    switch(state){
    case 0:
      red = maxBrightness;
      green = 0;
      break;

    case 1:
      red = maxBrightness;
      green += maxBrightness/20;
      break;

    case 2:
      red = maxBrightness;
      green = maxBrightness;
      break;

    case 3:
      red -= maxBrightness/20;
      green = maxBrightness;
      break;

    case 4:
      red = 0;
      green = maxBrightness;
      break;

    case 5:
      red += maxBrightness/20;
      green -= maxBrightness/20;
      break;
    }

    timer2 = millis();
  }
}

*/

