//-------------------------------------------------------------
// fgen_tutorial.nut
//
// Squirrel script for F-Gen Tutorial 01
//-------------------------------------------------------------


// create a keyboard listener
gKeyInput <- inputlistener();


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
	if (devicewasbuttonjustpressed(deviceHandle, FALCON_LOGO))
	{
		print("   ...Falcon LOGO button was just pressed\n");
	}
	else if (devicewasbuttonjustreleased(deviceHandle, FALCON_LOGO))
	{
		print("   ...Falcon LOGO button was just released\n");
	}

	if (devicebuttonisdown(deviceHandle, FALCON_TRIANGLE))
	{
		print("   ... Falcon TRIANGLE button is currently down\n");
	}

	// update the keyboard listener before checking keyboard values
	gKeyInput.update();

	if (gKeyInput.wasinputjustpressed(KEY_1))
	{
		print("   ... 1 key was just pressed\n");
	}
	else if (gKeyInput.wasinputjustreleased(KEY_1))
	{
		print("   ... 1 key was just released\n");
	}

	if (gKeyInput.isinputdown(KEY_0))
	{
		print("   ... 0 key is currently down\n");
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

