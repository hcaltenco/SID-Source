// SQTestDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h>
#include <tchar.h>
#include "SQTestDLL.h"
#include "Serial.h"

//==============================================================
// Error Functions
//==============================================================

LONG lLastError = ERROR_SUCCESS;

int ShowError (LONG lError, LPCTSTR lptszMessage)
{
	// Generate a message text
	TCHAR tszMessage[256];
	wsprintf(tszMessage,_T("%s\n(error code %d)"), lptszMessage, lError);

	// Display message-box and return with an error-code
	::MessageBox(0,tszMessage,_T("Error Message"), MB_ICONSTOP|MB_OK);
	return 1;
}

//==============================================================
// Serial Port Functions
//==============================================================

CSerial serial;

int SerialSetup (CSerial::EBaudrate baud, CSerial::EDataBits data, CSerial::EParity par, CSerial::EStopBits stop, CSerial::EHandshake handshake)
{
// Attempt to open the serial port (COM1)
    lLastError = serial.Open(_T("COM1"),0,0,false);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to open COM-port"));

    // Setup the serial port (9600,N81) using hardware handshaking
    lLastError = serial.Setup(baud, data, par, stop);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port setting"));

	// Setup handshaking
    lLastError = serial.SetupHandshaking(handshake);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port handshaking"));

	// if no error
	return 0;
}

int SerialWrite (char* str)
{
	// The serial port is now ready and we can send/receive data. If
	// the following call blocks, then the other side doesn't support
	// hardware handshaking.
    lLastError = serial.Write(str);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to send data"));

	// if no error
	return 0;
}

//==============================================================
// debug logging functions
//==============================================================

//------------------------------------------------------------------------------
// open debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_open (HSQUIRRELVM v)
{
	//gpDebugLogFile = fopen("testScriptLOG.txt", "w");
	SerialSetup(CSerial::EBaud9600,CSerial::EData8,CSerial::EParNone,CSerial::EStop1,CSerial::EHandshakeHardware);
	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_open);


//------------------------------------------------------------------------------
// close debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_close (HSQUIRRELVM v)
{
	if (serial.IsOpen())
	{
		//fclose(gpDebugLogFile);
		serial.Close();
	}

	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_close);


//------------------------------------------------------------------------------
// print a sting to the debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_print (HSQUIRRELVM v, const SQChar *pTxt)
{
	if (serial.IsOpen())
	{
		wchar_t *inTxt = (wchar_t *)pTxt;
		//fwprintf_s(gpDebugLogFile, inTxt);
		char dst[100];
		sprintf_s(dst, 100, "%ls", inTxt);
		SerialWrite(dst);
	}

	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_print);


//------------------------------------------------------------------------------
// print an int to the debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_printInt (HSQUIRRELVM v, SQInteger val)
{
	if (serial.IsOpen())
	{
		int inVal = (int)val;
		//fprintf(gpDebugLogFile, "%d", inVal);
		char dst[32];
		sprintf_s(dst, 32, "%d", inVal);
		SerialWrite(dst);
	}

	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_printInt);


//------------------------------------------------------------------------------
// print a float to the debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_printFloat (HSQUIRRELVM v, SQFloat val)
{
	if (serial.IsOpen())
	{
		float inVal = (float)val;
		//fprintf(gpDebugLogFile, "%f", inVal);
		char dst[32];
		sprintf_s(dst, 32, "%f", inVal);
		SerialWrite(dst);
	}

	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_printFloat);


//------------------------------------------------------------------------------
// print a float vector to the debug log file
//------------------------------------------------------------------------------
SQRESULT SQ_debugLog_printVector (HSQUIRRELVM v, SQFloat valX, SQFloat valY, SQFloat valZ)
{
	if (serial.IsOpen())
	{
		float inValX = (float)valX;
		float inValY = (float)valY;
		float inValZ = (float)valZ;
		//fprintf(gpDebugLogFile, "%f, %f, %f", inValX, inValY, inValZ);
		char dst[100];
		sprintf_s(dst, 100, "%f, %f, %f", inValX, inValY, inValZ);
		SerialWrite(dst);
	}

	return SQ_OK;
}

SQ_BIND_GLOBAL_METHOD(debugLog_printVector);


//------------------------------------------------------------------------------
// add two integers and return the result (just a quick example of how to 
// return a value to a squirrel script
//------------------------------------------------------------------------------
SQRESULT SQ_testAddInts (HSQUIRRELVM v, SQInteger int1, SQInteger int2)
{
	SQInteger outInt = int1 + int2;

	sq_pushinteger(v, outInt);		// return the value to the squirrel script

	// return one return value pushed
	return 1;
}

SQ_BIND_GLOBAL_METHOD(testAddInts);
