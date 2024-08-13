#include "Display.h"

#include <iostream>

Display::Display()
	: m_Window(nullptr), m_WindowWidth(800), m_WindowHeight(600), m_FrameBufferWidth(0), m_FrameBufferHeight(0), m_KeyCodes()
{
	
}

Display::Display(GLint WindowWidth, GLint WindowHeight)
	: m_Window(nullptr), m_WindowWidth(WindowWidth), m_WindowHeight(WindowHeight), m_FrameBufferWidth(0), m_FrameBufferHeight(0), m_KeyCodes()
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

	glEnable(GL_DEPTH_TEST);

	glfwGetFramebufferSize(m_Window, &m_FrameBufferWidth, &m_FrameBufferHeight);
	glViewport(0, 0, m_FrameBufferWidth, m_FrameBufferHeight);

	/* Set the window user pointer */
	glfwSetWindowUserPointer(m_Window, this);

	/* Initialize Callbacks */
	InitCallbacks();

	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

glm::vec2 Display::GetMouseDelta()
{
	double xPos, yPos;
	glfwGetCursorPos(m_Window, &xPos, &yPos);

	std::cout << "Delta: " << (float)xPos - m_LastMousePosition.x << ", " << m_LastMousePosition.y - (float)yPos << "\n";
	return { (float)xPos - m_LastMousePosition.x, m_LastMousePosition.y - (float)yPos };
}

void Display::InitCallbacks()
{
	glfwSetKeyCallback(m_Window, HandleInput);
	glfwSetCursorPosCallback(m_Window, HandleMouse);
}

void Display::HandleInput(GLFWwindow* window, int key, int code, int action, int mode)
{
	Display* display = static_cast<Display*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//glfwSetInputMode(display->m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			display->m_KeyCodes[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			display->m_KeyCodes[key] = false;
		}
	}

}

void Display::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Display* display = static_cast<Display*>(glfwGetWindowUserPointer(window));

	//display->GetMouseDelta();
	display->m_LastMousePosition.x = (float)xPos;
	display->m_LastMousePosition.y = (float)yPos;
}
