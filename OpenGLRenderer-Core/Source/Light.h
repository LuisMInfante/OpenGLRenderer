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
	Light(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& direction);
	Light(const glm::vec3& color, GLfloat ambientIntensity, const glm::vec3& direction, GLfloat diffuseIntensity);

	Light(const glm::vec3& position, const glm::vec3& color, GLfloat intensity);

	~Light();

	void ActivateLight(Shader& shader) const;

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetAmbientColor() const { return m_AmbientColor; }
	const glm::vec3& GetDiffuseColor() const { return m_DiffuseColor; }
	float GetAmbientIntensity() const { return m_AmbientIntensity; }
	glm::vec3 GetDirection() const { return m_Direction; }
	float GetDiffuseIntensity() const { return m_DiffuseIntensity; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	void SetAmbientColor(const glm::vec3& color) { m_AmbientColor = color; }
	void SetDiffuseColor(const glm::vec3& color) { m_DiffuseColor = color; }
	void SetAmbientIntensity(GLfloat intensity) { m_AmbientIntensity = intensity; }
	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	void SetDiffuseIntensity(GLfloat intensity) { m_DiffuseIntensity = intensity; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_AmbientColor;
	GLfloat m_AmbientIntensity;

	glm::vec3 m_DiffuseColor;
	GLfloat m_DiffuseIntensity;
	glm::vec3 m_Direction;

	GLuint m_RendererID;
};