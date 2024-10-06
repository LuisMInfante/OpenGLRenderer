#include "Texture.h"
#include "stb_image.h"

#include <iostream>

Texture::Texture()
	:m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BitDepth(0)
{

}

Texture::Texture(const std::string& filepath)
	:m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BitDepth(0)
{
	Load(filepath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);

	m_RendererID = 0;
	m_FilePath = "";
	m_LocalBuffer = nullptr;
	m_Width = 0;
	m_Height = 0;
	m_BitDepth = 0;
}

void Texture::Bind(unsigned int textureUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BitDepth, 4);

	if(!m_LocalBuffer)
	{
		std::cout << "Failed to load texture: " << filepath << '\n';
		return;
	}

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}