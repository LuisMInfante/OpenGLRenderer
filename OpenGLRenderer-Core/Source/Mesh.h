#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Renderer;
class Shader;

typedef int GLsizei;
typedef float GLfloat;
typedef unsigned int GLuint;

class Mesh
{
public:
	Mesh();
	Mesh(const GLfloat* vertices, const unsigned int numVertices, const GLuint* indices, const unsigned int numIndices);
	~Mesh();

	void CreateMesh(const GLfloat* vertices, const unsigned int numVertices, const GLuint* indices, const unsigned int numIndices);
	void Bind() const;
	void Unbind() const;
	void ClearMesh();

	const VertexArray& GetVertexArray() const { return m_VertexArray; }
	const VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }
	const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; }
	unsigned int GetIndexCount() const { return m_IndexBuffer.GetCount();  }

private:
	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
};