#include "mekpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace MEK {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		MEK_CORE_ASSERT(false, "RendererAPI::None is currently not supported for IndexBuffers!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		MEK_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
