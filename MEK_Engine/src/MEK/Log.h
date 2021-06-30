#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace MEK {

	class MEK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define MEK_CORE_TRACE(...)   ::MEK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MEK_CORE_INFO(...)    ::MEK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MEK_CORE_WARN(...)    ::MEK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MEK_CORE_ERROR(...)   ::MEK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MEK_CORE_FATAL(...)   ::MEK::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MEK_TRACE(...)        ::MEK::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MEK_INFO(...)         ::MEK::Log::GetClientLogger()->info(__VA_ARGS__)
#define MEK_WARN(...)         ::MEK::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MEK_ERROR(...)        ::MEK::Log::GetClientLogger()->error(__VA_ARGS__)
#define MEK_FATAL(...)        ::MEK::Log::GetClientLogger()->fatal(__VA_ARGS__)
