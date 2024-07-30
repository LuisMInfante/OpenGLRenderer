#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Core {

	void PrintOpenGLVersion();

	extern GLFWwindow* window;

	bool Setup();
	void Exit();
}