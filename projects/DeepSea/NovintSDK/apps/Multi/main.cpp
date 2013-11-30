// Copyright 2007 Novint Technologies, Inc. All rights reserved.
// Available only under license from Novint Technologies, Inc.
//
// main.cpp
//
// Basic application showing use of HDAL.
// Haptic interaction with a ball.
// Graphic display of cursor.
// Selection among multiple devices

#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "glut.h"
#include <vector>

#include <hdl/hdl.h>
#include <hdlu/hdlu.h>

#include <tchar.h>
#include "Serial.h"

// A structure to maintain data for each device and associated cursor
struct HapticDevice
{
    HDLDeviceHandle handle;
    double workspaceDims[6];
    double cursorPos[3];
    double transformMat[16];
    double force[3];
    bool   button;
    GLfloat* color;
};

// numeric constants
const double kPI = 3.1415926535897932384626433832795;
const double MAX_FORCE = 15; // SHOULD NOT BE MUCH HIGHER THAN 10

// Cursor colors
GLfloat CURSOR_BLUE[3]   = {0.0, 0.0, 1.0};
GLfloat CURSOR_RED[3]    = {1.0, 0.0, 0.0};
GLfloat CURSOR_GREEN[3]  = {0.0, 1.0, 0.0};
GLfloat CURSOR_YELLOW[3] = {1.0, 1.0, 0.0};
GLfloat CURSOR_ORANGE[3] = {1.0, 0.5, 0.0};
GLfloat* gColorChoice[4] = {CURSOR_BLUE, CURSOR_RED, CURSOR_GREEN, CURSOR_YELLOW};
char*   gColorName[4] = {"Blue", "Red", "Green", "Yellow"};

bool    gSelectionDone = true;

typedef std::vector<HapticDevice> HDContainer;
HDContainer g_device;

HDLServoOpExitCode g_touchOp = HDL_INVALID_HANDLE;
HDLDeviceHandle g_uninitHandle;


double gLastTime = 0;
double gCursorScale;
GLuint gCursorDisplayList = 0;

// These constants control the relative sizes of ball and cursor.
// and the relative position of the balls
int gBallsPerRow = 7; // 3 to 10
double gCursorRadius = 0.25; //0.01 to 0.5
double gBP = 1; // 0 to 1;
double gBR = gBP*2/(gBallsPerRow-1); //0.85;
double gBPZ = 0.3-gBR-gCursorRadius;

// initialize the number of cursors and balls
const int gMaxBalls = 100; // max of 10 by 10
int		gNumCursors = 0;
int		gNumDevices = 0;
int		gNumBalls = gBallsPerRow * gBallsPerRow; 

// variables for ball kinematics
double gBallRadius[gMaxBalls];
double gBallPosition[gMaxBalls][3];
double gBallVelocity[gMaxBalls][3];

// These two constants tune the ball dynamics.
const double gBM = 100;
const double gBV = 100;
double gBallMass[gMaxBalls]; 
double gBallViscosity[gMaxBalls];

// These controls the activation of local and general behaviors
// Local stiffness is always enabled
typedef enum {
	inflNONE = 0,
	inflOPOSITE,
	inflGROUPS,
	inflWAVES
} infl;
typedef enum {
	elstcNONE = 0,
	elstcBAND,
	elstcHELP,
	elstcWATER
} elstc; 
const bool enableSliding = true;
const int enableElastics = elstcHELP;
const int enableInflation = inflNONE;

// These controls the cursor/ball force interaction
const double gBallStiffness = 10.0; //40.0;
const double gBallSlideness = 20.0; //40.0

// These controls the falcon/falcon elastic string interaction
const double gElasticStiffness = 40.0;
const double gGoHelpSpeed = 100.0;
const double gWaveSpeed = 10.0;

// The inflation wave effect variables
int waveCounter = 0;

// Serial port instance
const bool enableSerial = false;
CSerial serial;
LPCSTR port = "COM1";

// Methods Declarations
void glutDisplay(void);
void glutReshape(int width, int height);
void glutIdle(void);    
void glutKeyboard(unsigned char key, int x, int y);

void exitHandler(void);

void initGL();
void initHDL();
void initScene();

void resetBallPosition();
void inflateOpositeBalls(int cb, double pd);
void inflateGroupBalls(int cb, double pd);

void drawGraphics();
void drawCursor(HapticDevice& device);

void updateWorkspaceMapping(HapticDevice& device);
void vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3]);

void testHDLError(const char* str);

int SerialSetup(LPCTSTR port, CSerial::EBaudrate baud, CSerial::EDataBits data, CSerial::EParity par, CSerial::EStopBits stop, CSerial::EHandshake handshake);
int SerialWrite (char* str);
int SerialWriteInt (int val);
int SerialWriteFlo (float val);
int SerialWriteDou (double val);
int SerialWriteIntVector3 (int* val);
int SerialWriteFloVector3 (float* val);
int SerialWriteDouVector3 (double* val);

