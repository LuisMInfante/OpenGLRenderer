#include "Core/Core.h"
#include <iostream>

int main()
{
    if (!Core::Setup())
    {
        return -1;
    }

    Core::PrintOpenGLVersion();

    while (!glfwWindowShouldClose(Core::window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(Core::window);
    }

    Core::Exit();
	
}