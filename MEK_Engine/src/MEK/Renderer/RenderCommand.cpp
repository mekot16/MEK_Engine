#include "mekpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace MEK {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
