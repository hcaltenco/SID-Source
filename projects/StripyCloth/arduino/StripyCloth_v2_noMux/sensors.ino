void setControlPins(int i)
{
  //The following 4 commands set the correct logic for the control pins to select the desired input
  //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
  //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
  //digitalWrite(CONTROL0, (i&15)>>3); 
  //digitalWrite(CONTROL1, (i&7)>>2);  
  digitalWrite(CONTROL1, (i&3)>>1);  
  digitalWrite(CONTROL0, (i&1));  
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
  for (int i=0; i<nPreSens-1; i++)
  {
    //Read and store the input value at a location in the array
    setControlPins(i);
    press_array[i] = analogRead(PRESSPIN);
  }
  press_array[nPreSens-1] = analogRead(A2);
  
  //scroll through the Accelerometer multiplexer
  for (int i=0; i<nAccSens; i++)
  {
    setControlPins(i);     
    accel_array[i] = analogRead(ACCELPIN)-accel_base[i];
  }
  
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
  Serial.print("activ: \t");
  Serial.print(active_press);
  Serial.print("\t");  
  
  Serial.print("state: \t");
  Serial.println(current_state_p);
  
  
  //printing out results of accel data
  Serial.print("Acceleration: \t");
  for (int i=0; i<nAccSens; i++)
  {
    Serial.print(accel_array[i]);
    Serial.print("\t");
  }
  Serial.print("mg:\t");
  Serial.print(active_accel);
  Serial.print("\t");  
  
  Serial.print("state: \t");
  Serial.println(current_state_a);
}

//--------------------------

void printWires()
{
  Serial.print("Wire brighness: \t");
  for (int i=0; i<nWires; i++)
  {
    Serial.print(brightness[i]);
    Serial.print("\t");
  }
  Serial.println();
}

//--------------------------

void printSound()
{
  Serial.print("Pitch: \t");
  Serial.println(s_pitch);
}
