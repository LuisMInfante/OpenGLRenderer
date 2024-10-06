#pragma once

class VertexArray;
class IndexBuffer;
class Shader;
class Mesh;

class Renderer
{
public:
	static void Clear();

	static void Draw(const Mesh& mesh, const Shader& shader);
	
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	static void Draw(const VertexArray& va, const Shader& shader);
};