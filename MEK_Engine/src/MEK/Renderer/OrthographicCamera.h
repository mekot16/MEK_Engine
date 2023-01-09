#pragma once

#include <glm/glm.hpp>

namespace MEK {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		//// Notes section ////
		// TRS (translation, rotation, scale), multiply in this order
		// proj * view * model * vertexPos
		// proj & view on camera, model is on object, vertexPos is on mesh
		//////////////////////
		glm::mat4 m_ProjectionMatrix; // field of view and aspect ratio (perspetive matrix?) glm::perspective glm::perspectiveFov
		glm::mat4 m_ViewMatrix; // inverse of the transformation matrix of the camera
		glm::mat4 m_ViewProjectionMatrix; // cache projection matrix * view matrix

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f; // z rotation since this is an orthographic camera

	};

}