void FalconWrite(int fd);

namespace 
{
double getSystemTime()
{
    static double s_wavelength = 0.0;
    static double s_wavelength_x_high = 0.0;
    static bool s_isFirstTime = true;

    if (s_isFirstTime)
    {
        LARGE_INTEGER l_frequency = { 0 };
        ::QueryPerformanceFrequency(&l_frequency);
        s_wavelength = 1.0 / double(l_frequency.LowPart);
        s_wavelength_x_high = s_wavelength * double(MAXDWORD);
        s_isFirstTime = false;
    }

    LARGE_INTEGER l_ticks = { 0 };
    ::QueryPerformanceCounter(&l_ticks);

    return s_wavelength_x_high * double(l_ticks.HighPart) +
           s_wavelength * double(l_ticks.LowPart);
}
};

int main(int argc, char *argv[])
{
    // Check command line.
    // This is not intended as a model for how to get command line options.

    if (argc > 1)
    {
        gNumCursors = atoi(argv[1]);
    }

    // Check to see if we have enough devices connected to support the
    // user's request.

    gNumDevices = hdlCountDevices();
    if (gNumDevices < gNumCursors)
    {
        printf("You requested %d devices, but only %d are connected.\n",
                gNumCursors, gNumDevices);
        printf("Continuing with %d devices/cursors.\n", gNumDevices);
        gNumCursors = gNumDevices;
    }

    // If we are in two-device mode and don't have two devices, just quit.
    if (gNumCursors == 0 && gNumDevices < 1) 
    {
        printf("You do not have enough Falcons connected.  I quit.\n");
        exit(1);
    }

	// set up the position of the balls;
	resetBallPosition();

    // General OpenGL and GLUT initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("HDAL Multi Demo");

    // Move graphic window away from console so user can see output
    glutPositionWindow(100, 100);

    glutDisplayFunc(glutDisplay);
    glutReshapeFunc(glutReshape);
    glutIdleFunc(glutIdle);
    glutKeyboardFunc(glutKeyboard);

	// Setup Serial communication
	SerialSetup(port, CSerial::EBaud115200,CSerial::EData8,CSerial::EParNone,CSerial::EStop1,CSerial::EHandshakeHardware);
   
    // Simple way to handle all exits
    atexit(exitHandler);

    // Specific graphic and haptic setup
    initScene();

	// push device front
	//while (g_device[0].cursorPos[2] < 1)
	//	g_device[0].force[2] = 5;
	/*double initialToolPos[3] = {0, 0, 1};
	hdlMakeCurrent(g_device[0].handle);
	hdlToolPosition(initialToolPos);
	*/

    // Now do it.  We never return from here.
    glutMainLoop();

    // This keeps the compiler from whining about no return statement.
    return 0;
}

void defineBallPosition()
{
	for (int row=0; row<gBallsPerRow; row++)
    {
		for (int col=0; col<gBallsPerRow; col++)
		{
			int j = row*gBallsPerRow + col;
			double bsp = gBP*2/(gBallsPerRow - 1);// ball spacing
			
			gBallPosition[j][0] = gBP*bsp*row - gBP;
			gBallPosition[j][1] = gBP*bsp*col - gBP;
			gBallPosition[j][2] = gBPZ;
		}
	}
}

// reseting ball position + kinematic + dynamic ball parameters
void resetBallPosition()
{
	for (int j=0; j<gNumBalls; j++)
    {
		gBallRadius[j] = gBR;
		
		defineBallPosition();
		// reset kinematics
		for (int i = 0; i < 3; i++) {
		//	gBallPosition[j][i] = gBallInitialPosition[j][i];
			gBallVelocity[j][i] = 0;
		}

		// reset dynamics
		gBallMass[j] = gBM;
		gBallViscosity[j] = gBV;
    }
}

// Handle keyboard.
void glutKeyboard(unsigned char key, int x, int y)
{
    static bool inited = true;

    // Enable the Escape key to exit the app
    if (key == 27) // esc key
    {
        // This looks nasty, but remember we set up the exit handler
        // during initialization.
        exit(0);
    }

    // Enable the 'r' key to reset the ball.  This should really be
    // smarter, since this simple-minded method will likely bump a
    // cursor.
    if (key == 'r')
    {
		resetBallPosition();
    }


}

// draw function
void glutDisplay()
{   
    drawGraphics();
    glutSwapBuffers();
}

