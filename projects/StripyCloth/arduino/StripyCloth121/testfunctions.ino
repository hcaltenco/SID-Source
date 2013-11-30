void lightWires()
{
  int status;
  
  // Step through all EL channels 
  for (int x=0; x<=nWires; x++)
  {
    byte brightness = constrain (map(caps_array[x], 0, 1024, 0, 255), 0, 255);
    if (brightness > 20)
      analogWrite(ELPIN[x], brightness);   // turn the EL channel on
    else
      digitalWrite(ELPIN[x], LOW);    // turn the EL channel off

    digitalWrite(10, status);   // blink status LEDs
    status = !status;
  }
}

//-------------------------

void lightWire(int wire, byte brightness)
{
  if (wire < nWires) {
    analogWrite(ELPIN[wire], brightness);
  }
}


