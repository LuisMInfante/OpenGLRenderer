#include "Core/Core.h"

#include <iostream>
#include <string.h>

int main()
{
    if (!Core::Setup())
    {
        return -1;
    }

    Core::PrintOpenGLVersion();

    GLuint VAO = Core::CreateTriangle();

    Core::ShaderProgramSource source = Core::ParseShader("Assets/Shaders/Basic.glsl");
	GLuint shader = Core::CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

    while (!glfwWindowShouldClose(Core::window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Core::window);
    }

	glDeleteProgram(shader);

    Core::Exit();
}