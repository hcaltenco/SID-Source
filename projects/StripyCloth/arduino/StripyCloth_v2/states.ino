void updateState()
{
  // IF ACCELERATION SWING OR WAVE
  if (active_accel > ACCEL_THRES) {
    if (active_press || active_caps) {
      current_state = WAVE;
    }
    else {
      current_state = SWING;
    }
  }
  // OTHERWISE IF PRESSING OR KNEEDING
  else if (active_press) {
    if (active_press != last_press) {
      start_press = millis();
    }
    unsigned long time_press = millis() - start_press;
    if (time_press < TIME_THRES) {
      current_state = KNEED;
    }
    else {
      current_state = PRESS;
    }
  }
  // OTHERWISE IF ONLY TOUCHING OR CARESSING
  else if (active_caps) {
    if (active_caps != last_caps) {
      start_touch = millis();
    }
    unsigned long time_caps = millis() - start_touch;
    if (time_caps < TIME_THRES) {
      current_state = CARESS;
    }
    else {
      current_state = TOUCH;
    }
  }
  // NO INPUTS
  else {
    current_state = IDLE;
  }  
}

//-------------------------

void idle()
{
  // Light the wires in a snoring mode
  // Purple and Green wires oscillating in low brightness
  //static byte brightness[] = {0, BRIGHT_LOW, 0};
  static byte d_bright[] = {BRIGHT_STEP, -BRIGHT_STEP, 0};

  if (current_state != last_state) {
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
}

//-------------------------

/*void touch()
{
  // Light Wires gradually to a max brightness
  // if continue touching stop lighting
  // Wire color depends on the caps sensor touched
  //static byte brightness[nWires] = {0};
  static byte d_bright[nWires];
  //static boolean thres_achieved[nWires] = {false};
  
  for (int i=0; i <nWires; i++) {
    if(current_state != last_state)
      brightness[i] = 0;
      
    //if (brightness[i] > BRIGHT_HIGH)
    //  d_bright[i] = -BRIGHT_STEP;
    if (brightness[i] < BRIGHT_HIGH && !thres_achieved[i])
      d_bright[i] = BRIGHT_STEP * caps_array[i] / 1023;
    else if (brightness[i] >= BRIGHT_HIGH) {
      thres_achieved[i] = true;
      d_bright[i] = -(BRIGHT_STEP * caps_array[i] / 1023);
    }
    if (brightness[i] <= 0 && thres_achieved[i]) {
      //thres_achieved = false;
      brightness[i] = 0;
      d_bright[i] = 0;
    }
    
    brightness[i] += d_bright[i];
    
    analogWrite(ELPIN[i], brightness[i]);
  }  
}
*/
//-------------------------

/*void caress()
{
  // Light Wires gradually to a max brighness
  // Wire color depends on the caps sensor touched
  //static byte brightness[nWires] = {0};
  static byte d_bright[nWires];
  
  for (int i=0; i <nWires; i++) {
    if(current_state != last_state)
      brightness[i] = 0;
    
    //if (brightness[i] > BRIGHT_HIGH)
    //  d_bright[i] = -BRIGHT_STEP;
    if (brightness[i] < BRIGHT_HIGH)
      d_bright[i] = BRIGHT_STEP * caps_array[i] / 1023;
    else
      d_bright[i] = 0;
    
    brightness[i] += d_bright[i];
    
    analogWrite(ELPIN[i], brightness[i]);
  }  
}
*/
//-------------------------

void press() 
{
  // Blink wires gradually to a max brighness
  // if continue touching stop blinking
  // blink wire depending on the area pressed
  //static byte brightness[nWires] = {0};
  //static byte blinkdelay[nWires] = {0};
  static float d_bright[nWires];
  //static float d_blink[nWires] = {BLINK_MAX};
  //static boolean thres_achieved[nWires] = {false};
  //static unsigned long start_blink[nWires] = {0};
  //static boolean wire_state = false;
  
  int press_arr3[nWires];
  press_arr3[0] = max(press_array[0], press_array[3]);
  press_arr3[1] = max(press_array[1], press_array[4]);
  press_arr3[2] = press_array[2];
  
  
  for (int i=0; i <nWires; i++) {
    if(current_state != last_state)
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
    
    /*if (blinkdelay[i] > BLINK_THRES && !thres_achieved[i])
      d_blink[i] = -map(press_arr3[i], 0, 255, 10, 100);
    else if (blinkdelay[i] <= BLINK_THRES) {
      thres_achieved[i] = true;
      d_blink[i] = map(press_arr3[i], 0, 255, 10, 100);
    }
    if (blinkdelay[i] >= BLINK_MAX && thres_achieved[i]) {
      //thres_achieved = false;
      blinkdelay[i] = BLINK_MAX;
      d_blink[i] = 0;
    }
    
    blinkdelay[i] += d_blink[i];
    
    if (millis() - start_blink[i] >= blinkdelay[i]) {
      start_blink[i] = millis();
      wire_state = !wire_state;
    }
    
    if (wire_state)
      analogWrite(ELPIN[i], brightness[i]);
    else
      digitalWrite(ELPIN[i], LOW);*/
      
    analogWrite(ELPIN[i], brightness[i]);
  }  
  
}

//-------------------------

void kneed()
{
  // Blink wires gradually to a max blink speed
  // blink wire depending on the area pressed
  //static byte brightness[nWires] = {0};
  static byte blinkdelay[nWires] = {0};
  static float d_bright[nWires];
  static float d_blink[nWires] = {BLINK_MAX};
  static unsigned long start_blink[nWires] = {0};
  static boolean wire_state = false;
  
  byte press_arr3[nWires];
  press_arr3[0] = max(press_array[0], press_array[3]);
  press_arr3[1] = max(press_array[1], press_array[4]);
  press_arr3[2] = press_array[2];
  
  
  for (int i=0; i <nWires; i++) {
    if(current_state != last_state)
      brightness[i] = 0;
    
    if (brightness[i] < BRIGHT_MAX)
      d_bright[i] = 2*BRIGHT_STEP * press_arr3[i] / 100;
    else
      d_bright[i] = 0;
    
    brightness[i] += d_bright[i];
    
    if (blinkdelay[i] > BLINK_MIN)
      d_blink[i] = -map(press_arr3[i], 0, 255, 10, 100);
    else {
      d_blink[i] = 0;
    }
    
    blinkdelay[i] += d_blink[i];
    
    if (millis() - start_blink[i] >= blinkdelay[i]) {
      start_blink[i] = millis();
      wire_state = !wire_state;
    }
    
    if (wire_state)
      analogWrite(ELPIN[i], brightness[i]);
    else
      digitalWrite(ELPIN[i], LOW);
  }  
}

//-------------------------

void swing()
{
  static int pitch;
  
  pitch = map(active_accel, 0, 20000, 120, 1500);
  
  tone(SPEAKPIN, pitch, 1000/4);
}

//-------------------------

/*void wave()
{
  static int pitch;
  
  pitch = map(active_accel, 0, 20000, 800, 1500);
  
  tone(SPEAKPIN, pitch, 1000/4);
}*/