// reshape function (handle window resize)
void glutReshape(int width, int height)
{
    static const double kFovY = 40;

    double nearDist, farDist, aspect;

    glViewport(0, 0, width, height);

    nearDist = 1.0 / tan((kFovY / 2.0) * kPI / 180.0);
    farDist = nearDist + 2.0;
    aspect = (double) width / height;
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(kFovY, aspect, nearDist, farDist);

    /* Place the camera down the Z axis looking at the origin */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();            
    gluLookAt(0, 0, nearDist + 1.0,
              0, 0, 0,
              0, 1, 0);

    
    for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
    {
        if ((*it).handle != HDL_INVALID_HANDLE)
            updateWorkspaceMapping(*it);
    }
}

void glutIdle()
{
    glutPostRedisplay();
}

void initScene()
{
    initGL();
    initHDL();
}

void updateWorkspaceMapping(HapticDevice& device)
{
    // create mapping from device to application workspace coordinates
    // device workspace comes from hdlDeviceWorkspace call
    // application workspace is unit cube

    //double gameWorkspace[] = {-1,-1,-1,1,1,1};
	double gameWorkspace[][6] = {{-1,0,-1,0,1,1},{0,0,-1,1,1,1},
								{-1,-1,-1,0,0,1},{0,-1,-1,1,0,1}};
    bool useUniformScale = true;
    hdluGenerateHapticToAppWorkspaceTransform(device.workspaceDims,
                                              gameWorkspace[device.handle],
                                              useUniformScale,
                                              device.transformMat);

    testHDLError("hdluGenerateHapticToAppWorkspaceTransform");
}

void initGL()
{
    static const GLfloat light_model_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    static const GLfloat light0_diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};   
    static const GLfloat light0_direction[] = {0.0f, -0.4f, 1.0f, 0.0f};    
    
    /* Enable depth buffering for hidden surface removal. */
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    /* Cull back faces. */
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    /* Set lighting parameters */
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    glEnable(GL_LIGHT0);   
}

// This is the workhorse function to calculate the force exerted
// on the cursor due to contact with the ball.
void ballToolContact(int fd, double pos[3], double force[3])
{
	// make sure the forces are zero
    force[0] = 0; force[1] = 0; force[2] = 0;

    // Get cursor position relative to ball
	double rpos[gMaxBalls][3];
	double eucl[gMaxBalls];
	int closestBall = 0;
	double toolDist = gBP*2;
	for (int j = 0; j < gNumBalls; j++) {
		rpos[j][0] = pos[0] - gBallPosition[j][0];
		rpos[j][1] = pos[1] - gBallPosition[j][1];
		rpos[j][2] = pos[2] - gBallPosition[j][2];
		eucl[j] = sqrt(rpos[j][0]*rpos[j][0] + rpos[j][1]*rpos[j][1] + rpos[j][2]*rpos[j][2]);
		if (eucl[j] < toolDist) {
			closestBall = j;
			toolDist = eucl[j];
		}
	}

	// Wave inflation effect variables
	//static int counter = 0;
	static bool activateWave = false;
    static double waveDst[gMaxBalls];
	static double waveAmp;

    // Force is proportional to distance, if touching ball, else zero
    if (toolDist - gCursorRadius < gBallRadius[closestBall])
    {
		// Force based on stiffness of ball
		double penetrationDist = gBallRadius[closestBall] - (toolDist - gCursorRadius);
        double forceScale = penetrationDist * gBallStiffness;

		if (penetrationDist > (gBallRadius[closestBall] / 2))
			forceScale *= 2;
		/*else if (penetrationDist > (gBallRadius[closestBall] / 3))
			forceScale *= 3;*/

		force[0] = rpos[closestBall][0]/toolDist * forceScale;
		force[1] = rpos[closestBall][1]/toolDist * forceScale;
		//force[2] = rpos[closestBall][2]/toolDist * forceScale;
		force[2] = forceScale* 10; // react mostly upwards!

		// Force based on slideness of ball
		double slideScale = penetrationDist * gBallSlideness;
		static bool dir_cw = false;

		if (penetrationDist > (gBallRadius[closestBall] / 2))
			slideScale *= 2;
		/*else if (penetrationDist > (gBallRadius[closestBall] / 3))
			slideScale *= 3;*/

		// Sliding force is ortogonal force in cw or ccw direction (x,y)
		// force in z will always push up
		if (dir_cw) {		
			force[0] += (rpos[closestBall][1]/toolDist) * slideScale;
			force[1] -= (rpos[closestBall][0]/toolDist) * slideScale;
		}
		else {
			force[0] -= (rpos[closestBall][1]/toolDist) * slideScale;
			force[1] += (rpos[closestBall][0]/toolDist) * slideScale;
		}
		//force[2] += slideScale;
		
		// inflate other balls
		switch (enableInflation)
		{
		case inflOPOSITE:
			inflateOpositeBalls(closestBall, penetrationDist);
			break;
		case inflGROUPS:
			inflateGroupBalls(closestBall, penetrationDist);
			break;
		case inflWAVES:
			if (!activateWave && penetrationDist > (gBallRadius[closestBall] * 0.7)) {
				activateWave = true;
				waveCounter = 0;
				waveAmp = penetrationDist;
				for (int j=0; j<gNumBalls; j++)
					waveDst[j] = eucl[j];
			}
		}
    }

	// The inflateWaves effect has to be able to perform even if ball not touched anymore
	if (enableInflation == inflWAVES && activateWave) {
		double waveR = waveCounter/2000;
		
		for (int j=0; j<gNumBalls; j++) {
			if (waveDst[j] > waveR && waveDst[j] < waveR + 0.5)
				gBallRadius[j] = gBR + waveAmp;
			else
				gBallRadius[j] = gBR;
		}
		if (waveR > 3) {
			waveCounter = 0;
			activateWave = false;
		}
		else
			waveCounter ++;
	}
		
}

