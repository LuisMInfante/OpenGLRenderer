#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();
	~Material();

private:
	GLfloat specularIntensity;
	GLfloat metallic;

};