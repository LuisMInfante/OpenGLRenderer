#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLint;

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void UseProgram() const;
	void UnuseProgram() const;
	void DeleteProgram() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, glm::vec3 value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix);

	unsigned int GetID() const { return m_RendererID; }

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	GLint GetUniformLocation(const std::string& name);
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
};