void inflateOpositeBalls(int closestBall, double penetrationDist) {
	// ball-cap parameters
	double r = gBR;
	double h = penetrationDist;
	double a = sqrt((r*r)-((r-h)*(r-h)));

	// volume of the sphere and the deflated part
	double Vball = 4*kPI/3 * (r*r*r);
	double Vdef = kPI*h/6 * (3*a*a + h*h);
	double Vinf = Vball + Vdef;
	
	// find the new ball inflated radius
	//double dr = (pow(3*Vinf/(4*kPI),(double)(1/3)) - gBR);
	double dr = h/2;

	// do not inflate center ball
	int ballToInflate = -1;
	if (gNumBalls%2 == 0 || closestBall != (gNumBalls-1)/2)
		ballToInflate = gNumBalls-closestBall-1;

	for (int i = 0; i<gNumBalls; i++) {
		if (ballToInflate >= 0 && ballToInflate == i)
			gBallRadius[i] = gBR + dr;
		//else
		//	gBallRadius[i] = gBR;
	}
}

void inflateGroupBalls(int closestBall, double penetrationDist) {
	// ball-cap parameters
	double r = gBR;
	double h = penetrationDist;
	double a = sqrt((r*r)-((r-h)*(r-h)));

	// volume of the sphere and the deflated part
	double Vball = 4*kPI/3 * (r*r*r);
	double Vdef = kPI*h/6 * (3*a*a + h*h);
	double Vinf = Vball + Vdef;
	
	// find the new ball inflated radius
	//double dr = (pow(3*Vinf/(4*kPI),(double)(1/3)) - gBR);
	double dr = h/2;

	// ball relations to deflate->inflate
	int groupBalls[][4] = {{0, 2, 6, 8},
							{1, 3, 5, 7}};

	// check which ball group does the deflated ball belongs
	int closestGroup = -1;
	for (int j=0; j<sizeof(groupBalls)/sizeof(groupBalls[0]); j++)
	{
		for (int i=0; i<sizeof(groupBalls[j])/sizeof(int); i++){
			if (closestBall == groupBalls[j][i]) {
				closestGroup = j;
				break;
			}
		}
	}
	// inflate other balls in the group based on which ball was deflated
	if (closestGroup >= 0) {
		for (int i=0; i<sizeof(groupBalls[closestGroup])/sizeof(int); i++){
			if (closestBall != groupBalls[closestGroup][i])
				gBallRadius[groupBalls[closestGroup][i]] = gBR + dr;
		}
	}
}

// This is the workhorse function to calculate the force exerted
// between a cursor and a lead cursor
void falconElasticForce(int fd, int fd_lead, double pos[3], double pos_lead[], double force[3])
{
	//static int counter = 0;
	static double prev_force[3];

	// make sure the force is zero
	force[0] = 0; force[1] = 0; force[2] = 0;

	// Get cursor position relative to the lead cursor
	double eblength[][4] = {{0, 1, 1, sqrt(2.0)},
							{1, 0, sqrt(2.0), 1},
							{1, sqrt(2.0), 0, 1},
							{sqrt(2.0), 1, 1, 0}};
	double rpos[3];
	double cursorDist;
	double forceScale = 0;

	rpos[0] = pos_lead[0] - pos[0];
	rpos[1] = pos_lead[1] - pos[1];
	rpos[2] = pos_lead[2] - pos[2];
	cursorDist = sqrt(rpos[0]*rpos[0] + rpos[1]*rpos[1] + rpos[2]*rpos[2]);

	// static variables for General force effects
	static bool wavein = false;

	switch (enableElastics) {
	case elstcBAND:
		// force is proportional to the elastic band distance if higher than 10%
		if (abs(cursorDist - eblength[fd_lead][fd]) > eblength[fd_lead][fd]/10 ) 
		{
			forceScale = gElasticStiffness * (cursorDist - eblength[fd_lead][fd]);

			for (int i = 0; i < 2; i++) { // do not use z axis
				force[i] = (rpos[i] * forceScale) * 0.01 + prev_force[i] * 0.99;
				prev_force[i] = force[i];
			}
		}
		break;
	case elstcHELP:
		// immediately help if the lead cursor is below the allowed position more than time_thershold seconds
		forceScale = gGoHelpSpeed;
		if (pos_lead[2] < - abs(gBPZ))// && timer > time_threshold) 
		{
			for (int i = 0; i < 2; i++) { // do not use z axis
				force[i] = (rpos[i] * forceScale) * 0.01 + prev_force[i] * 0.99;
				prev_force[i] = force[i];
			}
		}
		break;
	case elstcWATER:
		// wave like water if the lead cursor is below the allowed position more than time_thershold seconds
		if (pos_lead[2] < - abs(gBPZ))// && timer > time_threshold) 
		{
			if (wavein) {
				if (cursorDist < 0.2)
					wavein = false;
				forceScale = gWaveSpeed;
			}
			else
			{
				if (cursorDist > 1.5)
					wavein = true;
				forceScale = -gWaveSpeed;
			}
		
			for (int i = 0; i < 2; i++) { // do not use z axis
				force[i] = (rpos[i] * forceScale) * 0.01 + prev_force[i] * 0.99;
				prev_force[i] = force[i];
			}
		}
		break;
	}
	
	
	
}

