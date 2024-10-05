#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Shader.h"

class Light
{
public:
	Light();

	/* Ambient Light */
	Light(const glm::vec3& color, GLfloat intensity);

	/* Directional Light */
	Light(const glm::vec3& color, GLfloat ambientIntensity, const glm::vec3& direction, GLfloat diffuseIntensity);

	Light(const glm::vec3& position, const glm::vec3& color, GLfloat intensity);

	~Light();

	void ActivateLight(Shader& shader) const;

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetColor() const { return m_Color; }
	float GetAmbientIntensity() const { return m_AmbientIntensity; }
	glm::vec3 GetDirection() const { return m_Direction; }
	float GetDiffuseIntensity() const { return m_DiffuseIntensity; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetAmbientIntensity(GLfloat intensity) { m_AmbientIntensity = intensity; }
	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	void SetDiffuseIntensity(GLfloat intensity) { m_DiffuseIntensity = intensity; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	GLfloat m_AmbientIntensity;
	glm::vec3 m_Direction;
	GLfloat m_DiffuseIntensity;
	GLuint m_RendererID;
};