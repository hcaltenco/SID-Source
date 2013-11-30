//-------------------------------------------------------------
// fgen_tutorial_02_sendkeys.nut
//
// Squirrel script for emulating sending keyboard commands
//-------------------------------------------------------------


//============================================
// global effects and variables
//============================================

// ---- setup keyboard settings
gSendCTRL <- inputsender(KEY_LCONTROL);
gSendY <- inputsender(KEY_Y);


//-------------------------------------------------------------
// tap Ctrl+Y
//-------------------------------------------------------------
function TapCTRLandY ()
{
	gSendCTRL.press();
	gSendY.press();

	gSendY.release();
	gSendCTRL.release();
}


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
	if (devicewasbuttonjustpressed(deviceHandle, FALCON_LIGHTNING))
	{	// pressed top falcon button... hit keyboard Ctrl + Y
		TapCTRLandY();
	}
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

