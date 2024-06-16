#pragma once
#include "Core.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "spdlog/fmt/ostr.h"
#pragma warning(pop)


namespace Monstera {


	class MONSTERA_API Log
	{

	public :
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log Macros
#define MD_CORE_TRACE(...)     ::Monstera::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MD_CORE_INFO(...)      ::Monstera::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MD_CORE_WARN(...)      ::Monstera::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MD_CORE_ERROR(...)     ::Monstera::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MD_CORE_FATAL(...)     ::Monstera::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log Macros
#define MD_TRACE(...)          ::Monstera::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MD_INFO(...)           ::Monstera::Log::GetClientLogger()->info(__VA_ARGS__)
#define MD_WARN(...)           ::Monstera::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MD_ERROR(...)          ::Monstera::Log::GetClientLogger()->error(__VA_ARGS__)
#define MD_FATAL(...)          ::Monstera::Log::GetClientLogger()->fatal(__VA_ARGS__)

// If distribution build (dist build), then these log macros can be nullified, and macros will not be used in the binary
// something like below
// #define MD_CORE_INFO = null