#include "VertexBufferLayout.h"
#include "GL/glew.h"

VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0)
{

}

template <typename T>
void VertexBufferLayout::Push(GLint count)
{
	static_assert(false);
}

template <>
void VertexBufferLayout::Push<float>(GLint count)
{
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::Push<unsigned int>(GLint count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::Push<unsigned char>(GLint count)
{
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

