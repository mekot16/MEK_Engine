#pragma once

#include "Core.h"

namespace MEK {

	class MEK_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
