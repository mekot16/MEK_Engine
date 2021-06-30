#include "mekpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace MEK {

	// For Core and Client
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init()
	{
		// Core
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("MEK");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Client
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}