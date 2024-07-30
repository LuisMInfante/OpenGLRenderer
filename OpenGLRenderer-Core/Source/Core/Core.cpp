#include "Core.h"

#include <iostream>

namespace Core {

	void PrintOpenGLVersion()
	{
		std::cout << glGetString(GL_VERSION) << "\n";
	}
	
	/* Declare Window Pointer */
	GLFWwindow* window = nullptr;

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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

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

}