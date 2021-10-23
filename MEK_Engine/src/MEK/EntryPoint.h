#pragma once

#ifdef MEK_PLATFORM_WINDOWS

// This function is implemented in the client app that's using MEK Engine
// The client must create a child class of Application (ex: Sandbox:Application),
// then CreateApplication is implemented to return a new instance of that child class.
// That child class is then Run.
extern MEK::Application* MEK::CreateApplication();

int main(int argc, char** argv)
{
	MEK::Log::Init();
	MEK_CORE_WARN("Initialized Log!");

	auto app = MEK::CreateApplication();
	app->Run();
	delete app;
}

#endif