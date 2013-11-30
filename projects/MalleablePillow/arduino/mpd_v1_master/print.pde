/* function that prints acceleration data from 
 * the data arrays of Board "b"
 */
void printBoardData(int b)
{
  Serial.print(  "#: "); 
  Serial.print(b);
  Serial.print("\tx: "); 
  Serial.print(dx[b], DEC);
  Serial.print("\ty: "); 
  Serial.print(dy[b], DEC);
  Serial.print("\tz: "); 
  Serial.print(dz[b], DEC);
  Serial.print("\tg: "); 
  Serial.print(dg[b], DEC);
  Serial.print("\tp: "); 
  Serial.print(dp[b], DEC);
  Serial.print("\tr: "); 
  Serial.print(dr[b], DEC);
  Serial.print("\tmagn: "); 
  Serial.print(magn[b], 4);
  Serial.print("\tDelay:  ");
  Serial.print(o_delay[b], DEC);
  Serial.println();
}
//----------------------------------------------------
/* function that prints to serial every 8th loop
 * add here data to be printed.
 */
void printToSerial()
{
  static int div_prnt;
  if (--div_prnt <= 0) {
    div_prnt = 8; // print every 8th loop
    for (int s = 0; s < nB; s++)
      printBoardData(s);
    /*Serial.print("Pitch Mean: "); 
    Serial.print(pAv, 4);
    Serial.print("\tSD: ");       
    Serial.print(pSD, 4);
    Serial.println();
    Serial.print("Roll Mean:  "); 
    Serial.print(rAv, 4);
    Serial.print("\tSD: ");       
    Serial.print(rSD, 4);*/
    Serial.print("Outlier: "); 
    Serial.print(outlier, DEC);
    Serial.print("\tAnger: ");       
    Serial.print(anger);
    Serial.println();
  }  
}

