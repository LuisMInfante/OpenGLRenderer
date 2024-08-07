#pragma once

typedef struct GLFWwindow GLFWwindow;
class VertexArray;

namespace Core 
{
	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();

	VertexArray CreateTriangle();
}