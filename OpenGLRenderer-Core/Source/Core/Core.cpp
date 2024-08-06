#include "Core.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


namespace Core 
{
	void PrintOpenGLVersion()
	{
		std::cout << glGetString(GL_VERSION) << "\n";
	}
	
	/* Declare Window Pointer */
	GLFWwindow* window = nullptr;
	GLuint VAO;

	/* Setup GLFW and GLEW */
	bool Setup()
	{
		/* Initialize GLFW */
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW\n";
			return false;
		}

		/* Use GLFW Version 4.4 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		/* Use the OpenGL Core Profile */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Forward Compatibility */
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		/* Create a window and its OpenGL context */
		window = glfwCreateWindow(800, 600, "OpenGLRenderer", nullptr, nullptr);

		if (!window)
		{
			std::cout << "Failed to create window\n";
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Initialize GLEW */
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW\n";
			glfwTerminate();
			return false;
		}

		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
		glViewport(0, 0, bufferWidth, bufferHeight);

		return true;
	}

	/* Terminate GLFW */
	void Exit()
	{
		glfwTerminate();
	}

	VertexArray CreateTriangle()
	{
		/* Vertex Data */
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		/* Vertex Array Object */
		VertexArray VAO;

		/* Vertex Buffer Object */
		VertexBuffer VBO(vertices, sizeof(vertices));

		/* Format Vertex Data */
		VertexBufferLayout layout;
		layout.Push<float>(3);
		VAO.BindBuffer(VBO, layout);

		/* Index Buffer */
		//IndexBuffer IBO(indices, sizeof(indices) / sizeof(indices[0]));

		/* Unbind */
		VBO.Unbind();
		VAO.Unbind();

		return VAO;
	}

	GLuint CompileShader(GLenum type, const std::string& source)
	{
		/* Create and Compile Shader */
		GLuint id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Error Handling
		int compileStatus;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
		if (!compileStatus)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); // length of log

			std::vector<char> message(length);
			glGetShaderInfoLog(id, length, &length, message.data()); // returns the log

			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
			std::cout << message.data() << "\n";

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint program = glCreateProgram();

		if (!program)
		{
			std::cout << "Failed to create shader program\n";
			return 0;
		}

		GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		/* Attach Shaders to Program */
		glAttachShader(program, vs);
		glAttachShader(program, fs);

		/* Link Program */
		glLinkProgram(program);

		/* Error Handling */
		int linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) 
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> message(length);
			glGetProgramInfoLog(program, length, &length, message.data());

			std::cout << "Failed to link shader program\n";
			std::cout << message.data() << "\n";

			glDeleteProgram(program);
			return 0;
		}

		/* Validate Program */
		glValidateProgram(program);

		/* Error Handling */
		int validateStatus;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &validateStatus);
		if (validateStatus == GL_FALSE) 
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> message(length);
			glGetProgramInfoLog(program, length, &length, message.data());

			std::cout << "Failed to validate shader program\n";
			std::cout << message.data() << "\n";

			glDeleteProgram(program);
			return 0;
		}

		/* Detach Shaders for Deletions */
		glDetachShader(program, vs);
		glDetachShader(program, fs);

		/* Delete Shaders */
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	Core::ShaderProgramSource ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, 
			VERTEX = 0, 
			FRAGMENT = 1
		};
		
		ShaderType type = ShaderType::NONE;
		std::stringstream shaders[2];

		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				if (type != ShaderType::NONE)
					shaders[(int)type] << line << '\n';
			}
		}

		return { shaders[0].str(), shaders[1].str() };
	}

}