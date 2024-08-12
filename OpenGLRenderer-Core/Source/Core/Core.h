#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

typedef struct GLFWwindow GLFWwindow;

namespace Core 
{
	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();
}