#pragma once

#include <vector>

typedef unsigned int GLenum;
typedef int GLint;
typedef unsigned char GLboolean;
typedef float GLfloat;
typedef unsigned int GLuint;
typedef unsigned char GLubyte;
typedef int GLsizei;

#define GL_UNSIGNED_BYTE 0x1401
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406

struct VertexBufferElement
{
	GLenum type;
	GLint count;
	GLboolean normalized;

	static GLenum GetSizeOfType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);

		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);

		default:
			return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();

	template<typename T>
	void Push(GLint count);

	template<>
	void Push<float>(GLint count);

	template<>
	void Push<unsigned int>(GLint count);

	template<>
	void Push<unsigned char>(GLint count);

	inline GLsizei GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

private:
	std::vector<VertexBufferElement> m_Elements;
	GLsizei m_Stride;
};
