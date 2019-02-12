#include "shader.h"
#include <GLEW/glew.h>
#include "../util/file.h"
#include "../globals.h"

#define U_LOCATION getUniformLocation(u_name)

Shader::Shader(const std::string& filepath)
	: 
	_id(glCreateProgram())
	, _filepath(filepath)
{
	std::string vsSource = load_text_file(filepath + ".vs");
	std::string fsSource = load_text_file(filepath + ".fs");

	if (vsSource == "")
	{
		ERR("Could not open vertex shader: " << filepath << ".vs");
	}
	if (fsSource == "")
	{
		ERR("Could not open fragment shader: " << filepath << ".fs");
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsC = vsSource.c_str();
	const char* fsC = fsSource.c_str();

	glShaderSource(vertexShader, 1, &vsC, NULL);
	glShaderSource(fragmentShader, 1, &fsC, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);

	glLinkProgram(_id);
	glValidateProgram(_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(_id);
}

void Shader::bind() const
{
	glUseProgram(_id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform1f(const std::string& u_name, float v0)
{
	glUniform1f(U_LOCATION, v0);
}

void Shader::setUniform2f(const std::string& u_name, float v0, float v1)
{
	glUniform2f(U_LOCATION, v0, v1);
}

void Shader::setUniform3f(const std::string& u_name, float v0, float v1, float v2)
{
	glUniform3f(U_LOCATION, v0, v1, v2);
}

void Shader::setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3)
{
	glUniform4f(U_LOCATION, v0, v1, v2, v3);
}

void Shader::setUniform1i(const std::string& u_name, int v0)
{
	glUniform1i(U_LOCATION, v0);
}

int Shader::getUniformLocation(const std::string& u_name)
{
	if (_uniformLocations.find(u_name) != _uniformLocations.end())
	{
		return _uniformLocations[u_name];
	}
	int location = glGetUniformLocation(_id, u_name.c_str());
	if (location == -1)
	{
		WARN("Could not find uniform: " << u_name);
	}
	_uniformLocations[u_name] = location;
	return location;
}