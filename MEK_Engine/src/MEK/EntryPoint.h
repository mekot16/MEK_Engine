#pragma once

#ifdef MEK_PLATFORM_WINDOWS

// created somewhere else
extern MEK::Application* MEK::CreateApplication();

int main(int argc, char** argv)
{
	auto app = MEK::CreateApplication();
	app->Run();
	delete app;
}

#endif