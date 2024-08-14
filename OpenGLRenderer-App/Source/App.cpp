#include "Core/Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Display.h"
#include "Camera.h"

int main()
{
    Display mainWindow(800, 600);
    if (!mainWindow.Init())
    {
        return -1;
    }
    Display::EnableSync();
    Display::PrintOpenGLVersion();

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

    /* Shader */
    Shader shader("Assets/Shaders/Basic.glsl");
    shader.UseProgram();

    /* Testing Movement */
    float angle = 0.0f;

    GLfloat aspectRatio = mainWindow.GetFrameBufferWidth() / mainWindow.GetFrameBufferHeight();
    glm::mat4 projection(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));
    Camera camera(45.0f, 0.1f, 100.0f, aspectRatio);

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrameTime = 0.0f;
    while (!mainWindow.IsClosed())
    {
        GLfloat currentFrameTime = (GLfloat)glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        Display::Update();

        camera.ProcessInput(mainWindow.GetKeyCodes(), deltaTime);
        camera.ProcessMouseInput(mainWindow.GetMouseDelta());

        // Rotate
        angle += 0.25f;
		if (angle > 360.0f)
		{
			angle = 0.0f;
		}

        Renderer::Clear();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

        shader.SetUniformMatrix4f("u_Model", model);
        shader.SetUniformMatrix4f("u_Projection", camera.GetProjection());
        shader.SetUniformMatrix4f("u_View", camera.GetView());

        Renderer::Draw(mesh, shader);

        mainWindow.SwapBuffers();
    }
}