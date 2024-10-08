#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const glm::vec3& color, GLfloat diffuseIntensity, const glm::vec3& position, GLfloat range, GLfloat constant, GLfloat linear, GLfloat quadratic);

	glm::vec3 GetPosition() const { return m_Position; }
	GLfloat GetRange() const { return m_Range; }
	GLfloat GetConstant() const { return m_Constant; }
	GLfloat GetLinear() const { return m_Linear; }
	GLfloat GetQuadratic() const { return m_Quadratic; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	void SetRange(const GLfloat range) { m_Range = range; }
	void SetConstant(const GLfloat constant) { m_Constant = constant; }
	void SetLinear(const GLfloat linear) { m_Linear = linear; }
	void SetQuadratic(const GLfloat quadratic) { m_Quadratic = quadratic; }

private:
	glm::vec3 m_Position;
	GLfloat m_Range;
	GLfloat m_Constant;
	GLfloat m_Linear;
	GLfloat m_Quadratic;
};

/*
	* Common Light Properties
	* Taken from https://wiki.ogre3d.org

	Range   Constant   Linear   Quadratic
	3250,   1.0,       0.0014,  0.000007
	600,    1.0,       0.007,	0.0002
	325,    1.0,       0.014,	0.0007
	200,    1.0,       0.022,	0.0019
	160,    1.0,       0.027,	0.0028
	100,    1.0,	   0.045,	0.0075
	65,     1.0,	   0.07,	0.017
	50,     1.0,	   0.09,	0.032
	32,     1.0,	   0.14,	0.07
	20,     1.0,	   0.22,	0.20
	13,     1.0,	   0.35,	0.44
	7,      1.0,	   0.7,		1.8
*/