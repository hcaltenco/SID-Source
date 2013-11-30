:: HugBag Programs Startup tool by H. Caltenco, Certec, LTH
@echo off

:: show a welcome message
echo\
echo HugBag Batch Program Starter
echo ---------------------------------
echo Hector Caltenco (hector.caltenco@certec.lth.se)
echo\
echo (Do not close this window!)
echo\

:: start the kinect server
echo Starting Kinect TUIO Server Application: KinectCoreVision.exe
echo\

cd kinectCV_OpenNi_hec
start KinectCoreVision.exe
:: start the Max/Msp client
echo Starting Max Standalone TUIO Cient Application: HugBagControls.exe
echo\

cd ..
cd HugBagControls
start HugBagControls.exe

:: start the MIDI-Serial bridge
echo Starting MIDI-Serial bridge: hairless-midiserial.exe
echo\

cd ..
cd hairless-midiserial
start hairless-midiserial.exe

:: start the Ableton Live Project
echo Starting Ableton Live Project: hugbagdemokosmos.als
echo\

cd ..
cd "HugBagTUIO Project"
cd "hugbagdemowhale Project"
start hugbagdemowhale.als

:end