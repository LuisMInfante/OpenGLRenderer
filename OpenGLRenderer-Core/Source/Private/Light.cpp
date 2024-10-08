#include "Light.h"

Light::Light()
	: m_Color(glm::vec3(1.0f, 1.0f, 1.0f)), m_Intensity(1.0f)
{
}

Light::Light(const glm::vec3& color, const float intensity)
	: m_Color(color), m_Intensity(intensity)
{
}

Light::~Light()
{
}
