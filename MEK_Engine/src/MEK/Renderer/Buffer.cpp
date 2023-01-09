#include "mekpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace MEK {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	MEK_CORE_ASSERT(false, "RendererAPI::None is currently not supported for VertexBuffers!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		MEK_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	MEK_CORE_ASSERT(false, "RendererAPI::None is currently not supported for IndexBuffers!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}

		MEK_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
