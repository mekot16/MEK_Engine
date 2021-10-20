#pragma once

#include "MEK/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace MEK {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	
	private:
		GLFWwindow* m_WindowHandle;
	};

}
