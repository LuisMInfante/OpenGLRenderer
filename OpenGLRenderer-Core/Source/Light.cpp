#include "Light.h"

Light::Light()
	: m_Position(glm::vec3(0.0f, 0.0f, 0.0f)), m_Color(glm::vec3(1.0f, 1.0f, 1.0f)), m_Intensity(1.0f)
{
}

Light::Light(const glm::vec3& color, float intensity)
	: m_Color(color), m_Intensity(intensity)
{
}

Light::Light(const glm::vec3& position, const glm::vec3& color, GLfloat intensity)
	: m_Position(position), m_Color(color), m_Intensity(intensity)
{
}

Light::~Light()
{
}

void Light::ActivateLight(Shader& shader) const
{
	shader.SetUniform3f("u_Light.position", m_Position);
	shader.SetUniform3f("u_Light.color", m_Color);
	shader.SetUniform1f("u_Light.intensity", m_Intensity);
}
