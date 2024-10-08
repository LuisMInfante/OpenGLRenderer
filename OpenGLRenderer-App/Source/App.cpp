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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Utility.h"
#include "Material.h"

constexpr int MaxPointLights = 3;

int main()
{
    Display mainWindow(1280, 720);
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

    /* Floor */
    GLfloat floorVertices[] = {
		// Position              // Texture Coordinates            // Normals
		-10.0f, 0.0f, -10.0f,    0.0f, 0.0f, /* Bottom-left */     0.0f, 1.0f, 0.0f,
		 10.0f, 0.0f, -10.0f,    10.0f, 0.0f, /* Bottom-right */   0.0f, 1.0f, 0.0f,
		 10.0f, 0.0f,  10.0f,    10.0f, 10.0f, /* Top-right */     0.0f, 1.0f, 0.0f,
		-10.0f, 0.0f,  10.0f,    0.0f, 10.0f, /* Top-left */       0.0f, 1.0f, 0.0f,
	};

    GLuint floorIndices[] = {
        0, 1, 2,
    	2, 3, 0
    };

    /* Calculate Normals */
    Utility::CalculateNormals(vertices, std::size(vertices), indices, std::size(indices), 8, 5);

    /* Mesh */
    Mesh mesh(vertices, std::size(vertices), indices, std::size(indices));
	Mesh floor(floorVertices, std::size(floorVertices), floorIndices, std::size(floorIndices));

    /* Shader */
    Shader shader("Assets/Shaders/BasicTextAndLight.glsl");
    shader.UseProgram();

    /* Texture */
    Texture texture("Assets/Textures/Metal.png");
    Texture floorTexture("Assets/Textures/Dirt.png");

    /* Light */
    Light light(glm::vec3(1.0f, 1.0f, 1.0f), 0.005f);
    DirectionalLight directionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.05f, glm::normalize(glm::vec3(2.0f, 3.0f, -4.0f)));
    PointLight pointLights[MaxPointLights];
    pointLights[0] = PointLight(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, glm::vec3(-9.0f, 2.0f, -9.0f), 15.0f, 1.0f, 0.09f, 0.032f); // Near bottom-left
    pointLights[1] = PointLight(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, glm::vec3(9.0f, 2.0f, -9.0f), 15.0f, 1.0f, 0.09f, 0.032f);  // Near bottom-right
    pointLights[2] = PointLight(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, glm::vec3(9.0f, 2.0f, 9.0f), 15.0f, 1.0f, 0.09f, 0.032f);   // Near top-right

    /* Material */
    Material metallicMaterial(1.0f, 32.0f);
    Material flatMaterial(0.3f, 2.0f);

    /* Testing Movement */
    float angle = 0.0f;

    GLfloat aspectRatio = mainWindow.GetFrameBufferWidth() / mainWindow.GetFrameBufferHeight();
    glm::mat4 projection(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));
    Camera camera(45.0f, 0.1f, 100.0f, aspectRatio);

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrameTime = 0.0f;
    while (!mainWindow.IsClosed())
    {
	    int pointLightCount = 3;
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

        /* Triangle mesh transformation */
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
        shader.SetUniformMatrix4f("u_Model", model);

        /* Camera */
        shader.SetUniformMatrix4f("u_Projection", camera.GetProjection());
        shader.SetUniformMatrix4f("u_View", camera.GetView());
        shader.SetUniform3f("u_CameraPosition", camera.GetPosition());

        /* Ambient Light */
        shader.SetUniform3f("u_Light.color", light.GetColor());
        shader.SetUniform1f("u_Light.intensity", light.GetIntensity());

        /* Directional Light */
        shader.SetUniform3f("u_DirectionalLight.direction", directionalLight.GetDirection());
        shader.SetUniform3f("u_DirectionalLight.color", directionalLight.GetColor());
        shader.SetUniform1f("u_DirectionalLight.intensity", directionalLight.GetIntensity());

        /* Specular Light */
        shader.SetUniform1f("u_Material.specularIntensity", metallicMaterial.GetSpecularIntensity());
        shader.SetUniform1f("u_Material.metallic", metallicMaterial.GetMetallic());

        /* Point Light */
        shader.SetUniform1i("u_PointLightCount", pointLightCount);

        for (int i = 0; i < pointLightCount; i++) 
        {
            std::string index = std::to_string(i);
            shader.SetUniform3f("u_PointLights[" + index + "].color", pointLights[i].GetColor());
            shader.SetUniform1f("u_PointLights[" + index + "].intensity", pointLights[i].GetIntensity());
            shader.SetUniform3f("u_PointLights[" + index + "].position", pointLights[i].GetPosition());
            shader.SetUniform1f("u_PointLights[" + index + "].range", pointLights[i].GetRange());
            shader.SetUniform1f("u_PointLights[" + index + "].constant", pointLights[i].GetConstant());
            shader.SetUniform1f("u_PointLights[" + index + "].linear", pointLights[i].GetLinear());
            shader.SetUniform1f("u_PointLights[" + index + "].quadratic", pointLights[i].GetQuadratic());
        }

        /* SpotLight */

        /* Triangle mesh */
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        Renderer::Draw(mesh, shader);

        /* Floor transformation */
        glm::mat4 floorModel(1.0f);
        floorModel = glm::translate(floorModel, glm::vec3(0.0f, -1.0f, -2.5f));
        shader.SetUniformMatrix4f("u_Model", floorModel);

        /* Floor Material */
        shader.SetUniform1f("u_Material.specularIntensity", flatMaterial.GetSpecularIntensity());
        shader.SetUniform1f("u_Material.metallic", flatMaterial.GetMetallic());

        /* Floor mesh */
        floorTexture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        Renderer::Draw(floor, shader);

        mainWindow.SwapBuffers();
    }
}