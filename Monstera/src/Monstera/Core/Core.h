#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define MD_PLATFORM_WINDOWS
#else
	/* Windows x86 */
	#error "x86 Builds are not supported!"
#endif

#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define MD_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define MD_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

	 /* We also have to check __ANDROID__ before __linux__
	  * since android is based on the linux kernel
	  * it has __linux__ defined */
	#elif defined(__ANDROID__)
		#define MD_PLATFORM_ANDROID
		#error "Android is not supported!"
	#elif defined(__linux__)
		#define MD_PLATFORM_LINUX
		#error "Linux is not supported!"
	#else
		/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

// DLL support
#ifdef MD_PLATFORM_WINDOWS
	#if MD_DYNAMIC_LINK
		#ifdef MD_BUILD_DLL
			#define MONSTERA_API __declspec(dllexport)
		#else
			#define MONSTERA_API __declspec(dllimport)
		#endif
	#else
		#define MONSTERA_API
#endif
#else
	#error Monstera only supports Windows!
#endif // End of DLL support


// TODO: Make this macro able to take in no arguments except condition
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

// #define MD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define MD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...); }

namespace Monstera {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	//Instead of std::make_shared, we can type in CreateRef... which is cleaner
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}