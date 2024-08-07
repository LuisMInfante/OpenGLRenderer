#include "Shader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>

#include "Renderer.h"

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::UseProgram() const
{
	glUseProgram(m_RendererID);
}

void Shader::UnuseProgram() const
{
	glUseProgram(0);
}

void Shader::DeleteProgram() const
{
	glDeleteProgram(m_RendererID);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
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

GLuint Shader::CompileShader(GLenum type, const std::string& source)
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

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

GLint Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.contains(name))
	{
		return m_UniformLocationCache[name];
	}

	GLint location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' does not exist\n";
	}

	m_UniformLocationCache[name] = location;

	return location;
}
