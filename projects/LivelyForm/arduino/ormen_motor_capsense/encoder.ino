//--------------------------------------------------------------

void encoder() {
  long tmpdata = myEnc.read();
  if (tmpdata != rot_counter) {
    //last_counter = rot_counter;
    rot_counter = tmpdata;
    if (DEBUG) {
      Serial.print("rot_counter: ");
      Serial.println(rot_counter, DEC);
    }
  }
}


//--------------------------------------------------------------

