void runReset(){
  Serial.println("Before play, the toy needs to be reset.");
  Serial.println("Use the open/close buttons to open the toy fully,");
  Serial.println("and then press the reset button.");
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  
  while(!reset_bool){
    checkButtons();
    encoder();
    reset_motor();
    reset_data();
    if(digitalRead(resetPin)){
      delay(300);
      reset_bool = true;
      rot_counter = 0;
      myEnc.write(rot_counter);
    }
  }
  Serial.println();
  Serial.println("Reset completed. Continue play.");
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
}

//--------------------------------------------------------------

void reset_motor(){
  if(open_bool){
    motor.run(FORWARD);
  } 
  else if(close_bool){
    motor.run(BACKWARD);
  } 
  else{
    motor.run(RELEASE);
  }
}

//--------------------------------------------------------------

void checkButtons() {
  if(digitalRead(openPin)){
    open_bool = true;
  } 
  else{
    open_bool = false;
  }

  if(digitalRead(closePin)){
    close_bool = true;
    open_bool = false;
  } 
  else{
    close_bool = false;
  }
}

//--------------------------------------------------------------

void reset_data(){  
  //Receive from sensor board
  Wire.requestFrom(3, nSens);
  int i = 0;
  while(Wire.available())    // slave may send less than requested 
  {
    touch_state[i] = Wire.read();
    i++;
  }

  //Send to LED board
  char s[16] = {0};
  sprintf(s, "%d %d %d %s", rot_counter, state, touch_sensor, true);
  Wire.beginTransmission(2);
  Wire.write(s);
  Wire.endTransmission();
}



