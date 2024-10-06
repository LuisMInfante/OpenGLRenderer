#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();

private:
	glm::vec3 m_Position;
	GLfloat m_Range;
	GLfloat m_Constant;
	GLfloat m_Linear;
	GLfloat m_Quadratic;
};