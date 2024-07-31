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

	/* String Literals just for testing, will remove */
	// Vertex Shader
	const std::string vertexShader = R"(
	#version 460 core
	layout(location = 0) in vec4 pos;

	void main()
	{
		gl_Position = pos;
	}
	)";

	// Fragment Shader
	const std::string fragmentShader = R"(
	#version 460 core
	out vec4 color;

	void main()
	{
		color = vec4(0.0, 0.5, 1.0, 1.0);
	}
	)";

	GLuint shader = Core::CreateShader(vertexShader, fragmentShader);
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