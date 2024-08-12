#pragma once

typedef unsigned int GLuint;

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetRendererID() const { return m_RendererID; }
private:
		unsigned int m_RendererID;
};