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

		// Messing a bit with ImGui, delete this at some point
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("I want..."))
			{
				if (ImGui::MenuItem("to break free")) MEK_INFO("I want to BREAK free");
				if (ImGui::MenuItem("to ride my bicycle")) MEK_INFO("I want to ride my bike");
				if (ImGui::MenuItem("it all")) MEK_INFO("And I want it now");
				if (ImGui::MenuItem("to make a supersonic man out of you")) MEK_INFO("Having a good time, having a ball");
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		ImGui::Begin("Control Panel");
		ImGui::ColorEdit4("What's your favorite color?", m_favColor);
		ImGui::End();

		ImGui::Begin("Filters");
		ImGui::TextColored(ImVec4(1,0,1,1), "Pick your filters");
		ImGui::BeginChild("Scrolling");

		int length = sizeof(m_filters) / sizeof(m_filters[0]);
		for (int i = 0; i < length; i++)
		{
			ImGui::Checkbox(m_filters[i].label.c_str(), &m_filters[i].is_checked);
		}
		ImGui::EndChild();
		ImGui::End();

		ImGui::Begin("Roll");
		if (ImGui::Button("Do a barrel roll!"))
			MEK_INFO("Doing a kick flip");
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

private:
	// For messing with ImGui, delete these when I delete those
	float m_favColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	struct filterTest {
		std::string label = "";
		bool is_checked = 0;
	};
	filterTest m_filters[3] = {
		{"Coffee", 0},
		{"Pool", 1},
		{"Bad Words", 1}
	};
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
