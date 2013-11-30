//Feel free to use this code.
//Please be respectful by acknowledging the author in the code if you use or modify it.
//Author: Bruce Allen
//Date: 23/07/09

//Analog pin 1 for reading in the analog voltage from the MaxSonar device.
//Digital pin 7 for reading in the pulse width from the MaxSonar device.
//This variable is a constant because the pin will not change throughout execution of this code.
const int anPin = 1;
const int pwPin = 7; 

//variables needed to store values
float anVolt, pulse, mm_a, mm_p;
float sum_a=0;//Create sum variable so it can be averaged
float sum_p=0;
int avgrange=9;//Quantity of values to average (sample size)

void setup() {
  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
  pinMode(anPin, INPUT);
  pinMode(pwPin, INPUT);
}

void loop() {
  //MaxSonar Analog reads are known to be very sensitive. See the Arduino forum for more information.
  //A simple fix is to average out a sample of n readings to get a more consistant reading.\\ 
  //Even with averaging I still find it to be less accurate than the pw method.\\ 
  //This loop gets 60 reads and averages them

  for(int i = 0; i < avgrange ; i++)
  {
    //Used to read in the analog voltage output that is being sent by the MaxSonar device.
    //Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
    //Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
    anVolt = analogRead(anPin)/2;
    //pulse = pulseIn(pwPin, HIGH)/147;//147uS per inch
    sum_a += anVolt;
    //sum_p += pulse;
    delay(1);
  } 
  
  //Used to read in the pulse that is being sent by the MaxSonar device.
  //Pulse Width representation with a scale factor of 147 uS per Inch.
  pulse = pulseIn(pwPin, HIGH)/147;
  
  mm_a = sum_a/avgrange * 25.4;
  //mm_p = sum_p/avgrange * 25.4; 
  mm_p = pulse * 25.4;
  
  Serial.print("analog: ");
  Serial.print(int(mm_a));
  Serial.print("\t pw: ");
  Serial.print(int(mm_p));
  Serial.println("\t mm.");
  //reset sample total
  sum_a = 0;
  sum_p = 0;
  delay(20);
}
