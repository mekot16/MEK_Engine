#include "mekpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace MEK {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MEK_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// initialize glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MEK_CORE_ASSERT(status, "Failed to initialize Glad!");

		MEK_CORE_INFO("----- OpenGL Info ------------------------");
		MEK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		MEK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		MEK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		MEK_CORE_INFO("------------------------------------------\n");

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}