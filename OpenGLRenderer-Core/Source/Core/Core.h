#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

typedef struct GLFWwindow GLFWwindow;
typedef struct Buffers Buffers;

struct Buffers
{
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
};

namespace Core 
{
	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();

	Buffers CreateTriangle();
}