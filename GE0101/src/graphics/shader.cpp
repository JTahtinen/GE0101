#include "shader.h"
#include <GLEW/glew.h>
#include "../util/file.h"
#include "../globals.h"

#define U_LOCATION getUniformLocation(u_name)

Shader::Shader(const std::string& filepath, bool inclGeometryShader)
	: 
	_id(glCreateProgram())
	, _filepath(filepath)
{
	std::string vsSource = load_text_file(filepath + ".vs");
	std::string fsSource = load_text_file(filepath + ".fs");
	std::string gsSource;


	if (vsSource == "")
	{
		ERR("Could not open vertex shader: " << filepath << ".vs");
	}
	if (fsSource == "")
	{
		ERR("Could not open fragment shader: " << filepath << ".fs");
	}

	GLCALL(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GLCALL(unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	unsigned int geometryShader;

	const char* vsC = vsSource.c_str();
	const char* fsC = fsSource.c_str();
	const char* gsC;

	

	GLCALL(glShaderSource(vertexShader, 1, &vsC, NULL));
	GLCALL(glShaderSource(fragmentShader, 1, &fsC, NULL));

	GLCALL(glCompileShader(vertexShader));
	GLCALL(glCompileShader(fragmentShader));

	GLCALL(glAttachShader(_id, vertexShader));
	GLCALL(glAttachShader(_id, fragmentShader));

	if (inclGeometryShader)
	{
		gsSource = load_text_file(filepath + ".gs");
		if (gsSource == "")
		{
			ERR("Could not open geometry shader: " << filepath << ".gs");
		}
			gsC = gsSource.c_str();
			GLCALL(geometryShader = glCreateShader(GL_GEOMETRY_SHADER));
			GLCALL(glShaderSource(geometryShader, 1, &gsC, NULL));
			GLCALL(glCompileShader(geometryShader));
			GLCALL(glAttachShader(_id, geometryShader));
	}

	GLCALL(glLinkProgram(_id));
	GLCALL(glValidateProgram(_id));

	GLCALL(glDeleteShader(vertexShader));
	GLCALL(glDeleteShader(fragmentShader));
	if (inclGeometryShader)
	{
		GLCALL(glDeleteShader(geometryShader));
	}
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(_id));
}

void Shader::bind() const
{
	GLCALL(glUseProgram(_id));
}

void Shader::unbind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::setUniform1f(const std::string& u_name, float v0)
{
	GLCALL(glUniform1f(U_LOCATION, v0));
}

void Shader::setUniform2f(const std::string& u_name, float v0, float v1)
{
	GLCALL(glUniform2f(U_LOCATION, v0, v1));
}

void Shader::setUniform3f(const std::string& u_name, float v0, float v1, float v2)
{
	GLCALL(glUniform3f(U_LOCATION, v0, v1, v2));
}

void Shader::setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(U_LOCATION, v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& u_name, int v0)
{
	GLCALL(glUniform1i(U_LOCATION, v0));
}

int Shader::getUniformLocation(const std::string& u_name)
{
	if (_uniformLocations.find(u_name) != _uniformLocations.end())
	{
		return _uniformLocations[u_name];
	}
	GLCALL(int location = glGetUniformLocation(_id, u_name.c_str()));
	if (location == -1)
	{
		WARN("Could not find uniform: " << u_name << " from shader: " << _filepath);
	}
	_uniformLocations[u_name] = location;
	return location;
}