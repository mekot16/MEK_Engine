#include "mekpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace MEK {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		MEK_CORE_ASSERT(false, "RendererAPI::None is currently not supported for Shaders!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		MEK_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}


}