void computeBallPosition()
{
	// We have the forces, now compute a new ball position
        // Position algorithm:
        //    a = (F - zeta*v)/m    (F = m*a + zeta*v)
        //    v = a*dt + v0
        //    p = v*dt + p0

        double forceSum[3] = {0, 0, 0};
        double acc[3] = {0, 0, 0};
        int i, j;

        // Start by computing reaction force F from sum of all cursor forces
        for (HDContainer::iterator iter = g_device.begin(); iter != g_device.end(); ++iter)
            for (i = 0; i < 3; i++)
                forceSum[i] -= (*iter).force[i];

        // Add in viscosity force to get (F - zeta*v)
		for (j = 0; j < gNumBalls; j++) {
			for (i = 0; i < 3; i++)
				forceSum[i] -= gBallViscosity[j] * gBallVelocity[j][i];
		}

        // Divide by mass for a = (F - zeta*v)/m
		for (j = 0; j < gNumBalls; j++) {
			for (i = 0; i < 3; i++)
				acc[i] = forceSum[i] / gBallMass[j];
		}

        // Now do Euler integration
        double thisTime = getSystemTime();
        double dt = thisTime - gLastTime;

        for (j=0; j<gNumBalls; j++) {
			for (i = 0; i < 3; i++)
				gBallVelocity[j][i] += acc[i] * dt;
 			for (i = 0; i < 3; i++)
				gBallPosition[j][i] += gBallVelocity[j][i] * dt;
		}
        gLastTime = thisTime;

        // Uncomment the following to play around with ball dynamics
        // and see the results
        /*
        printf("%8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
            gBallVelocity[0], gBallVelocity[1], gBallVelocity[2],
            gBallPosition[0], gBallPosition[1], gBallPosition[2]);
        */
    
		
}


