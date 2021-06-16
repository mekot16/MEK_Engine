#include <MEK_Engine.h>

class Sandbox : public MEK::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

MEK::Application* MEK::CreateApplication()
{
	return new Sandbox();
}
