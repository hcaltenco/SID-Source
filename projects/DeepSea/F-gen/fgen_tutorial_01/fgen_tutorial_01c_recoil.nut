//-------------------------------------------------------------
// fgen_tutorial.nut
//
// Squirrel script for F-Gen Tutorial 01
//-------------------------------------------------------------


// create a keyboard listener
gKeyInput <- inputlistener();


// creating default Falcon effect stack
gEffectsStack <- effectstack("effects", 1.0);

// registering envelope effect.
gEnvelopeEffectID <- registereffect("Envelope");

// create a simple recoil effect and set its parameters.
gSimpleRecoil <- effectparameters(gEnvelopeEffectID, gEffectsStack);	// create the effect
gSimpleRecoil.setvarelement("force", 0, 0); // 0 newtons right-wards
gSimpleRecoil.setvarelement("force", 1, 0);	// 0 newtons upwards
gSimpleRecoil.setvarelement("force", 2, 20); // 20 newtons backwards
gSimpleRecoil.setvar("attack", 30); // ramp up to the force over 30 milliseconds.
gSimpleRecoil.setvar("hold", 0); // no hold time once at maximum force
gSimpleRecoil.setvar("decay", 0); // no fall off time at end of effect


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
	// unlocking the device list on stack
	gEffectsStack.setdevicelock(false);

	// adding the device to the stack input slot 0
	gEffectsStack.adddevice(deviceHandle, 0);

	// locking the device list on stack
	gEffectsStack.setdevicelock(true);

	// connect the stack to the device for output
	deviceconnectstack(deviceHandle, gEffectsStack);

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

		// launch the simple recoil effect
		gSimpleRecoil.fire();
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
	// unlocking the device list on stack
	gEffectsStack.setdevicelock(false);

	// removing the device from the stack input slot 0
	gEffectsStack.removedevice(deviceHandle, 0);

	// locking the device list on stack
	gEffectsStack.setdevicelock(true);

	// disconnecting the stack output from the device
	devicedisconnectstack(deviceHandle, gEffectsStack);

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
