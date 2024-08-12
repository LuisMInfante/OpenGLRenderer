#include "Display.h"

#include <iostream>

Display::Display()
	: m_WindowWidth(800), m_WindowHeight(600)
{
	
}

Display::Display(GLint WindowWidth, GLint WindowHeight)
	: m_WindowWidth(WindowWidth), m_WindowHeight(WindowHeight)
{
	
}

Display::~Display()
{
	glfwTerminate();
}

bool Display::Init()
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
	m_Window = glfwCreateWindow(800, 600, "OpenGLRenderer", nullptr, nullptr);

	if (!m_Window)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	/* Initialize GLEW */
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW\n";
		glfwTerminate();
		return false;
	}

	glfwGetFramebufferSize(m_Window, &m_FrameBufferWidth, &m_FrameBufferHeight);
	glViewport(0, 0, m_FrameBufferWidth, m_FrameBufferHeight);

	return true;
}