// This is the callback function that is exercised at servo rate (1KHz)
HDLServoOpExitCode touchScene(void* pUserData)
{
	// position variables
    double posDC[3];
    double posWC[3];
	double posDC_lead[3];
	double posWC_lead[3];
    
	// ball-contact and facon-elastic force variables
	double bt_force[4][3];
	double el_force[4][3];
	double sum_force[3];
	static double prev_force[4][3];

	// max tool force variables
	double tf[4];
	double eucl_force = 0;
	double max_tf = 0;
	int max_tfi = -1;

	// the loop counter for serial port printing
	static int serialCounter =  0;

	// Initialize time
    if (gLastTime == 0) gLastTime = getSystemTime();

    if (gSelectionDone)
    {
		// Position and Ball-Tool force
        for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
        {
            // Calculate and set forces for each device that has not
            // been uninited.
            if ((*it).handle != HDL_INVALID_HANDLE)
            {
                hdlMakeCurrent((*it).handle);

                // find workspace position
				hdlToolPosition(posDC);
				testHDLError("hdlToolPosition");
                vecMultMatrix(posDC, (*it).transformMat, posWC);

				// get ball-tool interaction force
				bt_force[(*it).handle][0] = 0; bt_force[(*it).handle][1] = 0; bt_force[(*it).handle][2] = 0;
				ballToolContact((*it).handle, posWC, bt_force[(*it).handle]);
				
				// find "lead" cursor with max force and corresponding force
				tf[(*it).handle] = sqrt(bt_force[(*it).handle][0]*bt_force[(*it).handle][0] + 
					bt_force[(*it).handle][1]*bt_force[(*it).handle][1] +
					bt_force[(*it).handle][2]*bt_force[(*it).handle][2]);
				if (tf[(*it).handle] > max_tf) {
					max_tf = tf[(*it).handle];
					max_tfi = (*it).handle;

					// save the position of the lead cursor
					for (int i=0; i<3; i++) {
						posDC_lead[i] = posDC[i];
						posWC_lead[i] = posWC[i];
					}
				}

            }
        }

		// tool-tool interaction force based on max ball-tool force
		for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
        {
			// Calculate and set forces for each device that has not
			// been uninited.
			if ((*it).handle != HDL_INVALID_HANDLE)
			{
				hdlMakeCurrent((*it).handle);

				//initialize forces to be zero
				el_force[(*it).handle][0] = 0; el_force[(*it).handle][1] = 0; el_force[(*it).handle][2] = 0;

				if (max_tf > gElasticStiffness && (*it).handle != max_tfi) {
					// find workspace position
					hdlToolPosition(posDC);
					testHDLError("hdlToolPosition");
					vecMultMatrix(posDC, (*it).transformMat, posWC);

					// get tool-tool interaction
					falconElasticForce((*it).handle, max_tfi, posWC, posWC_lead, el_force[(*it).handle]);
				}

			}

			// Set ToolForce
			for (int i = 0; i < 3; i++){
				sum_force[i] = (bt_force[(*it).handle][i] + el_force[(*it).handle][i]) * 0.1 + prev_force[(*it).handle][i] * 0.9;
				prev_force[(*it).handle][i] = sum_force[i];
				
				// limit the force so is never more than MAX_FORCE
				if (sum_force[i] < 0)
					sum_force[i] = max(sum_force[i], -MAX_FORCE);
				else
					sum_force[i] = min(sum_force[i], MAX_FORCE);
				
				// the magnitude of the sum_force
					eucl_force += sum_force[i]*sum_force[i];
				// save in haptic device structure
				(*it).force[i] = sum_force[i];
			}
			// magnitude
			eucl_force = sqrt(eucl_force);

			hdlSetToolForce(sum_force);
			testHDLError("hdlSetToolForce");

			// print the falcon position every 100th loop
			if (enableSerial) {
				//if (toolDist < gBallRadius[closestBall]*0.75 && counter > 100) {
				if (eucl_force > MAX_FORCE/3 && serialCounter > 100) {
					FalconWrite((*it).handle);
					serialCounter = 0;
					//dir_cw = !dir_cw;
				}
			}

		}

		//computeBallPosition();

		if(enableSerial)
			serialCounter ++;
		
	}
    return HDL_SERVOOP_CONTINUE;
}

// Check HDAL error and report with user-defined string
void testHDLError(const char* str)
{
    HDLError err = HDL_NO_ERROR;
    err = hdlGetError();
    if (err != HDL_NO_ERROR)
    {
        char msg[200];
        sprintf_s(msg, "HDAL ERROR %d", err);
        MessageBox(NULL, str, msg, MB_OK);
        exit(1);
    }
}

// Initialize device by hdal.ini section name
void initDevice(const char* deviceName, GLfloat* color = CURSOR_ORANGE)
{
    HDLError err = HDL_NO_ERROR;

    HapticDevice hd;
    hd.handle = hdlInitNamedDevice(deviceName);
    hd.color = color;
    for (int i = 0; i < 3; i++)
    {
        hd.force[i] = 0;
    }
    char msg[200];
    sprintf_s(msg, "Cannot init %s", deviceName);
    testHDLError(msg);
    if (hd.handle < 0)
    {
        MessageBox(NULL, msg, "Named Initialization error", MB_OK);
        abort();
    }

    g_device.push_back(hd);
}

// Initialize device by index into (hidden) device list.
// Note that the application does not have access to list of device
// serial numbers.  It only knows how many devices are in the list.
void initIndexedDevice(const int ndx,  GLfloat* color = CURSOR_ORANGE)
{
    HDLError err = HDL_NO_ERROR;

    HapticDevice hd;
    hd.handle = hdlInitIndexedDevice(ndx);
    hd.color = color;
    for (int i = 0; i < 3; i++)
    {
        hd.force[i] = 0;
    }
    char msg[200];
    sprintf_s(msg, "Cannot init %d", ndx);
    testHDLError(msg);
    if (hd.handle < 0)
    {
        MessageBox(NULL, msg, "Indexed Initialization error", MB_OK);
        abort();
    }

    g_device.push_back(hd);
}

// Get all the devices' state information
HDLServoOpExitCode GetStateCB(void* pUserData)
{
    for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
    {
        if ((*it).handle != HDL_INVALID_HANDLE)
        {
            HapticDevice& hd = *it;

            hdlMakeCurrent(hd.handle);
            hdlToolPosition(&(hd.cursorPos[0]));
            hdlToolButton(&(hd.button));
            testHDLError("hdlToolPosition");
        }
    }

    return HDL_SERVOOP_EXIT;
}

