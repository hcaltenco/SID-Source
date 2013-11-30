void TestLed(int led) {
  int spd = 5;
  int pause = 100;
    for (int i = 0; i <= 255; i++) {
      analogWrite(rl[led], i); // set the LED on
      delay(spd); 
    }
    delay (pause);
    for (int i = 255; i >= 0; i--) {
      analogWrite(rl[led], i);    // set the LED off
      delay(spd);
    }
    delay (pause);
    for (int i = 0; i <= 255; i++) {
      analogWrite(bl[led], i); // set the LED on
      delay(spd); 
    }
    delay (pause);
    for (int i = 255; i >= 0; i--) {
      analogWrite(bl[led], i);    // set the LED off
      delay(spd);
    }
    delay (pause);
}
