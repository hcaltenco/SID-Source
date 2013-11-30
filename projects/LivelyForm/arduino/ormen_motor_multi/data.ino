//--------------------------------------------------------------

void data(){  
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
  sprintf(s, "%d %d %d %d", rot_counter, state, touch_sensor, false);
  Wire.beginTransmission(2);
  Wire.write(s);
  Wire.endTransmission();
}

//--------------------------------------------------------------
