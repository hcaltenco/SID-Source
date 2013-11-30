/* function that gets acceleration data from this board
 * (master) and stores them in our data arrays
 */
void getAccelData(int b)
{
  accel.update(); // update accelerometer
  x[b] = accel.accel(0);   // X axis acc
  y[b] = accel.accel(1);   // Y axis acc
  z[b] = accel.accel(2);   // Z axis acc
  g[b] = accel.milligee(); // mG force
  p[b] = accel.pitch();    // pitch angle
  r[b] = accel.roll();     // roll angle
}
//----------------------------------------------------
/* function that finds the deviation from mean for
 * each acceleration data variable of board b
 */
void findDeviation(int b){
  dx[b] = x[b] - xAv;
  dy[b] = y[b] - yAv;
  dz[b] = z[b] - zAv;
  dg[b] = g[b] - gAv;
  dp[b] = p[b] - pAv;
  dr[b] = r[b] - rAv;
}
//----------------------------------------------------
/* function that updates the deviation data of board "b".
 * used for updating master data only in showState function.
 */
void updateDevs(int b)
{
  dxM = dx[b];
  dyM = dy[b];
  dzM = dz[b];
  dgM = dg[b];
  dpM = dp[b];
  drM = dr[b];
}
//----------------------------------------------------
/* function that returns the magnitude of acceleration vector
 * (x,y,z) or the magnitude of tilt angle (p, r) using use_tilt
 */
float getMagnitude(int b)
{
  float magn;
  if (use_tilt)
    magn = sqrt(sq(dp[b])+sq(dr[b]));
  else
    magn = sqrt(sq(dx[b])+sq(dy[b])+sq(dz[b]));
    
  return magn;
}
//----------------------------------------------------
/* function that find the dalay order of each board 
 * according to the outlier
 */
void findDelays(int outl) {
	switch (outl){
	case 0:
		o_delay[0] = 0;
		o_delay[1] = 1;
		o_delay[2] = 2;
		o_delay[3] = 1;
		break;
	case 1:
		o_delay[0] = 1;
		o_delay[1] = 0;
		o_delay[2] = 1;
		o_delay[3] = 2;
		break;
	case 2:
		o_delay[0] = 2;
		o_delay[1] = 1;
		o_delay[2] = 0;
		o_delay[3] = 1;
		break;
	case 3:
		o_delay[0] = 1;
		o_delay[1] = 2;
		o_delay[2] = 1;
		o_delay[3] = 0;
		break;
	default:
		for (int i=1; i<nB; i++)
			o_delay[i] = 0;
		break;
	}
}

