#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat specularIntensity, GLfloat metallic);
	~Material();

	GLfloat GetSpecularIntensity() const { return m_SpecularIntensity; }
	GLfloat GetMetallic() const { return m_Metallic; }

private:
	GLfloat m_SpecularIntensity;
	GLfloat m_Metallic;

};