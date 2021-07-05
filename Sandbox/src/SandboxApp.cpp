#include <MEK_Engine.h>

class ExampleLayer : public MEK::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//MEK_INFO("ExampleLayer::Update");
	}

	void OnEvent(MEK::Event& event) override
	{
		MEK_TRACE("{0}", event);
	}
};

class Sandbox : public MEK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new MEK::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

MEK::Application* MEK::CreateApplication()
{
	return new Sandbox();
}
