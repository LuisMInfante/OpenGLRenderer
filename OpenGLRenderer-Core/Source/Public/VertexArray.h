#pragma once

class VertexBuffer;
class VertexBufferLayout;

typedef unsigned int GLuint;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

	GLuint GetRendererID() const { return m_RendererID; }
private:
	unsigned int m_RendererID;
};