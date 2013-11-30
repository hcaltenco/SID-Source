:: HugBag Programs Startup tool by H. Caltenco, Certec, LTH
@echo off

:: show a welcome message
echo\
echo Fluid DAC with Sound Batch Program Starter
echo ---------------------------------
echo Hector Caltenco (hector.caltenco@certec.lth.se)
echo\
echo (Do not close this window!)
echo\

:: start the kinect server
echo Starting Kinect TUIO Server Application: KinectCoreVision.exe
echo\

cd kinectCV_mssdk_dualTuio
start KinectCoreVision.exe

:: start the fluid client
echo Starting Processing TUIO Client Application: MSAFluidTuioDemo.exe
echo\

cd ..
cd MSAFluidTuio_Full_3334
start MSAFluidTuioDemo.exe

:: start the Max/Msp client
echo Starting Max Standalone TUIO Cient Application: HugBagControls.exe
echo\

cd ..
cd MAXControls
start MaxControls.exe

:: start the Ableton Live Project
echo Starting Ableton Live Project: hugbagdemokosmos.als
echo\

cd ..
cd "hugbagdemowhale Project"
start hugbagdemowhale.als

:end