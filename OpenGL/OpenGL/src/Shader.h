#pragma once
#include <string>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{


private:
	unsigned int m_rendererID;
	std::string m_filePath;
	std::unordered_map <std::string, int> m_uniformLocationCache;


	int getUniformLocation(const std::string& name);

	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource parseShader(const std::string& filePath);

public:
	Shader(const std::string& filepath);
	~Shader();
	void bind() const;  //GL use program
	void unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMatrix4f(const std::string& name, const glm::mat4& matrix);

};

