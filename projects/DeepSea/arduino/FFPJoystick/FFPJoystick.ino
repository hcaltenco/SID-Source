#include <FFPJoystick.h>

FFPJoystick sidewinder = FFPJoystick();

void setup() {
  // put your setup code here, to run once:
  sidewinder.EnableAutoCenter();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  sidewinder.Poll();
  sidewinder.forceTest(100);
  Serial.print(sidewinder.X);
  Serial.print("\t");
  Serial.print(sidewinder.Y);
  Serial.print("\t");
  Serial.print(sidewinder.Z);
  Serial.println();
  delay(100);
}
