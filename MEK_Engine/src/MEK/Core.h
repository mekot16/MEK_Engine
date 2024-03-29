#pragma once

#ifdef MEK_PLATFORM_WINDOWS
	#if MEK_DYNAMIC_LINK // this isn't defined anywhere, it's just hiding the old dynamic link definitions
			#ifdef MEK_BUILD_DLL
				#define MEK_API __declspec(dllexport)
			#else
				#define MEK_API __declspec(dllimport)
			#endif
	#else
		#define MEK_API
	#endif
#else
	#error MEK only supports Windows!
#endif

#ifdef MEK_DEBUG
	#define MEK_ENABLE_ASSERTS
#endif

#ifdef MEK_ENABLE_ASSERTS
	#define MEK_ASSERT(x, ...) { if(!(x)) { MEK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MEK_CORE_ASSERT(x, ...) { if(!(x)) { MEK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MEK_ASSERT(x, ...)
	#define MEK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MEK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
