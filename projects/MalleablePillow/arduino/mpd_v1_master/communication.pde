/* function recieves n_bytes of acceleration data from
 * slave "s" and stores them in our data arrays
 */
void recieveFromSlave(int s, int n_bytes)
{
  char data[n_bytes];
  int i=0;
  
  Wire.requestFrom(s, n_bytes); // request n_bytes from slave device s
  while (Wire.available()) {
    data[i] = Wire.receive();
    i++;
  }
  
  if (6 <= sizeof(data))  // if n_bytes were received
  { 
    x[s] = data[0];   // recieve acceleration bytes 
    y[s] = data[1];
    z[s] = data[2];
    g[s] = data[3];   // recieve mG force byte 
    p[s] = data[4];   // receive pitch byte 
    r[s] = data[5];   // receive roll byte 
  }
  else {
    Serial.println("incomplete data recieved");
  }
}
//----------------------------------------------------
/* function transmit byte array "data" to
 * slave "s"
 */
void sendToSlave(int s, byte* data, int n_bytes)
{
  Wire.beginTransmission(s); // transmit to slave s
  Wire.send(data, n_bytes);  // send data
  Wire.endTransmission();    // stop transmitting
}

