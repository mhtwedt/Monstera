#pragma once

#ifdef MD_PLATFORM_WINDOWS
	#ifdef MD_BUILD_DLL
		#define MONSTERA_API _declspec(dllexport)
	#else
		#define MONSTERA_API _declspec(dllimport)
	#endif
#else
	#error only supports Windows
#endif

#ifdef MD_DEBUG
	#define MD_ENABLE_ASSERTS
#endif

#ifdef MD_ENABLE_ASSERTS
	#define MD_ASSERT(x, ...) {if (!(x)) {MD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MD_CORE_ASSERT(x, ...) {if (!(x)) {MD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MD_ASSERT(x, ...)
	#define MD_CORE_ASSERT(x, ...)
#endif



// Shift 1 by x places
// used EventCategory flags in Event.h
#define BIT(x) (1 << x)

#define MD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)