// This is the entry point used by the application to synchronize
// data access to the device.  Using this function eliminates the 
// need for the application to worry about threads.
void synchFromServo()
{
    hdlCreateServoOp(GetStateCB, 0, true);
}

// Wait for user to press, then release, a button on a device.
// Return index into application's list of handles.  Skip devices
// that have already been selected.  Use orange color to indicate
// devices that have not yet been selected.
int waitForButton()
{
    int id = 0;

    // Rotate through all attached devices looking for a button press
    while (true)
    {
        if (g_device[id].handle != HDL_INVALID_HANDLE && 
            g_device[id].color == CURSOR_ORANGE)
        {
            synchFromServo();
            if (g_device[id].button) break;
        }

        if (++id == gNumDevices) id = 0;

    }

    // Got a button, now wait until it's released
    while (g_device[id].button)
    {
        // Cheap debouncing
        synchFromServo();
        Sleep(100);
    }

    return id;
}

/* initHDL() sets up the HDAL connections.
   The main purpose is to associate specific devices with application functions.
   In this case, the functions are colored cursors.
   Option 1: No command line parameters
             Use named sections in hdal.ini.  Requires device SNs
   Option 2: Execution-time selection
             Number of cursors to use is passed on the command line and
             remembered in global variable gNumCursors.
             Prompt the user to press a button on the device to use for
             control of specified cursors.  Uninitialize left-over
             devices if there are any. */
void initHDL()
{

    
    if (gNumCursors == 0)
    {
        // Option 1: Use device names that match your config file
        initDevice("FALCON_1", CURSOR_BLUE);
        //initDevice("FALCON_2", CURSOR_RED);
		initDevice("FALCON_6", CURSOR_RED);
		initDevice("FALCON_3", CURSOR_GREEN);
		//initDevice("FALCON_4", CURSOR_YELLOW);
        initDevice("FALCON_5", CURSOR_YELLOW);
		/*initDevice("NullDriver", CURSOR_BLUE);
		initDevice("NullDriver", CURSOR_RED);
		initDevice("NullDriver", CURSOR_GREEN);
        initDevice("NullDriver", CURSOR_YELLOW);*/
        hdlStart();
    }
    else
    {
        // Option 2: Let user select from connected devices.
        // Start up required devices
        gSelectionDone = false;
        for (int i = 0; i < gNumDevices; i++)
        {
            initIndexedDevice(i);
        }
        hdlStart();
        Sleep(1000);  // Wait for data to stabilize

        // It is possible to have more devices connected than needed
        for (int ic = 0; ic < gNumCursors; ic++)
        {
            printf("Press a button on the Falcon you wish to use to control the %s cursor: ",
                gColorName[ic]);
            int id = waitForButton();
            printf("%d\n", id);
            hdlMakeCurrent(g_device[id].handle);
            g_device[id].color = gColorChoice[ic];
        }

        // Now we know which devices are used, let's delete the ones not used.
        // Note that one of the selected devices is current, and all selected devices
        //   have colors other than orange.
        for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); it++)
        {
            if ((*it).color == CURSOR_ORANGE)
            {
                hdlUninitDevice((*it).handle);
                (*it).handle = HDL_INVALID_HANDLE;
            }
        }
        

        gSelectionDone = true;
    }


    // Set up workspace dimensions
    for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
    {
        if ((*it).handle != HDL_INVALID_HANDLE)
        {
            hdlMakeCurrent((*it).handle);
            hdlDeviceWorkspace((*it).workspaceDims);
        }
    }

    const bool bBlocking = false;
    g_touchOp = hdlCreateServoOp(touchScene,
                                 (void*)0,
                                 bBlocking);
    testHDLError("hdlCreateServoOp");
}

void exitHandler()
{
    // Close the serial port
	if (serial.IsOpen())
	{
		serial.Close();
	}
	
	if (g_touchOp != HDL_INVALID_HANDLE)
    {
        hdlDestroyServoOp(g_touchOp);
        g_touchOp = HDL_INVALID_HANDLE;
    }
    hdlStop();

    for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
    {
        if ((*it).handle != HDL_INVALID_HANDLE)
            hdlUninitDevice((*it).handle);
    }
}

void drawGraphics()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           

    for (HDContainer::iterator it = g_device.begin(); it != g_device.end(); ++it)
    {
        if ((*it).color != CURSOR_ORANGE)
            drawCursor(*it);
    }

    for (int j=0; j<gNumBalls; j++) {
		glPushMatrix();
		glTranslatef(gBallPosition[j][0], gBallPosition[j][1], gBallPosition[j][2]);
		glutSolidSphere(gBallRadius[j], 32, 32);
		glPopMatrix();
	}
}


