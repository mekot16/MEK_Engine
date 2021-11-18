#pragma once

#include "Core.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

#include "MEK/ImGui/ImGuiLayer.h"

#include "MEK/Renderer/Buffer.h"
#include "MEK/Renderer/Shader.h"
#include "MEK/Renderer/VertexArray.h"

namespace MEK {
	// singleton (only one Application for entire application)
	class MEK_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		// gets the instance of the singleton
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_TriangleShader;
		std::shared_ptr<VertexArray> m_TriangleVertexArray;

		std::shared_ptr<Shader> m_RectShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
