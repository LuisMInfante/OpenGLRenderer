#pragma once

//#include "GL/glew.h"

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
	static void Clear();

	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	static void Draw(const VertexArray& va, const Shader& shader);

};