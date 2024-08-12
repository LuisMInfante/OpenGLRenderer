#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "GL/glew.h"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh& mesh, const Shader& shader)
{
	mesh.Bind();
	shader.UseProgram();
	glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();
	shader.UseProgram();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader)
{
	va.Bind();
	shader.UseProgram();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
