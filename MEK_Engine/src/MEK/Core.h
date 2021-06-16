#pragma once

#ifdef MEK_PLATFORM_WINDOWS
	#ifdef MEK_BUILD_DLL
		#define MEK_API __declspec(dllexport)
	#else
		#define MEK_API __declspec(dllimport)
	#endif
#else
	#error MEK only supports Windows!
#endif