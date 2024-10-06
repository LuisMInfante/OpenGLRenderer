#include "Light.h"

Light::Light()
	: m_AmbientColor(glm::vec3(1.0f, 1.0f, 1.0f)), m_AmbientIntensity(1.0f)
{
}

Light::Light(const glm::vec3& color, float intensity)
	: m_AmbientColor(color), m_AmbientIntensity(intensity)
{
}

Light::~Light()
{
}
