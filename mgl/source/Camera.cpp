#include <mgl/Camera.hpp>

namespace mgl
{
	Camera::Camera()
	{
		updateVectors();	
	}

	Camera::Camera(const glm::vec3& position, const gm::vec3& up, float yaw, float pitch)
		: m_Position{position},
		  m_Up{up},
		  m_Yaw{yaw}, m_Pitch{pitch}
	{
		updateVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: m_Position{posX, posY, posZ},
		  m_Up{upX, upY, upZ},
		  m_Yaw{yaw}, m_Pitch{pitch}
	{
		updateVectors();
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::updateVectors()
	{
		// calculate new front vector
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		// re-calculate front and up vector
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cros(m_Right, m_Front));
	}
}