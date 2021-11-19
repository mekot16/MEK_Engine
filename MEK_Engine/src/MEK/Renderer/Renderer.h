#pragma once

#include "RenderCommand.h"

namespace MEK {

	class Renderer
	{
	public:
		static void BeginScene(); // TODO: add scene parameters
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}
