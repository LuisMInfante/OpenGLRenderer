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

	/* Lock the cursor to the window */
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

glm::vec2 Display::GetMousePosition()
{
	double xPos, yPos;
	glfwGetCursorPos(m_Window, &xPos, &yPos);

	return { (float)xPos, (float)yPos };
}

glm::vec2 Display::GetMouseDelta()
{
	glm::vec2 delta = m_MouseDelta;
	m_MouseDelta = glm::vec2(0.0f);
	return delta;
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
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	if (display->m_FirstMouse)
	{
		display->m_LastMousePosition = glm::vec2((GLfloat)xPos, (GLfloat)yPos);
		display->m_FirstMouse = false;
	}

	display->m_MouseDelta = { (GLfloat)xPos - display->m_LastMousePosition.x, display->m_LastMousePosition.y - (GLfloat)yPos };
	display->m_LastMousePosition = { (float)xPos, (float)yPos };
}
