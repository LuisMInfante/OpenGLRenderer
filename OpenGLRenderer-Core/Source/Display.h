#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/vec2.hpp>

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

	bool* GetKeyCodes() { return m_KeyCodes; }
	glm::vec2 GetMouseDelta();

private:

	/* Callbacks */
	void InitCallbacks();
	static void HandleInput(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
private:
	GLFWwindow* m_Window;
	GLint m_WindowWidth, m_WindowHeight;
	GLint m_FrameBufferWidth, m_FrameBufferHeight;

	/* Input Handling (May Create a separate class for input in the future */
	bool m_KeyCodes[1024];
	glm::vec2 m_LastMousePosition = { 0.0f, 0.0f};
	bool m_Moved = false;
};