void updateState()
{
  // IF ACCELERATION SWING OR WAVE
  if (active_accel > ACCEL_THRES) {
    if (active_accel > ACCEL_HIGH) {
      start_shake = millis();
    }
    unsigned long time_accel = millis() - start_shake;
    if (time_accel < TIME_THRES) {
      current_state_a = WAVE;
    }
    else {
      current_state_a = SWING;
    }
  }
  else if (millis() - start_shake > TIME_THRES){
    current_state_a = IDLE;
  }
  
  // IF PRESSING OR KNEEDING
  if (active_press) {
    if (active_press != last_press) {
      start_press = millis();
    }
    unsigned long time_press = millis() - start_press;
    if (time_press < TIME_THRES) {
      current_state_p = KNEED;
    }
    else {
      current_state_p = PRESS;
    }
  }
  else if (millis() - start_press > TIME_THRES){
    current_state_p = IDLE;
  }  
}

//-------------------------

void idle()
{
  // Light the wires in a snoring mode
  // Purple and Green wires oscillating in low brightness
  static byte d_bright[] = {BRIGHT_STEP, -BRIGHT_STEP, 0};

  if (current_state_a != last_state_a || current_state_p != last_state_p) {
    brightness[0] = 0;
    brightness[1] = BRIGHT_LOW;
    brightness[2] = 0;
  }
  
  for (int i=0; i<nWires-1; i++) {
    if (brightness[i] >= BRIGHT_LOW)
      d_bright[i] = -BRIGHT_STEP;
    else if (brightness[i] <= 0)
      d_bright[i] = BRIGHT_STEP;
    
    brightness[i] += d_bright[i];
    
  }
 for (int i=0; i<nWires; i++) {
   thres_achieved[i] = false;
   analogWrite(ELPIN[i], brightness[i]);
 }
 //noTone(SPEAKPIN);
 //digitalWrite(STATPIN, LOW);
 delay(250);
}

//-------------------------



void press() 
{
  // Light wires gradually to a high brighness
  // if continue touching gradually decrease brightness
  // wire color dependis on the area pressed
  static float d_bright[nWires];
  
  int press_arr3[nWires];
  press_arr3[0] = max(press_array[0], press_array[3]);
  press_arr3[1] = max(press_array[1], press_array[4]);
  press_arr3[2] = press_array[2];
  
  
  for (int i=0; i <nWires; i++) {
    if(current_state_p != last_state_p)
      brightness[i] = 0;
    
    if (press_arr3[i] > PRESS_THRES) {  
      if (brightness[i] < BRIGHT_HIGH && !thres_achieved[i]) {
        d_bright[i] = (BRIGHT_STEP * press_arr3[i]) / 1000;
      }
      else if (brightness[i] >= BRIGHT_HIGH) {
        thres_achieved[i] = true;
        d_bright[i] = -(BRIGHT_STEP * press_arr3[i]) / 1000;
      }
      if (brightness[i] <= 0 && thres_achieved[i]) {
        //thres_achieved[i] = false;
        brightness[i] = 0;
        d_bright[i] = 0;
      }
    }
    else {
      //thres_achieved[i] = false;
      brightness[i] = 0;
      d_bright[i] = 0;
    }
    
    
    brightness[i] += d_bright[i];
    
    brightness[i] = constrain(brightness[i], 0, BRIGHT_MAX);
    
    analogWrite(ELPIN[i], brightness[i]);
  }  
  
}

//-------------------------

void kneed()
{
  // Light Wires gradually to a max brighness
  // Blink wires gradually to a max brighness
  // Wire color depends on the area pressed
  static float d_bright[nWires];
  static float d_blink[nWires] = {BLINK_MAX};
  static unsigned long start_blink[nWires] = {0};
  static unsigned long blinkdelay[nWires] = {0};
  static boolean wire_state = false;
  
  int press_arr3[nWires];
  press_arr3[0] = max(press_array[0], press_array[3]);
  press_arr3[1] = max(press_array[1], press_array[4]);
  press_arr3[2] = press_array[2];
  
  
  for (int i=0; i <nWires; i++) {
    if(current_state_p != last_state_p)
      brightness[i] = 0;
    
    //if (press_arr3[i] > PRESS_THRES) {  
      if (brightness[i] < BRIGHT_MAX)
        d_bright[i] = 2*BRIGHT_STEP * press_arr3[i] / 1000;
      else
        d_bright[i] = 0;
      
      //d_blink[i] = 50;
      
    /*}
    else {
      //thres_achieved[i] = false;
      //brightness[i] = 0;
      d_bright[i] = 0;
      d_blink[i] = 0;
    }*/
    
    brightness[i] += d_bright[i];
    blinkdelay[i] = 300;//d_blink[i];
    
    brightness[i] = constrain(brightness[i], 0, BRIGHT_MAX);
    
    if (millis() - start_blink[i] >= blinkdelay[i]) {
      start_blink[i] = millis();
      wire_state = !wire_state;
    }
    
    if (wire_state) {
      analogWrite(ELPIN[i], brightness[i]);
      digitalWrite(STATPIN, HIGH);
    }
    else {
      digitalWrite(ELPIN[i], LOW);
      digitalWrite(STATPIN, LOW);
    }
  }  
}

//-------------------------

void swing()
{
  // Blink wires gradually to a max brighness
  // if continue touching stop blinking
  // blink wire depending on the area pressed
  s_pitch = map(active_accel, 0, 2000, 120, 1500);
  if (active_accel > ACCEL_THRES)
    tone(SPEAKPIN, s_pitch,100);
  delay(1);
}

//-------------------------

void wave()
{
  s_pitch = map(active_accel, 0, 20000, 120, 1500);
  if (active_accel > ACCEL_THRES)
    tone(SPEAKPIN, s_pitch,100);
  delay(1);
}
