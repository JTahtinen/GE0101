#pragma once
#include <GLEW/glew.h>

class Buffer
{
	unsigned int _id;
public:
	Buffer();
	void push(const void* data, unsigned int size);
	void bind() const;
	void unbind() const;
};