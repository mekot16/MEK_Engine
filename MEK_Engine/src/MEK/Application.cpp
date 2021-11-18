#include "mekpch.h"
#include "Application.h"

#include "Input.h"

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

		// don't like using 'new' (see unique_ptr and shared_ptr)
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Drawing a triangle on screen
		// Vertex Array
		m_TriangleVertexArray.reset(VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,		0.8f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.7f, 0.7f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f,		0.2f, 0.7f, 0.9f, 1.0f
		};

		// Vertex Buffer
		std::shared_ptr<VertexBuffer> triangleVB;
		triangleVB.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"}
		};
		triangleVB->SetLayout(layout);

		// important to do this after layout is created and set
		m_TriangleVertexArray->AddVertexBuffer(triangleVB);

		// Index Buffer
		uint32_t triangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> triangleIB;
		triangleIB.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVertexArray->SetIndexBuffer(triangleIB);


		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_TriangleShader.reset(Shader::Create(vertexSrc, fragmentSrc));


		// Drawing a square too //
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		// define how the buffer is laid out
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		// this handles the vertex array 
		// important to do this after layout is created and set
		m_SquareVA->AddVertexBuffer(squareVB);

		// Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		// Shader for rectangle
		std::string vertexRectSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentRectSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_RectShader.reset(Shader::Create(vertexRectSrc, fragmentRectSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
		
			m_RectShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_TriangleShader->Bind();
			m_TriangleVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_TriangleVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			// call OnUpdate for all Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// TODO: this rendering will be done on the render thread
			// call OnImGuiRender for all Layers between ImGui's Begin and End
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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