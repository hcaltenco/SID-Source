/* function that gets acceleration data from this board
 * (slave) and stores them in our data arrays
 */
void getAccelData()
{
  accel.update(); // update accelerometer 
  x = accel.accel(0); // X axis acc
  y = accel.accel(1); // Y axis acc
  z = accel.accel(2); // Z axis acc
  g = accel.milligee(); // mG force
  p = accel.pitch();  // pitch angle
  r = accel.roll();   // roll angle
}

//----------------------------------------------------
/* function that returns the magnitude of acceleration vector
 * (x,y,z) or the magnitude of tilt angle (p, r) using use_tilt
 */
float getMagnitude()
{
  float magn;
  if (use_tilt)
    magn = sqrt(sq(dp)+sq(dr));
  else
    magn = sqrt(sq(dx)+sq(dy)+sq(dz));
    
  return magn;
}