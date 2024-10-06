#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: m_DiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f)), m_DiffuseIntensity(1.0f), m_Direction(glm::vec3(0.0f, -1.0f, 0.0f))
{
}

DirectionalLight::DirectionalLight(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& direction)
	: m_DiffuseColor(color), m_DiffuseIntensity(diffuseIntensity), m_Direction(direction)
{
}

