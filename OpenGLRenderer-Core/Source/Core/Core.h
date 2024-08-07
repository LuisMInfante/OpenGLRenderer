#pragma once

class GLFWwindow;
class VertexArray;

namespace Core 
{
	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();

	VertexArray CreateTriangle();
}