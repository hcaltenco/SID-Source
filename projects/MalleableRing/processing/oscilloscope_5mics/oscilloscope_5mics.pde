/* ****************************************************
 
 Processing Code for Microphone Test
 
 **************************************************** */

// import the Processing serial library
import processing.serial.*;

// Linefeed in ASCII
int linefeed = 10; 

// threshold value should match with arduino code
int[] RANGE = {-300,300};
int gridsize = 50;

// value recieved from the serialport / arduino
int n_mics = 6;
int[] sensorValue = new int[n_mics];
int[] prevValue = new int[n_mics];

// the sensor value mapped to the screen size
float[] sensorValueMap = new float[n_mics];
float[] prevValueMap = new float[n_mics];

// threshold values from the serialport
float[] thresholdValue = new float[n_mics];

// capsense value mapped to the screen size
float capsenseValueMap = 0;
float capsensePrevMap = 0;

// the color pallete for each sensor
color[] palette = new color[n_mics];

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Setup

void setup() {
  Serial myPort = new Serial(this, Serial.list()[0], 19200);//9600);

  // read bytes into a buffer until you get a linefeed (ASCII 10):
  myPort.bufferUntil(linefeed);

  size (800, 600);
  background (0);
  //smooth();

  // you need to have this font in your machine, if not go to
  // Tools – Creat Font – and create your own font
  PFont font48 = loadFont("Calibri-48.vlw");
  textFont(font48);
  
  // setup the color palette
  palette[0] = color(0,255,0);
  palette[1] = color(255,100,200);
  palette[2] = color(200,100,0);
  palette[3] = color(0,255,255);
  palette[4] = color(255,0,255);
  palette[5] = color(255,255,255);
}

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Serial Event
void serialEvent(Serial myPort) {
  // read the serial buffer:
  String myString = myPort.readStringUntil(linefeed);

  // if you got any bytes other than the linefeed:
  int[] sensors = new int[n_mics];
  int[] thresholds = new int[n_mics];
    
  if (myString != null) {
    //myString = trim(myString);
    //myString = myString.replace("\t", "");
    
    // split string groups at tabs
    // split the string at the commas
    // and convert the sections into integers:
    String[] splitted = split(myString, ";\t");
    for (int i = 0; i < splitted.length; i++) {
      int subsplitted[] = int(split(splitted[i], ",\t"));
        sensors[i] = subsplitted[0];
      if (subsplitted.length > 1) {
        thresholds[i] = subsplitted[1];
      }
    }
  
    // save values into local variables
    for (int i = 0; i < n_mics; i++) {
      // save in previous value before updating
      prevValue[i] = sensorValue[i];
      prevValueMap[i] = sensorValueMap[i];
  
      sensorValue[i] = sensors[i];
      thresholdValue[i] = thresholds[i];
      
      // map the recieved values
      sensorValueMap[i] = map(sensorValue[i], RANGE[0], RANGE[1], 0, height);
    }
  }
}

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Draw

void draw() {
  // run the displayText() function
  //displayText();
  
  // run the displayPlot() function
  displayPlot();
}

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Display Text

void displayText() {
  // set the black background
  background(0);
  float averageMap = 0;
  // draw the text based on the actual sensorValue
  text("Sensor Value", 20, 80);
  for (int i = 0; i < n_mics; i++ ){
    text(sensorValue[i], 450+10*i, 80);
    averageMap += sensorValueMap[i];
  }
  averageMap /= (float) (n_mics);
  // draw a rectangle based on the variable sensorValueMap
  rect (0, 100, width, averageMap);
}

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Running Plot Mode

int xPos;  // horizontal position of the graph

void displayPlot() {
  // draw the grid
  stroke(127, 34, 255);
  for (int i=0; i < height; i+=gridsize){
    line(0, i, width, i);
    textAlign(LEFT); 
    if (i%(2*gridsize)==0)
      text((int) map(height-i,0,height,RANGE[0],RANGE[1]), 0, i);
  }
  
  // draw threshold lines
  for (int i = 0; i < n_mics; i++) {
    stroke(palette[i]);
    float thres_low = height - map(-thresholdValue[i], RANGE[0],RANGE[1], 0, height);
    float thres_high = height - map(thresholdValue[i], RANGE[0],RANGE[1], 0, height);
    //line(0, thres_val, width, thres_val);
    line(xPos, thres_low, xPos+1, thres_low);
    line(xPos, thres_high, xPos+1, thres_high);
  }
  
  // draw the lines:
  for (int i = 0; i < n_mics; i++) {
    stroke(palette[i]);
    line(xPos, height - prevValueMap[i], xPos+1, height - sensorValueMap[i]);
  }
  
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    background(0);
  } 
  else {
    // increment the horizontal position:
    xPos++;
  }
}

// – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – - – Save image

void keyPressed() {
  if (key=='s')
    saveFrame("sound-######.png");
}


