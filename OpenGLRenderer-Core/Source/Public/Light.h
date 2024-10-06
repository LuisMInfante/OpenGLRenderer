#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

/* Ambient Light */
class Light
{
public:
	Light();
	Light(const glm::vec3& color, GLfloat intensity);
	~Light();

	const glm::vec3& GetColor() const { return m_Color; }
	float GetIntensity() const { return m_Intensity; }

	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetIntensity(GLfloat intensity) { m_Intensity = intensity; }

private:
	glm::vec3 m_Color;
	GLfloat m_Intensity;
};