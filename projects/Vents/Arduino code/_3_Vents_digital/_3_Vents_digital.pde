//Accelerometer
int sensorPinX = 1;
int sensorPinY = 0;

int ventpinRight = 9;
int ventpinLeft = 10;
int ventpinFront = 11;

long sensorValueX = 0;
long sensorValueY = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ventpinRight, OUTPUT);
  pinMode(ventpinLeft, OUTPUT);
  pinMode(ventpinFront, OUTPUT);
}

void loop()
{
  int i = 0;
  //Messure 100 times on x and y pin, and take the average
  for(i; i < 100; i++)
  {
    sensorValueX += analogRead(sensorPinX);
    sensorValueY += analogRead(sensorPinY);
  }
  sensorValueX /= i+1;            //Calc the average
  sensorValueY /= i+1;            //Calc the average
  //Turn the three vents
  TurnVents();
}

//Table with the values from CERTEC end DUMLE
/********************** CERTEC values *************************
NUL:		x = 502,5	y = 508
LEFT:	        x = 498
RIGHT:	        x = 506
FRONT:			y = 503
BACK:			y = 510
****************************************************************/
/********************** DUMLE values ****************************
NUL:		x: 504	y: 509
LEFT	x: 500
RIGHT	x: 508
FRONT			y: 502
BACK			y: 511
*************************************************/

void TurnVents()
{
  //Variables right, left and front used to be analog values, butwe ended up being digital (0/255)
  int right;                            //Indicates how much to turn the right vent
  if(sensorValueX > 505)
  {
    right = 255;
  }
  else
  {
    right = 0;
  }
  analogWrite(ventpinRight, right);    //Turn vent
  
  int left;                            //Indicates how much to turn the left vent
  if(sensorValueX < 502)
  {
    left = 255;
  }
  else
  {
    left = 0;
  }
  analogWrite(ventpinLeft, left);    //Turn vent
  
  int front;                            //Indicates how much to turn the front vent
  if(sensorValueY < 505)
  {
    front = 255;
  }
  else
  {
    front = 0;
  }
  analogWrite(ventpinFront, front);    //Turn vent
}
