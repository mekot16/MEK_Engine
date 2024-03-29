#pragma once

#include <string>
#include "glm/glm.hpp"

namespace MEK {

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void UploadMat4(const std::string& name, const glm::mat4& matrix) = 0; // aka SetMat4
	};

}
