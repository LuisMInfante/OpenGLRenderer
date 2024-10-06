#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& direction);

	glm::vec3 GetDirection() const { return m_Direction; }

	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

private:
	glm::vec3 m_Direction;
};