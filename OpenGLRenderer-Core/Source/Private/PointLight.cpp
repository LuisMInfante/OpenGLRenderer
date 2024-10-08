#include "PointLight.h"

PointLight::PointLight()
	: Light(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f), m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Range(0.0f), m_Constant(1.0f), m_Linear(0.0f), m_Quadratic(0.0f)
{
}

PointLight::PointLight(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& position, GLfloat range,
	GLfloat constant, GLfloat linear, GLfloat quadratic)
		: Light(color, diffuseIntensity), m_Position(position), m_Range(range), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
{
}