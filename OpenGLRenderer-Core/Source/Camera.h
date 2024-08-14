#pragma once

#include <glm/glm.hpp>

typedef float GLfloat;

class Camera
{
public:
	Camera(float verticalFOV, float nearClip, float farClip, float aspectRatio);
	~Camera();

	void OnUpdate();
	void ProcessInput(bool* keyCodes, GLfloat deltaTime);
	void ProcessMouseInput(glm::vec2 delta);

	const glm::mat4& GetProjection() const { return m_Projection; }
	const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
	const glm::mat4& GetView() const { return m_View; }
	const glm::mat4& GetInverseView() const { return m_InverseView; }

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetDirection() const { return m_ForwardDirection; }
private:
	void RecalculateProjection();
	void RecalculateView();
private:
	float m_VerticalFOV = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;
	float m_AspectRatio = 0.0f;

	glm::mat4 m_Projection{ 1.0f };
	glm::mat4 m_View{ 1.0f };
	glm::mat4 m_InverseProjection{ 1.0f };
	glm::mat4 m_InverseView{ 1.0f };

	glm::vec3 m_Position { 0.0f, 0.0f, 5.0f };
	glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_CameraUp;
	glm::vec3 m_RightDirection;
	glm::vec3 m_WorldUp{ 0.0f, 1.0f, 0.0f };

	GLfloat m_Yaw = -90.0f;
	GLfloat m_Pitch = 0.0f;

	GLfloat m_MovementSpeed = 5.0f;
	GLfloat m_RotationSpeed = 0.3f;
	GLfloat m_MouseSensitivity = 0.002f;
	GLfloat m_Zoom;

	glm::vec2 m_LastMousePosition { 0.0f, 0.0f};
	bool m_Moved = false;
};