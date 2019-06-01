#pragma once
#include <GLEW/glew.h>

class Buffer
{
	unsigned int _id;
public:
	Buffer();
	~Buffer();
	void push(const void* data, unsigned int size) const;
	void bind() const;
	void unbind() const;
};