//-------------------------------------------------------------
// fgen_tutorial_02_FalconPos.nut
//
// Squirrel script for getting the current Falcon position
//-------------------------------------------------------------


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
	print("Script Activated\n");
}


//-------------------------------------------------------------
// Run this script
// Called repeatedly while this acript is active
//-------------------------------------------------------------
function HapticsThink (deviceHandle)
{
	local falcon_X = deviceaxis(deviceHandle, 0);	// 0 = X axis (left/right)
	local falcon_Y = deviceaxis(deviceHandle, 1);	// 1 = Y axis (up/down)
	local falcon_Z = deviceaxis(deviceHandle, 2);	// 2 = Z axis (in/out)

	// do stuff with the Falcon position here....
}


//-------------------------------------------------------------
// Deactivate this script
// called whenever this script stops being active (such as if
// you switch to another window)
//-------------------------------------------------------------
function HapticsDeactivated (deviceHandle)
{
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

