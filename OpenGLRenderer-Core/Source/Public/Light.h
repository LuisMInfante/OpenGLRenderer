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

	const glm::vec3& GetAmbientColor() const { return m_AmbientColor; }
	float GetAmbientIntensity() const { return m_AmbientIntensity; }

	void SetAmbientColor(const glm::vec3& color) { m_AmbientColor = color; }
	void SetAmbientIntensity(GLfloat intensity) { m_AmbientIntensity = intensity; }

private:
	glm::vec3 m_AmbientColor;
	GLfloat m_AmbientIntensity;
};