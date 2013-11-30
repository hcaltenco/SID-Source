//******************************************************//
// Control Box wall key presses:  F-Gen Script			//
// 2011-07-11										    //
//******************************************************//



// key bindings
action <- regenum("action", "Actions",
						regvalue("Accelerate",		KEY_X,		"Throttle Up"),
						regvalue("Decelerate",		KEY_Z,		"Throttle Down"));

bindings <- regenumitem("bindings",
						"Game's Buttons", 
						"Set keys match to what the game uses", 
						action, 
						"Accelerate", 
						ui(UI_KEYBINDING));
	
binds					<- {};
binds.Accelerate		<- action.value(0);
binds.Decelerate		<- action.value(1);


							        //***********************************//
//**********************************// Force Effect Type Initialization  //******************************************//
							        //***********************************//

// initialize some effect and force related things.
EffectStacks <- { 
					CONTROL=	effectstack("control", 1.0)
				}
	
//effect id table
effectid <- {};
effectid.controlbox <- registereffect("ControlBox");

function ConnectStacks(deviceHandle)
{
	foreach(val in EffectStacks)
	{
		val.setdevicelock(false);
		val.adddevice(deviceHandle, 0);
		val.setdevicelock(true);
		deviceconnectstack(deviceHandle, val);
	}

}
function DisconnectStacks(deviceHandle)
{	
	foreach(val in EffectStacks)
	{
		val.setdevicelock(false);
		val.removedevice(deviceHandle, 0);
		val.setdevicelock(true);
		devicedisconnectstack(deviceHandle, val);
	}
}
controlStack <- EffectStacks.CONTROL;



							        //*************************************//
//**********************************//  Movement Controls with Control Box //******************************************//
							        //*************************************//

// Control box effect. ( uses default so cannot be constructed here, constructed in HapticsActivated )
CB			<- null;
		
sendAccelerate		<- inputsender(binds.Accelerate);
sendDecelerate		<- inputsender(binds.Decelerate);
							//sendkeys functions
							//send.isdown()
							//send.isup()
							//send.press()
							//send.release()
							//send.tap()
							//send.toggle()
class MovementControls {
	constructor()
	{
		sendAccelerate.release();
		sendDecelerate.release();
	}

	CBvel = vec3();
	inThreshold = -0.25;
	outThreshold = 0.25;
	inState = 0;
	outState = 0;

	function update()
	{
		CBvel = CB.getvelocity();//tells you how far you are pressing into the control box

		//Throttle Up Control
		if(CBvel.z < inThreshold)
		{
			if(inState == 0)
			{
				inState = 1;
				sendAccelerate.press();
				print("Press accelerate button \n");
			}
		}
		else
		{
			if(inState == 1)
			{
				inState = 0;
				sendAccelerate.release();
				print("Release accelerate button \n");
			}
		}

		//Throttle Down Control
		if(CBvel.z > outThreshold)
		{
			if(outState == 0)
			{
				outState = 1;
				sendDecelerate.press();
				print("Press decelerate button \n");
			}
		}
		else
		{
			if(outState == 1)
			{
				outState = 0;
				sendDecelerate.release();//Release decelerate button
				print("Release decelerate button \n");
			}
		}

		return(CBvel);
	}
 
};
movementControlsProcessor <- MovementControls();


							        //*************************************//
//**********************************//  Core Haptic Processing Functions   //****************************************//
							        //*************************************//
											
// inputlistener.
g_input <- null;
				
firstActivate <- false;
// Called when the tied profile is made active
function HapticsActivated(deviceHandle)
{
	if(!firstActivate)
	{
		firstActivate = true;

		// make our input listener
		g_input = inputlistener();

		// load the default effect parameter for control box. (this ties into manager settings)
		CB = controlbox(effectparameters("_DefaultControlBox", controlStack), controlStack);
		// bind this effect as the input emulating one.
		setinputeffect(CB);	
	}
	ConnectStacks(deviceHandle);
}

function HapticsThink(deviceHandle)
{
	//Input listener update
	g_input.update();

	//Handle driving input
	movementControlsProcessor.update();
}

// Called when the tied profile is made inactive
function HapticsDeactivated(deviceHandle)
{
	DisconnectStacks(deviceHandle);
}
 
// Called when the tied profile is about to be shutdown (Once)
function HapticsShutdown()
{
}
