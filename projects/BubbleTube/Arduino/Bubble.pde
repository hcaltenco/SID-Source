//BUTTON:
//jord -> 10k -> knap + pin2 -> 5V

#define resolution 8
#define mains 50 // 60: north america, japan; 50: most other places

#define refresh 2 * 1000000 / mains

int capacitiveTurnValue = 9850;   //What value to react on the capacitive sensor

int capacitivePin = 12;
int bubblePin = 3;
int tmpDistance = 0;
int distance = 0;
long previousMillis = 0;
int parseCharNumber = 0;
int serialIn;

//Lights
int pinR = 9;
int pinG = 10;
int pinB = 11;

long previousMillisLight = 0;
int r, g, b = 0;
int fadeSpeed = 4; //Light fading speed Larger = slower fade
int restTime = 2000; //The time to rest bestween fading the lifgt to next colour

//Button
int buttonState = 0;
int buttonPin = 2;

void setup()
{
  Serial.begin(9600);
  pinMode(capacitivePin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(bubblePin, OUTPUT);
  startTimer();
}

int startet = 0;

void loop()
{
  //Get the system state
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  //Get distance from c#
  if(Serial.available() > 0)
  {
    serialIn = Serial.read();
    switch(serialIn)
    {
    case '0':
      {
        tmpDistance *= 10;
        parseCharNumber++;
      }
      break;
    case '1':
      {
        tmpDistance *= 10;
        tmpDistance += 1;
        parseCharNumber++;
      }
      break;
    case '2':
      {
        tmpDistance *= 10;
        tmpDistance += 2;
        parseCharNumber++;
      }
      break;
    case '3':
      {
        tmpDistance *= 10;
        tmpDistance += 3;
        parseCharNumber++;
      }
      break;
    case '4':
      {
        tmpDistance *= 10;
        tmpDistance += 4;
        parseCharNumber++;
      }
      break;
    case '5':
      {
        tmpDistance *= 10;
        tmpDistance += 5;
        parseCharNumber++;
      }
      break;
    case '6':
      {
        tmpDistance *= 10;
        tmpDistance += 6;
        parseCharNumber++;
      }
      break;
    case '7':
      {
        tmpDistance *= 10;
        tmpDistance += 7;
        parseCharNumber++;
      }
      break;
    case '8':
      {
        tmpDistance *= 10;
        tmpDistance += 8;
        parseCharNumber++;
      }
      break;
    case '9':
      {
        tmpDistance *= 10;
        tmpDistance += 9;
        parseCharNumber++;
      }
      break;
    case 10:
      {
        distance = tmpDistance;
        //Serial.println(distance);
        distance -= 1;
        if(distance < 0) distance = 0;
        //distance *= 3;
        Serial.println(distance);
        tmpDistance = 0;
        parseCharNumber = 0;
      }
      break;
    }
  }
  //Check cpapcitive sensor
  int c = time(capacitivePin, B00010000);
  //Serial.println(c);

  //Behavior 1: (increase bubbles, when hand is getting closer, shine lights and change colours when touching tube)
  if(buttonState == LOW)
  {
    if(c > capacitiveTurnValue)
    {
      TurnOnLights();
    }
    else
    {
      analogWrite(9, 0);
      analogWrite(10, 0);
      analogWrite(11, 0);
    }
    if(distance > 0)
    {
      if(millis() - previousMillis < 80)
      {
        digitalWrite(bubblePin, HIGH);
      }
      if(millis() - previousMillis > 80)
      {
        digitalWrite(bubblePin, LOW);
      }
      if(millis() - previousMillis > 80 + distance)
      {
        previousMillis = millis();
      }
    }
    else
    {
      digitalWrite(bubblePin, HIGH);
    }
  }
  //Behavior 2: Change colour when hand is getting closer. When touching make a rythem with bubbles
  else
  {
    if(distance > 0)
    {
      r = distance*2;
      g = 255;
      b = 0;
      if(r>255)r=255;
      analogWrite(pinR, r);
      analogWrite(pinG, g);
      analogWrite(pinB, b);
    }
    else
    {
      TurnOnLights();
    }
    if(c > capacitiveTurnValue)
    {
      if(millis() - previousMillis < 500)
      {
        digitalWrite(bubblePin, HIGH);
      }
      if(millis() - previousMillis > 1000)
      {
        digitalWrite(bubblePin, LOW);
      }
      if(millis() - previousMillis < 1500)
      {
        digitalWrite(bubblePin, HIGH);
      }
      if(millis() - previousMillis > 2000)
      {
        digitalWrite(bubblePin, LOW);
      }
      if(millis() - previousMillis < 2500)
      {
        digitalWrite(bubblePin, HIGH);
      }
      if(millis() - previousMillis > 4500)
      {
        digitalWrite(bubblePin, LOW);
      }
      if(millis() - previousMillis > 6500)
      {
        previousMillis = millis();
      }
    }
    else
    {
      digitalWrite(bubblePin, HIGH);
    }
  }
}

long time(int pin, byte mask)
{
  unsigned long count = 0, total = 0;
  while(checkTimer() < refresh)
  {
    // pinMode is about 6 times slower than assigning
    // DDRB directly, but that pause is important
    pinMode(pin, OUTPUT);
    PORTB = PORTB & B11101111;
    pinMode(pin, INPUT);
    while((PINB & mask) == 0)
      count++;
    total++;
  }
  startTimer();
  return (count << resolution) / total;
}

extern volatile unsigned long timer0_overflow_count;

void startTimer()
{
  timer0_overflow_count = 0;
  TCNT0 = 0;
}

unsigned long checkTimer()
{
  return ((timer0_overflow_count << 8) + TCNT0) << 2;
}

void TurnOnLights()
{
  //Grøn
  if(millis() > previousMillisLight)
  {
    r = 0;
    g = 255;
    b = 0;
  }
  //Grøn -> Blå
  if(millis() > previousMillisLight + restTime)
  {
    r = 0;
    g = 255 - ((millis() - (previousMillisLight + restTime))/fadeSpeed);
    b = (millis() - (previousMillisLight + restTime))/fadeSpeed;
    if(g<0)g=0;
    if(b>255)b=255;
  }
  //Blå
  if(millis() > previousMillisLight + restTime + (255*fadeSpeed))
  {
    r=0;
    g=0;
    b=255;
  }
  //Blå -> Lilla     blå ned, rød op
  if(millis() > previousMillisLight + (restTime*2) + (255*fadeSpeed))
  {
    r = (millis() - (previousMillisLight + (restTime*2) + (255*fadeSpeed)))/fadeSpeed;
    g = 0; 
    b =  255;
    if(b<0)b=0;
  }
  //Lilla
  if(millis() > previousMillisLight + (restTime*2) + (255*fadeSpeed*2))
  {
    r=255;
    g=0;
    b=255;
  }
  //Lilla -> Rød
  if(millis() > previousMillisLight + (restTime*3) + (255*fadeSpeed*2))
  {
    r = 255;
    g = 0;
    b = 255 - ((millis() - (previousMillisLight + (restTime*3) + (255*fadeSpeed*2)))/fadeSpeed);
    if(b<0)b=0;
  }
  //Rød
  if(millis() > previousMillisLight + (restTime*3) + (255*fadeSpeed*3))
  {
    r = 255;
    g = 0;
    b = 0;
  }
  //Rød -> Orange
  if(millis() > previousMillisLight + (restTime*4) + (255*fadeSpeed*3))
  {
    r = 255;
    g = (millis() - (previousMillisLight + (restTime*4) + (255*fadeSpeed*3)))/(fadeSpeed*2);   //128;
    b = 0;
    if(g>128)g=128;
  }
  //Orange
  if(millis() > previousMillisLight + (restTime*4) + (255*fadeSpeed*4))
  {
    r = 255;
    g = 128;
    b = 0;
  }
  //Orange -> Gul
  if(millis() > previousMillisLight + (restTime*5) + (255*fadeSpeed*4))
  {
    r = 255;
    g = 128 + ((millis() - (previousMillisLight + (restTime*5) + (255*fadeSpeed*4)))/(fadeSpeed*2));
    b = 0;
    if(g>255)g=255;
  }
  //Gul
  if(millis() > previousMillisLight + (restTime*5) + (255*fadeSpeed*5))
  {
    r = 255;
    g = 255;
    b = 0;
  }
  //Gul -> Grøn
  if(millis() > previousMillisLight + (restTime*6) + (255*fadeSpeed*5))
  {
    r = 255 - ((millis() - (previousMillisLight + (restTime*6) + (255*fadeSpeed*5)))/(fadeSpeed));
    g = 255;
    b = 0;
    if(r<0)r=0;
  }
  if(millis() > previousMillisLight + 10 + (restTime*6) + (255*fadeSpeed*6))
  {
    previousMillisLight = millis();
    r = 0;
    g = 255;
    b = 0;
  }
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b);
}

