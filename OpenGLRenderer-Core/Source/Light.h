#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Shader.h"

class Light
{
public:
	Light();
	Light(const glm::vec3& color, GLfloat intensity);
	Light(const glm::vec3& position, const glm::vec3& color, GLfloat intensity);

	~Light();

	void ActivateLight(Shader& shader) const;

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetColor() const { return m_Color; }
	float GetIntensity() const { return m_Intensity; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetIntensity(GLfloat intensity) { m_Intensity = intensity; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	GLfloat m_Intensity;
	GLuint m_RendererID;
};