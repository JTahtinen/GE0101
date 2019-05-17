#pragma once

#include "../shader.h"
#include "../../defs.h"


class Renderer 
{
protected:
	Shader*			_shader;
public:
	virtual ~Renderer()
	{
		delete _shader;
	}
	virtual void flush() = 0;
	inline void setShader(Shader* shader) 
	{ 
		_shader = shader; 
		if (!_shader)
		{
			WARN("Could not set shader for renderer - nullptr exception");
		}
	}
};