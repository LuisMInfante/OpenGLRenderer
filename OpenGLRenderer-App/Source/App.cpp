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
#include "Texture.h"
#include "Light.h"
#include "Utility.h"

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
        // Position              // Texture Coordinates            // Normals
        -1.0f, -1.0f,  1.0f,     0.0f, 0.0f, /* Bottom-left */     0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,     1.0f, 0.0f, /* Bottom-right */    0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,     1.0f, 1.0f, /* Top-right */       0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,     0.0f, 1.0f, /* Top-left */        0.0f, 0.0f, 0.0f,
         0.0f,  1.0f,  0.0f,     0.5f, 0.5f,  /* Apex */           0.0f, 0.0f, 0.0f,
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

    /* Calculate Normals */
    Utility::CalculateNormals(vertices, std::size(vertices), indices, std::size(indices), 8, 5);

    /* Mesh */
    Mesh mesh(vertices, std::size(vertices), indices, std::size(indices));

    /* Shader */
    Shader shader("Assets/Shaders/BasicTextAndLight.glsl");
    shader.UseProgram();

    /* Texture */
    Texture texture("Assets/Textures/Brick.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    /* Light */
    Light light(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, glm::vec3(2.0f, 2.0f, -4.0f), 1.0f);

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

        /* Ambient Light */
        shader.SetUniform3f("u_Light.color", light.GetColor());
        shader.SetUniform1f("u_Light.ambientIntensity", light.GetAmbientIntensity());

        /* Directional Light */
        shader.SetUniform3f("u_Light.direction", light.GetDirection());
        shader.SetUniform1f("u_Light.diffuseIntensity", light.GetDiffuseIntensity());

        Renderer::Draw(mesh, shader);

        mainWindow.SwapBuffers();
    }
}