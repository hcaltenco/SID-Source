//Mux_Shield_AnalogIn_Example
//http://mayhewlabs.com/arduino-mux-shield

/*
This example shows how to read and store all 48 pins as analog inputs into arrays and print the results over serial.
Multiplexer pin inputs that do not have a voltage reading (i.e nothing connected) will have erratic values.

To simplify this code further, one might use nested for loops or function calls.
*/

//Give convenient names to the control pins
#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

//Define the input pins
#define PRESSPIN  0
#define ACCELPIN  1

//Define the number of pins for each input type
#define nPreSens 5
#define nAccSens 3

//Create arrays for data from the the MUXs
//See the Arduino Array Reference: http://www.arduino.cc/en/Reference/Array
int press_array[nPreSens];
int accel_array[nAccSens];
//int mux2array[16];

//Accelerometer baseline
int acc_base[nAccSens] = {512};

void setup()
{
  //Set MUX control pins to output
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  
  //Calibrate the accelerometer
  for (int i=0; i<nAccSens; i++)
  {
    setControlPins(i);     
    acc_base[i] = analogRead(ACCELPIN);
  }
  
  //Open the serial port at 28800 bps
  Serial.begin(28800);
}

void setControlPins(int i)
{
  //The following 4 commands set the correct logic for the control pins to select the desired input
  //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
  //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
  digitalWrite(CONTROL0, (i&15)>>3); 
  digitalWrite(CONTROL1, (i&7)>>2);  
  digitalWrite(CONTROL2, (i&3)>>1);  
  digitalWrite(CONTROL3, (i&1));  
}

void loop()
{
  //This for loop is used to scroll through and store the Pressure sensor inputs
  for (int i=0; i<nPreSens; i++)
  {
    //Read and store the input value at a location in the array
    setControlPins(i);
    press_array[i] = analogRead(PRESSPIN);
  }
  
  //This for loop is used to scroll through the Accelerometer multiplexer
  for (int i=0; i<nAccSens; i++)
  {
    setControlPins(i);     
    accel_array[i] = analogRead(ACCELPIN)-acc_base[i];
  }
  
  //The following lines are for printing out results of array0
  Serial.print("Pressure: \t");
  for (int i=0; i<nPreSens; i++)
  {
    Serial.print(press_array[i]);
    Serial.print("\t");
  }
  Serial.println();  //line feed
  
  //The following lines are for printing out results of array1
  Serial.print("Acceleration: \t");
  for (int i=0; i<nAccSens; i++)
  {
    Serial.print(accel_array[i]);
    Serial.print("\t");
  }
    Serial.print(milligee());
  Serial.println();
  
  // delay between readings
  delay (1000);
}

int milligee()
{
  int scale = 100;
  long squared = 0.0;
  for (int i = 0; i < nAccSens; i++)
    squared += (long)accel_array[i] * (long)accel_array[i];
  int g = squared * 1000 / (scale*scale);
  return g;
}
