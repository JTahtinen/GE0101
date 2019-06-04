#pragma once
#include "buffer.h"
#include "bufferlayout.h"
#include <vector>
#include <string>

class VertexArray
{
	unsigned int			_id;
	unsigned int			_numAttributes;
	std::vector<Buffer*>	_buffers;
public:
	VertexArray();
	~VertexArray();
	void push(Buffer* buffer, const BufferLayout& layout);
	void bind() const;
	void unbind() const;
	static VertexArray* loadVertexArray(const std::string& filepath);
};