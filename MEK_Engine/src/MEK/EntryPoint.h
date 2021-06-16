#pragma once

#ifdef MEK_PLATFORM_WINDOWS

// created somewhere else
extern MEK::Application* MEK::CreateApplication();

int main(int argc, char** argv)
{
	MEK::Log::Init();
	MEK_CORE_WARN("Initialized Log!");
	int a = 5;
	MEK_INFO("HI! var={0}", a);

	auto app = MEK::CreateApplication();
	app->Run();
	delete app;
}

#endif