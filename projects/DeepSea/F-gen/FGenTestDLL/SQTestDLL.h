#ifndef NVNT_SQ_TEST_DLL_H
#define NVNT_SQ_TEST_DLL_H

#include "squirrel.h"


//Error functions
int ShowError (LONG lError, LPCTSTR lptszMessage);

// serial port functions
//int SerialSetup (CSerial::EBaudrate baud, CSerial::EDataBits data, CSerial::EParity par, CSerial::EStopBits stop, CSerial::EHandshake handshake);
//int SerialWrite (char* str);

// debug log functions
SQ_GLOBAL_METHOD(debugLog_open, 0);
SQ_GLOBAL_METHOD(debugLog_close, 0);
SQ_GLOBAL_METHOD(debugLog_print, 1, const SQChar *);
SQ_GLOBAL_METHOD(debugLog_printInt, 1, SQInteger);
SQ_GLOBAL_METHOD(debugLog_printFloat, 1, SQFloat);
SQ_GLOBAL_METHOD(debugLog_printVector, 3, SQFloat, SQFloat, SQFloat);

// test function for returning a value
SQ_GLOBAL_METHOD(testAddInts, 2, SQInteger, SQInteger);

// debug log file handle
//FILE	*gpDebugLogFile = NULL;

#endif