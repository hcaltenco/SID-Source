//-------------------------------------------------------------
// fgen_flightsimX.nut
//
// Squirrel script for F-Gen Microsoft Flight Simulator X
//-------------------------------------------------------------




//========================================================
// setup plugins
//========================================================

// load the mouse cursor plugin
loadplugin("SQTestDLL.dll");


//========================================================
// global variables
//========================================================

gFrameCounter <- 0;


//-------------------------------------------------------------
// Initialize this script
// Called once when this script is first loaded
//-------------------------------------------------------------
function HapticsInitialize (registryConfigHandle)
{
	print("Initialize Script\n");
}


//-------------------------------------------------------------
// Activate this script
// Called whenever this script becomes active (such as after
// returning to the application this script is attached to
// after switching to another window)
//-------------------------------------------------------------
function HapticsActivated (deviceHandle)
{
	// setup log file
	debugLog_open();

	print("Script Activated\n");
}


//-------------------------------------------------------------
// Run this script
// Called repeatedly while this acript is active
//-------------------------------------------------------------
function HapticsThink (deviceHandle)
{
	gFrameCounter = testAddInts(gFrameCounter, 1);

	if (devicewasbuttonjustpressed(deviceHandle, FALCON_LOGO))
	{	// pressed top falcon button... print Falcon handle position to the log file

		// grab the current falcon position
		local falcon_X = deviceaxis(deviceHandle, 0);	// 0 = X axis (left/right)
		local falcon_Y = deviceaxis(deviceHandle, 1);	// 1 = Y axis (up/down)
		local falcon_Z = deviceaxis(deviceHandle, 2);	// 2 = Z axis (in/out)

		debugLog_print("Falcon ");
		debugLog_printInt(deviceHandle);
		debugLog_print(" - Frame ");
		debugLog_printInt(gFrameCounter);
		debugLog_print(" - Falcon Pos = ");
		debugLog_printVector(falcon_X, falcon_Y, falcon_Z);
		debugLog_print("\n");
	}
}


//-------------------------------------------------------------
// Deactivate this script
// called whenever this script stops being active (such as if
// you switch to another window)
//-------------------------------------------------------------
function HapticsDeactivated (deviceHandle)
{
	// close log file
	debugLog_close();

	print("Script Deactivated\n");
}


//-------------------------------------------------------------
// Shutdown this script
// called when this script is cancelled and unloaded
//-------------------------------------------------------------
function HapticsShutdown (  )
{
	print("Shutdown Script\n");
}

