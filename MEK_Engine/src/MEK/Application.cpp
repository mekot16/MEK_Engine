#include "Application.h"

#include "MEK/Events/ApplicationEvent.h"
#include "MEK/Events/MouseEvent.h"
#include "MEK/Log.h"

namespace MEK {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			MEK_TRACE(e);
		}

		if (e.IsInCategory(EventCategoryMouse))
		{
			MEK_TRACE(e);
		}
		
		MouseButtonPressedEvent e2(10);
		if (e2.IsInCategory(EventCategoryMouse) && e2.IsInCategory(EventCategoryInput))
		{
			MEK_INFO(e2.ToString());
		}

		while (true);
	}

}