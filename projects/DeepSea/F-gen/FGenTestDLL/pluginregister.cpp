

#include "stdafx.h"
#include "SQTestDLL.h"


// script calls this function to register the dll.
// use it to register your type(s) global(s) and any other variables you wish to push into the script.
SCRIPT_LIBRARY_EXPORT_ENTRY("sqtestdll")
{
	// register any globals (if any) automatically 
	SQAutoRegisterGlobals(v);

	return SQ_OK;
}