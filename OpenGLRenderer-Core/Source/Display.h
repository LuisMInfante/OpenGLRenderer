#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <iostream>

typedef int GLint;
typedef struct GLFWwindow GLFWwindow;

class Display
{
public:
	Display();
	Display(GLint WindowWidth, GLint WindowHeight);
	~Display();

	static void PrintOpenGLVersion() { std::cout << glGetString(GL_VERSION) << "\n"; };

	bool Init();
	bool IsClosed() const { return glfwWindowShouldClose(m_Window); }
	void SwapBuffers() const { glfwSwapBuffers(m_Window); }
	static void Update() { glfwPollEvents(); }
	static void EnableSync() { glfwSwapInterval(1); }

	GLint GetWindowWidth() const { return m_WindowWidth; }
	GLint GetWindowHeight() const { return m_WindowHeight; }
	GLfloat GetFrameBufferWidth() const { return (GLfloat)m_FrameBufferWidth; }
	GLfloat GetFrameBufferHeight() const { return (GLfloat)m_FrameBufferHeight; }

private:
	GLFWwindow* m_Window;
	GLint m_WindowWidth, m_WindowHeight;
	GLint m_FrameBufferWidth, m_FrameBufferHeight;
};