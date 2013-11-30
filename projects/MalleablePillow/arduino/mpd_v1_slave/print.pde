/* function that prints to serial every 8th loop
 * add here data to be printed.
 */
void printToSerial()
{
  static int div_prnt;
  if (--div_prnt <= 0) {
    div_prnt = 8; // print every 8th loop
    if (cal_flag){
      Serial.println("Device calibrated:");
      Serial.print("cal_flag: ");  Serial.println(cal_flag,4);
      Serial.print("use_anger: "); Serial.println(use_anger,4);
      Serial.print("use_tilt: ");  Serial.println(use_tilt,4);
    }
    else {
      Serial.print("x: ");   Serial.print(dx, DEC);
      Serial.print("\ty: "); Serial.print(dy, DEC);
      Serial.print("\tz: "); Serial.print(dz, DEC);
      Serial.print("\tg: "); Serial.print(dg, DEC);
      Serial.print("\tp: "); Serial.print(dp, DEC);
      Serial.print("\tr: "); Serial.print(dr, DEC);
      if (use_tilt){
        Serial.print("\tTilt:  "); Serial.print(last_magn,4);
      }
      else {
        Serial.print("\tMagn:  "); Serial.print(last_magn,4);
      }
      if (use_anger)
        Serial.print("\tAnger:  "); Serial.print(anger);
	  Serial.print("\tDelay:  "); Serial.print(o_delay);
      Serial.println();
    }
  }
}