// dstVec = srcVec * mat
void vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3])
{
    dstVec[0] = mat[0] * srcVec[0] 
        + mat[4] * srcVec[1]
        + mat[8] * srcVec[2]
        + mat[12];
    
    dstVec[1] = mat[1] * srcVec[0]
        + mat[5] * srcVec[1]
        + mat[9] * srcVec[2]
        + mat[13];

    dstVec[2] = mat[2] * srcVec[0]
        + mat[6] * srcVec[1]
        + mat[10] * srcVec[2]
        + mat[14];
}

void drawCursor(HapticDevice& device)
{
    static const int kCursorTess = 15;
    synchFromServo();
    testHDLError("hdlCreateServoOp");

    // transform cursor position from device coordinates
    // to world coordinates
    double cursorPosWC[3];
    vecMultMatrix(device.cursorPos, device.transformMat, cursorPosWC);

	GLUquadricObj *qobj = 0;

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
    glPushMatrix();

    if (!gCursorDisplayList)
    {
        gCursorDisplayList = glGenLists(1);
        glNewList(gCursorDisplayList, GL_COMPILE);
        qobj = gluNewQuadric();
               
        gluSphere(qobj, gCursorRadius, kCursorTess, kCursorTess);

        gluDeleteQuadric(qobj);
        glEndList();
    }
    
    glTranslatef(cursorPosWC[0], cursorPosWC[1], cursorPosWC[2]);

    glEnable(GL_COLOR_MATERIAL);
    if (device.button)
    {
        glColor3fv(CURSOR_ORANGE);
    }
    else
    {
        glColor3fv(device.color);
    }

    glCallList(gCursorDisplayList);

    glPopMatrix(); 
    glPopAttrib();
}

//==============================================================
// Error Functions
//==============================================================

LONG lLastError = ERROR_SUCCESS;

int ShowError (LONG lError, LPCTSTR lptszMessage)
{
	// Generate a message text
	TCHAR tszMessage[256];
	wsprintf(tszMessage,_T("%s\n(error code %d)"), lptszMessage, lError);

	// Display message-box and return with an error-code
	::MessageBox(0,tszMessage,_T("Error Message"), MB_ICONSTOP|MB_OK);
	return 1;
}

//==============================================================
// SendingFalconData through Serial
//==============================================================

void FalconWrite (int fd)
{
		//Write Falcon handle
		SerialWrite("Falcon ");
		SerialWriteInt(g_device[fd].handle);
		SerialWrite("; ");
		
		//Write Falcon position
		SerialWrite("Position ");
		SerialWriteDouVector3(g_device[fd].cursorPos);
		SerialWrite("; ");

		//Write Falcon force
		SerialWrite("Force ");
		SerialWriteDouVector3(g_device[fd].force);
		SerialWrite("\n");
}

//==============================================================
// Serial Port Functions
//==============================================================

int SerialSetup (LPCTSTR port, CSerial::EBaudrate baud, CSerial::EDataBits data, CSerial::EParity par, CSerial::EStopBits stop, CSerial::EHandshake handshake)
{
// Attempt to open the serial port 
    lLastError = serial.Open(port,0,0,false);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to open COM-port"));

    // Setup the serial port (9600,N81) using hardware handshaking
    lLastError = serial.Setup(baud, data, par, stop);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port setting"));

	// Setup handshaking
    lLastError = serial.SetupHandshaking(handshake);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port handshaking"));

	// if no error
	return 0;
}

// Writes string to serial port
int SerialWrite (char* str)
{
	// The serial port is now ready and we can send/receive data. If
	// the following call blocks, then the other side doesn't support
	// hardware handshaking.
    lLastError = serial.Write(str);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to send data"));

	// if no error
	return 0;
}

//---------------------------------------------
// Writes int value to serial port
int SerialWriteInt(int val)
{
	char dst[32];
	sprintf_s(dst, 32, "%d", val);
	return SerialWrite(dst);
}

// Writes float value to serial port
int SerialWriteFlo(float val)
{
	char dst[32];
	sprintf_s(dst, 32, "%f", val);
	return SerialWrite(dst);
}

// Writes double value to serial port
int SerialWriteDou(double val)
{
	char dst[32];
	sprintf_s(dst, 32, "%f", val);
	return SerialWrite(dst);
}
//---------------------------------------------
// Writes an int vector of size 3 to serial port
int SerialWriteIntVector3(int* vals)
{
	char dst[100];
	sprintf_s(dst, "%d, %d, %d", vals[0], vals[1], vals[2]);
	return SerialWrite(dst);
}

// Writes a float vector of size 3 to serial port
int SerialWriteFloVector3(float* vals)
{
	char dst[100];
	sprintf_s(dst, "%f, %f, %f", vals[0], vals[1], vals[2]);
	return SerialWrite(dst);
}

// Writes a double vector of size 3 to serial port
int SerialWriteDouVector3(double* vals)
{
	char dst[100];
	sprintf_s(dst, "%f, %f, %f", vals[0], vals[1], vals[2]);
	return SerialWrite(dst);
}

