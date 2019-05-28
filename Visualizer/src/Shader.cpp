#include <iostream>
#include <sstream>
#include <fstream>

#include "GL/glew.h"
#include "Shader.h"
#include "CheckGLErrors.h"

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) : m_RendererID(0) {
	m_RendererID = CreateShader(ParseShader(vertexFilePath), ParseShader(fragmentFilePath));
}

//Shader::~Shader(){
//	std::cout << "Shader destructor called" << std::endl;
//	GLCall(glDeleteProgram(m_RendererID));
//}

std::string Shader::ParseShader(const std::string& filePath)
{
	std::ifstream inputFile(filePath);
	if (!inputFile.good()) {
		std::cout << "Failed to load shader file " << filePath << std::endl;
	}
	return std::string(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shader)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* source = shader.c_str();
	GLCall(glShaderSource(id, 1, &source, 0));
	GLCall(glCompileShader(id));

	int status;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
	if (status != GL_TRUE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		int len;
		GLCall(glGetShaderInfoLog(id, length, &len, message));
		std::cout << "Shader compilation failed for " << (type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER" : "GL_FRAGMENT_SHADER\n") << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDetachShader(program, vs));
	GLCall(glDeleteShader(fs));
	GLCall(glDetachShader(program, fs));

	return program;
}

void Shader::Bind() const{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const{
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;

	return location;
}

void Shader::SetUniform1i(const std::string& name, int value){
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value){
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 value) {
	GLCall(glUniform3fv(GetUniformLocation(name), 1, &value[0]));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix){
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
