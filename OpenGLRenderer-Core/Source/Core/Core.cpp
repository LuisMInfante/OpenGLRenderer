#include "Core.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

namespace Core 
{
	void PrintOpenGLVersion()
	{
		std::cout << glGetString(GL_VERSION) << "\n";
	}
	
	/* Declare Window Pointer */
	GLFWwindow* window = nullptr;
	GLuint VAO;

	/* Setup GLFW and GLEW */
	bool Setup()
	{
		/* Initialize GLFW */
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW\n";
			return false;
		}

		/* Use GLFW Version 4.4 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		/* Use the OpenGL Core Profile */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Forward Compatibility */
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		/* Create a window and its OpenGL context */
		window = glfwCreateWindow(800, 600, "OpenGLRenderer", nullptr, nullptr);

		if (!window)
		{
			std::cout << "Failed to create window\n";
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Initialize GLEW */
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW\n";
			glfwTerminate();
			return false;
		}

		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
		glViewport(0, 0, bufferWidth, bufferHeight);

		return true;
	}

	/* Terminate GLFW */
	void Exit()
	{
		glfwTerminate();
	}

	VertexArray CreateTriangle()
	{
		/* Vertex Data */
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		/* Vertex Array Object */
		VertexArray VAO;

		/* Vertex Buffer Object */
		VertexBuffer VBO(vertices, sizeof(vertices));

		/* Format Vertex Data */
		VertexBufferLayout layout;
		layout.Push<float>(3);
		VAO.BindBuffer(VBO, layout);

		/* Index Buffer */
		//IndexBuffer IBO(indices, sizeof(indices) / sizeof(indices[0]));

		/* Unbind */
		VBO.Unbind();
		VAO.Unbind();

		return VAO;
	}
}