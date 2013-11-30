/**
 * oscP5message by andreas schlegel
 * example shows how to create osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */
 
import oscP5.*;
import netP5.*;
 
float xmag, ymag = 0;
float newXmag, newYmag = 0; 
float radius = 0;

float px,py = 0;
float colorMod = 0;
OscP5 oscP5;
NetAddress myRemoteLocation;
boolean visible = false;

void setup() {
  size(1240, 960, P3D); 
  noStroke(); 
  colorMode(RGB, 1); 

  frameRate(25);
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


void draw() {
  
  background(0);
  if (visible)
cube(px,py) ;
}

void mousePressed() {
  /* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/test");
  
  myMessage.add(123); /* add an int to the osc message */
  myMessage.add(12.34); /* add a float to the osc message */
  myMessage.add("some text"); /* add a string to the osc message */
  myMessage.add(new byte[] {0x00, 0x01, 0x10, 0x20}); /* add a byte blob to the osc message */
  myMessage.add(new int[] {1,2,3,4}); /* add an int array to the osc message */

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}

void cube(float x, float y)
{
  background(0.5);
  
  pushMatrix(); 
 
  translate(width/2, height/2, -30); 
  
  newXmag = x/float(width) * TWO_PI;
  newYmag = y/float(height) * TWO_PI;
  
  float diff = xmag-newXmag;
  if (abs(diff) >  0.01) { xmag -= diff/2; }
  
  diff = ymag-newYmag;
  if (abs(diff) >  0.01) { ymag -= diff/2; }
  
  rotateX(-ymag); 
  rotateY(-xmag); 
  
  scale(200);
  beginShape(QUADS);

  fill(0, 1*colorMod, 1*colorMod); vertex(-1,  1,  1);
  fill(1*colorMod, 1*colorMod, 1*colorMod); vertex( 1,  1,  1);
  fill(1, 0, 1); vertex( 3, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);

  fill(1, 1*colorMod, 1); vertex( 1,  1,  1);
  fill(1*colorMod, 1, colorMod); vertex( 1,  1, -1);
  fill(1*colorMod, 0, colorMod); vertex( 1, -1, -1);
  fill(1, 0, 1); vertex( 1, -1,  1);

  fill(1*colorMod, 1*colorMod, 0); vertex( 1,  1, -1);
  fill(0, 1*colorMod, 0); vertex(-1,  1, -1);
  fill(colorMod, colorMod, 0); vertex(-1, -1, -1);
  fill(1, 0, colorMod); vertex( 1, -1, -1);

  fill(colorMod, 1, colorMod); vertex(-1,  1, -1);
  fill(colorMod, 1*colorMod, 1); vertex(-1,  1,  1);
  fill(0, colorMod, 1); vertex(-1, -1,  1);
  fill(colorMod, 0, 0); vertex(-1, -1, -1);

  fill(0, 1*colorMod, 0); vertex(-1,  1, -1);
  fill(1, 1*colorMod, 0); vertex( 1,  1, -1);
  fill(1, 1*colorMod, 1); vertex( 1,  1,  1);
  fill(colorMod, 1, 1); vertex(-1,  1,  1);

  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(1*colorMod, colorMod, 0); vertex( 1, -1, -1);
  fill(1*colorMod, colorMod, 1); vertex( 1, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);

  endShape();
  
  popMatrix(); 
 
  
}
/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  if(theOscMessage.get(1).intValue() == 1 && theOscMessage.get(0).intValue() ==1)
  {
  px = theOscMessage.get(2).floatValue()*-5;
  py = theOscMessage.get(3).floatValue()*5;
  visible = 1==theOscMessage.get(4).intValue();
  }else if(theOscMessage.get(1).intValue() == 1 && theOscMessage.get(0).intValue() ==2)
  {
  colorMod = theOscMessage.get(3).floatValue()/300;
  }
}
