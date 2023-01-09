#include "mekpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace MEK {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{ 
		m_SceneData->ViewProjectMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{ // TODO: will be implemented later
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadMat4("u_ViewProjection", m_SceneData->ViewProjectMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
