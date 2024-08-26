#include "Mesh.h"

#include "VertexBufferLayout.h"

Mesh::Mesh()
	: m_VertexArray(), m_VertexBuffer(nullptr, 0), m_IndexBuffer(nullptr, 0)
{

}

Mesh::Mesh(const GLfloat* vertices, const unsigned int numVertices, const GLuint* indices,
	const unsigned int numIndices)
    : m_VertexArray(), m_VertexBuffer(vertices, sizeof(GLfloat) * numVertices), m_IndexBuffer(indices, numIndices)
{
    VertexBufferLayout layout;
    layout.Push<float>(3); // Position (x,y,z)
    layout.Push<float>(2); // Texture Coordinates (u,v)

    m_VertexArray.BindBuffer(m_VertexBuffer, layout);
    Unbind();
}

Mesh::~Mesh()
{
    ClearMesh();
}

void Mesh::CreateMesh(const GLfloat* vertices, const unsigned int numVertices, const GLuint* indices, const unsigned int numIndices)
{
    /* Vertex Array Object */
    m_VertexArray.Bind();

    /* Index Buffer Object */
    m_IndexBuffer = IndexBuffer(indices, numIndices);

    /* Vertex Buffer Object */
    m_VertexBuffer = VertexBuffer(vertices, sizeof(vertices[0]) * numVertices);

    /* Format Vertex Data */
    VertexBufferLayout layout;
    layout.Push<float>(3); // Position (x,y,z)
    layout.Push<float>(2); // Texture Coordinates (u,v)

    m_VertexArray.BindBuffer(m_VertexBuffer, layout);

    /* Unbind */
    Unbind();
}

void Mesh::Bind() const
{
	m_VertexArray.Bind();
	m_IndexBuffer.Bind();
}

void Mesh::Unbind() const
{
    m_VertexBuffer.Unbind();
    m_VertexArray.Unbind();
    m_IndexBuffer.Unbind();
}


void Mesh::ClearMesh()
{
    m_VertexBuffer.Unbind();
    m_VertexArray.Unbind();
    m_IndexBuffer.Unbind();
}
