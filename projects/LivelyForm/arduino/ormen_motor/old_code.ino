/*

void checkButtons() {
  if(!press_bool && (digitalRead(openPin) || digitalRead(closePin))){
    press_bool = true;

    if(digitalRead(openPin)){
      open_bool = !open_bool;
      close_bool = false;
    }

    if(digitalRead(closePin)){
      close_bool = !close_bool;
      open_bool = false;
    }
  }

  if(!digitalRead(openPin) && !digitalRead(closePin)){
    press_bool = false;
  }
}

//--------------------------------------------------------------

void run_motor(int dir){

  if(dir == 1){
    if(rot_counter >= 0){
      motor.run(FORWARD);
    } 
    else{
      motor.run(RELEASE);
    }
  }

  if(dir == -1){
    if(rot_counter <= 200){
      motor.run(BACKWARD);
    }
    else{
      motor.run(RELEASE);
    }
  }
  else if(dir == 0){
    motor.run(RELEASE);
  }
}

//--------------------------------------------------------------

void encoder(){
  int8_t tmpdata; 

  tmpdata = read_encoder(); 
  if( tmpdata ) 
  { 
    if (DEBUG) {
      Serial.print("rot_counter: ");
      Serial.println(rot_counter, DEC);
    }
    last_counter = rot_counter;
    rot_counter += tmpdata;
    
  } 
  
}

//--------------------------------------------------------------

int8_t read_encoder() 
{ 
  static int8_t enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; 
  static uint8_t old_AB = 0; 
  
  old_AB <<= 2;                   //remember previous state 
  old_AB |= ( ENC_PORT & 0x03 );  //add current state 
  return ( enc_states[( old_AB & 0x0f )]); 
}

*/

