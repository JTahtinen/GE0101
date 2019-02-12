#pragma once
#include <GLEW/glew.h>
#include <vector>

struct BufferElement
{
	GLenum type;
	GLint count;
	GLboolean normalized;
};

class BufferLayout
{
	std::vector<BufferElement>	_elements;
	GLsizei						_stride;
public:
	BufferLayout();
	template <typename T>
	void push(GLint count);
	inline unsigned int getStride() const { return _stride; }
	inline const std::vector<BufferElement>& getElements() const { return _elements; }
};