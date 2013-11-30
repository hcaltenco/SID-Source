:: HugBag Programs Startup tool by H. Caltenco, Certec, LTH
@echo off

:: show a welcome message
echo\
echo Fluid DAC Batch Program Starter
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

:end