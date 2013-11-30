void setControlPins(int i)
{
  //The following 4 commands set the correct logic for the control pins to select the desired input
  //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
  //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
  //digitalWrite(CONTROL0, (i&15)>>3); 
  digitalWrite(CONTROL1, (i&7)>>2);  
  digitalWrite(CONTROL2, (i&3)>>1);  
  digitalWrite(CONTROL3, (i&1));  
}


//--------------------------------------------------------------------------------------

int findActive(int* array, int arraySize, int THRES)
{
  int active = 0;
  int maxval = 0;
  for (int i=0; i < arraySize; i++ )
  {
    if (array[i] > maxval) {
      maxval = array[i];
      if(array[i] > THRES) {
        active = i + 1;
      }
    }
  }
  return active;
}


//-------------------------

long readSensors()
{
  // start data aquisition timer
  long tic = millis();

  //scroll through and store the Pressure sensor inputs
  for (int i=0; i<nPreSens; i++)
  {
    //Read and store the input value at a location in the array
    setControlPins(i);
    press_array[i] = analogRead(PRESSPIN);
  }
  
  //scroll through the Accelerometer multiplexer
  for (int i=0; i<nAccSens; i++)
  {
    setControlPins(i);     
    accel_array[i] = analogRead(ACCELPIN)-accel_base[i];
  }
  
  //scroll through the capsense sensors
//  for (int i=0; i<nCapSens; i++)
//  {
//    // read the value
//    long caps_val = cs[i].capSense(nSamples);
//    
//    // find the maximum
//    if (caps_val > caps_max[i])
//      caps_max[i] = caps_val;
//    
//    // save normalized value into array
//    caps_array[i] = constrain(map(caps_val - caps_base[i], 0, caps_max[i], 0, 1023), 0, 1023);
//    //caps_array[i] = caps_val;
//  }
  
  // return elapsed data aquisition time
  return millis() - tic;
}



//-------------------------

int milligee()
{
  int scale = 100;
  long squared = 0.0;
  for (int i = 0; i < nAccSens; i++)
    squared += (long)accel_array[i] * (long)accel_array[i];
  int g = squared * 1000 / (scale*scale);
  return g;
}

//-------------------------

void printReadings()
{
  //printing out results of pressure data
  Serial.print("Pressure: \t");
  for (int i=0; i<nPreSens; i++)
  {
    Serial.print(press_array[i]);
    Serial.print("\t");
  }
  Serial.print("active: \t");
  Serial.println(active_press);
  
  //printing out results of accel data
  Serial.print("Acceleration: \t");
  for (int i=0; i<nAccSens; i++)
  {
    Serial.print(accel_array[i]);
    Serial.print("\t");
  }
  Serial.print("mg:\t");
  Serial.println(active_accel);
  
  //printing out results of capsense data
  /*Serial.print("Capsense: \t");
  for (int i=0; i<nCapSens; i++)
  {
    Serial.print(caps_array[i]);
    Serial.print("\t");
  }
  Serial.print("active: \t");
  Serial.println(active_caps);  //line feed*/
}

//--------------------------

void printWires()
{
  for (int i=0; i<nWires; i++)
  {
    Serial.print(brightness[i]);
    Serial.print("\t");
  }
  Serial.println(current_state);
}
