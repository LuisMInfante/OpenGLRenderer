#include "Core/Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
//#include "Renderer.h"

int main()
{
    if (!Core::Setup())
    {
        return -1;
    }
    
    glfwSwapInterval(1);

    Core::PrintOpenGLVersion();

    VertexArray VAO = Core::CreateTriangle();

    Shader shader("Assets/Shaders/Basic.glsl");
    shader.UseProgram();
    shader.SetUniform4f("u_Color", 0.0f, 0.5f, 1.0f, 1.0f);
    //shader.UnuseProgram();

    while (!glfwWindowShouldClose(Core::window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Core::window);
    }

    shader.DeleteProgram();

    Core::Exit();
}