#pragma once
#include <string>
#include <unordered_map>

class Shader
{
	unsigned int		_id;
	const std::string	_filepath;
	std::unordered_map < std::string, int> _uniformLocations;
public:
	Shader(const std::string& filepath, bool inclGeometryShader = false);
	~Shader();
	void bind() const;
	void unbind() const;
	void setUniform1f(const std::string& u_name, float v0);
	void setUniform2f(const std::string& u_name, float v0, float v1);
	void setUniform3f(const std::string& u_name, float v0, float v1, float v2);
	void setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3);

	void setUniform1i(const std::string& u_name, int v0);
private:
	int getUniformLocation(const std::string& u_name);
};