#pragma once

// debug shit idk, MS tells me i should do this
// https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library

#ifdef _WIN32

#	define _CRTDBG_MAP_ALLOC
#	include <cstdlib>
#	include <crtdbg.h>

#	ifdef _DEBUG
#		define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#	else
#		define DBG_NEW new
#	endif

#else
// for wsl
#	define _CrtDumpMemoryLeaks() (0)
#	define DBG_NEW new

#endif