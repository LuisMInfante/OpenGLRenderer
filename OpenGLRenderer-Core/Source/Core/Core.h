#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray;

namespace Core 
{
	typedef struct ShaderProgramSource ShaderProgramSource;

	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();

	VertexArray CreateTriangle();
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	Core::ShaderProgramSource ParseShader(const std::string& filepath);

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};
}