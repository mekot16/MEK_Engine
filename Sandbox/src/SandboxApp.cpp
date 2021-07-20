#include <MEK_Engine.h>

#include "imgui/imgui.h"

class ExampleLayer : public MEK::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	virtual void OnUpdate() override
	{
		//MEK_INFO("ExampleLayer::Update");
		if (MEK::Input::IsKeyPressed(MEK_KEY_SPACE))
			MEK_TRACE("Space bar is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	virtual void OnEvent(MEK::Event& event) override
	{
		if (event.GetEventType() == MEK::EventType::KeyPressed)
		{
			MEK::KeyPressedEvent& e = (MEK::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MEK_KEY_TAB)
				MEK_TRACE("Tab key is pressed (event)!");
			MEK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public MEK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
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
