#include "Material.h"

Material::Material()
	: m_SpecularIntensity(0.0f), m_Metallic(0.0f)
{
}

Material::Material(GLfloat specularIntensity, GLfloat metallic)
	: m_SpecularIntensity(specularIntensity), m_Metallic(metallic)
{
}

Material::~Material()
{
}
