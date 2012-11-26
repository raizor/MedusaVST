#pragma once

#include "Utils/console.h"

#if ENABLE_CONSOLE
	#define DebugPrint(txt) printf("%s", txt);
	#define DebugPrintLine(txt) printf("%s\n", txt);
#else
	#define DebugPrint(txt) 
	#define DebugPrintLine(txt) 
#endif
