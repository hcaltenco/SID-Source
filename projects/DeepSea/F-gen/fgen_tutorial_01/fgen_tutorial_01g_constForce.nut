//-------------------------------------------------------------
// fgen_tutorial.nut
//
// Squirrel script for F-Gen Tutorial 01
//-------------------------------------------------------------


// create a keyboard listener
gKeyInput <- inputlistener();


// setup event timing
gScriptTime <- timekeeper();	// setup time checker
gLoopRecoilTimer <- 0.0;		// timer to use for looping a recoil effect (initially set to zero)


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

// variable to store which type of recoil effect to use
gEffectType <- 1;	// 0 = no effect, 1 = simple recoil, 2 = looping recoil... init to 1


// creating a seperate Falcon effect stack for the control box
gControlBoxStack <- effectstack("control", 1.0);

// registering a control box effect
gControlBoxEffectID <- registereffect("ControlBox");
gControlBox <- null;	// variable to store the control box in


// create a seperate effects stack for "movement" forces
gMovementStack <- effectstack("movement", 1.0);

// create a constant effect type
gConstantEffectID <- registereffect("Constant");

// create the paramenters for a constant effect for use as a movement force
gMovementEffectParameters <- effectparameters(gConstantEffectID, gMovementStack);
gMovementForce <- null;


//-------------------------------------------------------------
// activate or deactivate the effects stacks
//-------------------------------------------------------------
function ConnectOrDisconnectStacks (deviceHandle, bConnect)
{
	// unlocking the device list on stacks
	gEffectsStack.setdevicelock(false);
	gControlBoxStack.setdevicelock(false);
	gMovementStack.setdevicelock(false);

	if (bConnect == true)
	{	// add the device to the stacks, input slot 0
		gEffectsStack.adddevice(deviceHandle, 0);
		gControlBoxStack.adddevice(deviceHandle, 0);
		gMovementStack.adddevice(deviceHandle, 0);
	}
	else
	{	// remove the device from the stacks, input slot 0
		gEffectsStack.removedevice(deviceHandle, 0);
		gControlBoxStack.removedevice(deviceHandle, 0);
		gMovementStack.removedevice(deviceHandle, 0);
	}

	// lock the device list on the stacks
	gEffectsStack.setdevicelock(true);
	gControlBoxStack.setdevicelock(true);
	gMovementStack.setdevicelock(true);

	if (bConnect == true)
	{	// connect the stacks to the device for output
		deviceconnectstack(deviceHandle, gEffectsStack);
		deviceconnectstack(deviceHandle, gControlBoxStack);
		deviceconnectstack(deviceHandle, gMovementStack);
	}
	else
	{	// disconnect the stacks from the device
		devicedisconnectstack(deviceHandle, gEffectsStack);
		devicedisconnectstack(deviceHandle, gControlBoxStack);
		devicedisconnectstack(deviceHandle, gMovementStack);
	}
}


//-------------------------------------------------------------
// Initialize this script
// Called once when this script is first loaded
//-------------------------------------------------------------
function HapticsInitialize (registryConfigHandle)
{
	print("Initialize Script\n");

	// launch the control box
	gControlBox = controlbox(effectparameters("_DefaultControlBox", gControlBoxStack), gControlBoxStack);
	if (gControlBox != null)
	{
		setinputeffect(gControlBox);
	}
}


//-------------------------------------------------------------
// Activate this script
// Called whenever this script becomes active (such as after
// returning to the application this script is attached to
// after switching to another window)
//-------------------------------------------------------------
function HapticsActivated (deviceHandle)
{
	// activate the effects stacks
	ConnectOrDisconnectStacks(deviceHandle, true);

	// launch the movement force
	gMovementForce = constantforce(gMovementEffectParameters, gMovementStack);

	print("Script Activated\n");
}


//-------------------------------------------------------------
// Run this script
// Called repeatedly while this acript is active
//-------------------------------------------------------------
function HapticsThink (deviceHandle)
{
	// update the time checker
	gScriptTime.update();

	// grab the time (in seconds) since the last call to HapticsThink
	local elapsedTime = gScriptTime.elapsedseconds();

	if (devicewasbuttonjustpressed(deviceHandle, FALCON_LOGO))
	{
		print("   ...Falcon LOGO button was just pressed\n");

		if (gEffectType == 1)
		{	// firing a single recoil

			// launch the simple recoil effect
			gSimpleRecoil.fire();
		}
	}
	else if (devicewasbuttonjustreleased(deviceHandle, FALCON_LOGO))
	{
		print("   ...Falcon LOGO button was just released\n");
	}

	if (devicebuttonisdown(deviceHandle, FALCON_LOGO))
	{
		print("   ... Falcon LOGO button is currently down\n");

		if (gEffectType == 2)
		{	// firing a looping recoil

			// count down to next time to fire off a recoil
			gLoopRecoilTimer -= elapsedTime;	// subtract elasped time from the timer
			if (gLoopRecoilTimer <= 0.0)
			{	// time to fire off another recoil
				gSimpleRecoil.fire();

				// reset timer... fire off a recoil every tenth of a second
				gLoopRecoilTimer += 0.1;	// increase timer by a tenth of a second
			}
		}
	}

	// update the keyboard listener before checking keyboard values
	gKeyInput.update();

	if (gKeyInput.wasinputjustpressed(KEY_0))
	{
		print("   ... select no recoil\n");

		// set effect type to no recoil
		gEffectType = 0;
	}
	else if (gKeyInput.wasinputjustpressed(KEY_1))
	{
		print("   ... select simple recoil\n");

		// set effect type to single recoil
		gEffectType = 1;
	}
	else if (gKeyInput.wasinputjustpressed(KEY_2))
	{
		print("   ... select looping recoil\n");

		// set effect type to looping recoil
		gEffectType = 2;
	}

	// now adjust the movement effect based on button presses
	local moveX = 0;
	local moveY = 0;
	local moveZ = 0;
	local steps = 3;

	if (gKeyInput.isinputdown(KEY_A))
	{
		moveX -= steps;
	}

	if (gKeyInput.isinputdown(KEY_D))
	{
		moveX += steps;
	}

	if (gKeyInput.isinputdown(KEY_S))
	{
		moveY -= steps;
	}

	if (gKeyInput.isinputdown(KEY_W))
	{
		moveY += steps;
	}

	if (gKeyInput.isinputdown(KEY_E))
	{
		moveZ -= steps;
	}

	if (gKeyInput.isinputdown(KEY_Z))
	{
		moveZ += steps;
	}

	gMovementForce.setforce(moveX, moveY, moveZ);
}


//-------------------------------------------------------------
// Deactivate this script
// called whenever this script stops being active (such as if
// you switch to another window)
//-------------------------------------------------------------
function HapticsDeactivated (deviceHandle)
{
	// remove the movement force
	gMovementForce.dispose();
	gMovementForce = null;

	// deactivate the effects stacks
	ConnectOrDisconnectStacks(deviceHandle, false);

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

