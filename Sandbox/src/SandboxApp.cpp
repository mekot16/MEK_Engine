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
		MEK_TRACE("Ex Layer: {0}", event);
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

// This function implementation is required!
// This allows us to create our own Application child class
// called Sandbox and pass it into the MEK Engine Core
// When CreateApplication is called in the MEK Engine Core,
// it will now be our Sandbox Application class that's running.
MEK::Application* MEK::CreateApplication()
{
	return new Sandbox();
}
