/* function that recieves n_bytes of acceleration data or
 * calibration data from the master and stores it in the
 * corresponding data or boolean variables
 */
boolean recieveFromMaster(int n_bytes) {
  byte data[n_bytes];
  int i=0;
  cal_flag = 0;
  
  while (Wire.available()) {
    data[i] = Wire.receive();
    i++;
  }
  if (8 <= sizeof(data)) {
    dx = data[0]; // signed byte acceleration data
    dy = data[1];
    dz = data[2];
    dg = data[3];
    dp = data[4];
    dr = data[5];
	outlier = data[6];
	o_delay = data[7];
  }
  else if (sizeof(data) <= 3 && data[0] == true) {
    cal_flag  = data[0]; // boolean flags
    use_anger = data[1];
    use_tilt  = data[2];
  }
  else { // in case of communication errors
    Serial.println("incomplete data recieved");
  }
  
  return cal_flag;
}
