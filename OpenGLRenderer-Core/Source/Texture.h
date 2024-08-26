#pragma once

#include <GL/glew.h>

#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int textureUnit = 0) const;
	void Unbind() const;
	void Load(const std::string& filepath);

private:
	GLuint m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BitDepth;
};