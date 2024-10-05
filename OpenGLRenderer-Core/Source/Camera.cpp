#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#include <iostream>

Camera::Camera(float verticalFOV, float nearClip, float farClip, float aspectRatio)
	: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip), m_AspectRatio(aspectRatio)
{
	m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	m_RightDirection = glm::normalize(glm::cross(m_ForwardDirection, m_WorldUp));
	m_CameraUp = glm::normalize(glm::cross(m_RightDirection, m_ForwardDirection));
	RecalculateProjection();
	RecalculateView();
	OnUpdate();
}

Camera::~Camera()
{
}

void Camera::OnUpdate()
{
	/* Using Euler Angles */
	m_ForwardDirection.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardDirection.y = sin(glm::radians(m_Pitch));
	m_ForwardDirection.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardDirection = glm::normalize(m_ForwardDirection);

	/* TODO: Implement Quaternions */

	m_RightDirection = glm::normalize(glm::cross(m_ForwardDirection, m_WorldUp));
	m_CameraUp = glm::normalize(glm::cross(m_RightDirection, m_ForwardDirection));
}

void Camera::ProcessInput(bool* keyCodes, GLfloat deltaTime)
{
	GLfloat velocity = m_MovementSpeed * deltaTime;

	if (keyCodes[GLFW_KEY_W])
	{
		m_Position += m_ForwardDirection * velocity;
		m_Moved = true;
	}

	if (keyCodes[GLFW_KEY_S])
	{
		m_Position -= m_ForwardDirection * velocity;
		m_Moved = true;
	}

	if (keyCodes[GLFW_KEY_A])
	{
		m_Position -= m_RightDirection * velocity;
		m_Moved = true;
	}

	if (keyCodes[GLFW_KEY_D])
	{
		m_Position += m_RightDirection * velocity;
		m_Moved = true;
	}

	if (keyCodes[GLFW_KEY_Q])
	{
		m_Position += m_CameraUp * velocity;
		m_Moved = true;
	}

	if (keyCodes[GLFW_KEY_E])
	{
		m_Position -= m_CameraUp * velocity;
		m_Moved = true;
	}

	if (m_Moved)
	{
		RecalculateView();
		m_Moved = false;
	}
}

void Camera::ProcessMouseInput(glm::vec2 delta)
{
	delta *= m_RotationSpeed;
	m_Yaw += delta.x;
	m_Pitch += delta.y;

	/* Clamp Pitch */
	m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

	RecalculateView();
	OnUpdate();
}

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspective(glm::radians(m_VerticalFOV), m_AspectRatio, m_NearClip, m_FarClip); // clip space
	m_InverseProjection = glm::inverse(m_Projection); // camera space
}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, m_WorldUp); // camera space
	m_InverseView = glm::inverse(m_View); // world space
}
