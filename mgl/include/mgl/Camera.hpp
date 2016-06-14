#pragma once

#include <vector>

#include <GL/glew.h>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mgl
{
	class Camera
	{
	public:
		static constexpr float defaultYaw{-90.f};
		static constexpr float defaultPitch{0.f};
		static constexpr float defaultSpeed{3.f};
		static constexpr float defaultSensitivity{0.25f};
		static constexpr float defaultZoom{45.f};

		Camera();
		Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		glm::mat4 getViewMatrix();

	private:
		void updateVectors();

	private:
		// Camera attributes
		glm::vec3 m_Position{0.f, 0.f, 0.f};
		glm::vec3 m_Front{0.f, 0.f, 0.f};
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp{0.f, 1.f, 0.f};

		// Euler angles
		float m_Yaw{defaultYaw};
		float m_Pitch{defaultPitch};

		// Camera options
		float m_MovementSpeed{defaultSpeed};
		float m_MouseSensitivity{defaultSensitivity};
		float m_Zoom{defaultZoom};
	};
}