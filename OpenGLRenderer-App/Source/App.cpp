#include "Core/Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

int main()
{
    if (!Core::Setup())
    {
        return -1;
    }

    glfwSwapInterval(1);

    Core::PrintOpenGLVersion();

    Renderer renderer;

    /* Vertex Data */
    GLfloat vertices[] = {
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f, 1.0f, 0.0f
    };

    /* Index Data */
    GLuint indices[] = {
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,
        0, 1, 2,
        2, 3, 0
    };

    /* Mesh */
    Mesh mesh(vertices, std::size(vertices), indices, std::size(indices));

    Shader shader("Assets/Shaders/Basic.glsl");
    shader.UseProgram();
    //shader.SetUniform4f("u_Color", 0.0f, 0.5f, 1.0f, 1.0f);

    //shader.UnuseProgram();


    /* Testing Movement */
    bool direction = true;
    float offset = 0.0f;
    float increment = 0.005f;
    float maxOffset = 0.5f;

    float angle = 0.0f;

    bool growth = true;
    float size = 1.0f;
    float maxSize = 2.0f;
    float minSize = 0.1f;

    glEnable(GL_DEPTH_TEST);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLfloat aspectRatio = (GLfloat)mode->width / (GLfloat)mode->height;
    glm::mat4 projection(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));

    while (!glfwWindowShouldClose(Core::window))
    {
        glfwPollEvents();

        // translate
        if (direction)
		{
			offset += increment;
		}
		else
		{
			offset -= increment;
		}

        // Reverse direction
        if (offset >= maxOffset || offset <= -maxOffset)
        {
        	direction = !direction;
        }

        // Rotate
        angle += 0.25f;
		if (angle > 360.0f)
		{
			angle = 0.0f;
		}

        // Scale
        if (growth)
        {
	        size += 0.01f;
		}
		else
		{
			size -= 0.01f;
        }

        if (size >= maxSize || size <= minSize)
		{
			growth = !growth;
		}

        Renderer::Clear();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

        shader.SetUniformMatrix4f("u_Model", model);
        shader.SetUniformMatrix4f("u_Projection", projection);

        Renderer::Draw(mesh, shader);

        glfwSwapBuffers(Core::window);
    }

    shader.DeleteProgram();

    Core::Exit();
}