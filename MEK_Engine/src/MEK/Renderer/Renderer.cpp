#include "mekpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace MEK {

	void Renderer::BeginScene()
	{ // TODO: will be implemented later
	}

	void Renderer::EndScene()
	{ // TODO: will be implemented later
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
