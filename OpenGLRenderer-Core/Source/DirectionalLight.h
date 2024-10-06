#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& direction);

	const glm::vec3& GetDiffuseColor() const { return m_DiffuseColor; }
	glm::vec3 GetDirection() const { return m_Direction; }
	float GetDiffuseIntensity() const { return m_DiffuseIntensity; }

	void SetDiffuseColor(const glm::vec3& color) { m_DiffuseColor = color; }
	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	void SetDiffuseIntensity(GLfloat intensity) { m_DiffuseIntensity = intensity; }

private:
	glm::vec3 m_DiffuseColor;
	GLfloat m_DiffuseIntensity;
	glm::vec3 m_Direction;

};