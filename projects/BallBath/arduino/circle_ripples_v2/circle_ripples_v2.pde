import oscP5.*;
import netP5.*;

float px,py = 0;
OscP5 oscP5;
NetAddress myRemoteLocation;
boolean visible = false;

CircleRipples circle1 = new CircleRipples();
CircleRipples circle2 = new CircleRipples();

int x1, y1;
boolean visible1;
int x2, y2;
boolean visible2;

void setup()
{
  circle1.circleBorderSize = 120;
  circle1.circleColor = color(255, 0, 0, 128);

  circle2.circleBorderSize = 80;
  circle2.circleColor = color(0, 0, 255, 100);

  size(1280,1024);
  noFill();
  ellipseMode(CENTER);
  frameRate(30);

  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,12345);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1",12000);
}


void draw()
{  
  background(0);
  circle1.Draw(x1, y1, visible1);
  circle2.Draw(x2, y2, visible2);
}


class CircleRipples
{
  public int circleBorderSize;
  public color circleColor;
  public int rippleSpeed = 5;

  private int maxNumberOfCircles = 20;
  private Circle [] circles = new Circle[maxNumberOfCircles];
  private int circleCount = 0;

  public CircleRipples()
  {
    for(int i = 0; i < maxNumberOfCircles; i++)
    {
      circles[i] = new Circle();
      circles[i].circleSize = -1;
    }
    circleCount = 0;
    circles[circleCount].circleSize = 0;
  }

  public void Draw(int x, int y, boolean visible)
  {
    strokeWeight(circleBorderSize);
    stroke(circleColor);
    Grow(x, y, visible);
    for(int i = 0; i < maxNumberOfCircles; i++)
    {
      if(circles[i].circleSize != -1)
      {
        ellipse(circles[i].x, circles[i].y, circles[i].circleSize, circles[i].circleSize);
      }
    }
  }
  
  private void Grow(int x, int y, boolean visible)
  {
    //create a new circle
    if(circles[circleCount].circleSize > 500 && visible)
    {
      circleCount++;
      if(circleCount >= maxNumberOfCircles)
      {
        circleCount = 0;
      }
      circles[circleCount].circleSize = 0;
      circles[circleCount].x = width-x;
      circles[circleCount].y = y;
    }
    //Grow the circles allready drawn
    for(int i = 0; i < maxNumberOfCircles; i++)
    {
      if(circles[i].circleSize > -1)
      {
        circles[i].circleSize += rippleSpeed;
      }
    }
  }

  class Circle
  {
    int x;
    int y;
    int circleSize;
  }
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage)
{
  //Webcam resolution is 400 x 300
  if(theOscMessage.get(1).intValue() == 1 && theOscMessage.get(0).intValue() ==1)
  {
    x1 = (int)theOscMessage.get(2).floatValue();
    x1 = (x1*width)/400;
    //x1 = width - x1;
    y1 = (int)theOscMessage.get(3).floatValue();
    y1 = (y1*height)/300;
    print(x1);
    print("  ");
    println(y1);
    visible1 = 1==theOscMessage.get(4).intValue();
  }
  else if(theOscMessage.get(1).intValue() == 1 && theOscMessage.get(0).intValue() ==2)
  {
    x2 = (int)theOscMessage.get(2).floatValue();
    x2 = (x2*width)/400;
    //x2 = width - x2;
    y2 = (int)theOscMessage.get(3).floatValue();
    y2 = (y2*height)/300;
    print(x2);
    print("  ");
    println(y2);
    visible2 = 1==theOscMessage.get(4).intValue();
  }
}

