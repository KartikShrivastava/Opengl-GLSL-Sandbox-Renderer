#pragma once

#include <string>
#include <unordered_map>

#include "glm.hpp"

class Shader{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	std::string ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& shader);
	void CheckProgramStatus(GLuint programID);
	int GetUniformLocation(const std::string& name);

public:
	Shader();
	//Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	//~Shader();

	void Bind() const;
	void UnBind() const;

	void CreateShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3fv(const std::string& name, glm::vec3 value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);

	void CleanupData();
};