#pragma once

#include "MEK/Renderer/Shader.h"
#include "glm/glm.hpp"


namespace MEK {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		// Parent class virtual functions
		void UploadMat4(const std::string& name, const glm::mat4& matrix);

		// Child class implementations
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};

}
