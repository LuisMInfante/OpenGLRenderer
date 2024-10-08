#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f), m_Direction(glm::vec3(0.0f, -1.0f, 0.0f))
{
}

DirectionalLight::DirectionalLight(const glm::vec3& color, const GLfloat diffuseIntensity, const glm::vec3& direction)
	: Light(color, diffuseIntensity), m_Direction(direction)
{
}