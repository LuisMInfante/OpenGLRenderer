#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

namespace Core 
{
	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();

	GLuint CreateTriangle();
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
}