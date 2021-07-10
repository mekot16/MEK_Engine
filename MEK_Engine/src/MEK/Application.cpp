#include "mekpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace MEK {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MEK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// this is binding the OnEvent function defined in Application to be
		// run as the callback function when an event happens in the window
		m_Window->SetEventCallback(MEK_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MEK_BIND_EVENT_FN(Application::OnWindowClose));

		// Uncomment to log events
		//MEK_CORE_TRACE("{0}", e);

		// start from top-most layer and iterate downward
		// call OnEvent for each layer passed, until event is handled
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
		
			// call OnUpdate for all Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// call OnUpdate for Window
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}