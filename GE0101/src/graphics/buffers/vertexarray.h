#pragma once
#include "buffer.h"
#include "bufferlayout.h"
#include <vector>
#include <string>

class VertexArray
{
	std::string				_name{ "" };
	unsigned int			_id;
	unsigned int			_numAttributes;
	std::vector<Buffer*>	_buffers;
public:
	VertexArray(const std::string& name);
	~VertexArray();
	void push(Buffer* buffer, const BufferLayout& layout);
	void bind() const;
	void unbind() const;
	inline const std::string& getName() const { return _name; }
	static VertexArray* loadVertexArray(const std::string& filepath);
};