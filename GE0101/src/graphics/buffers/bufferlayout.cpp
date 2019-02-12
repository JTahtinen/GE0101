#include "bufferlayout.h"
#include "../../util/glutil.h"

BufferLayout::BufferLayout()
	: 
	_stride(0)
{
	_elements.reserve(3);
}

template <>
void BufferLayout::push<float>(GLint count)
{
	_elements.push_back(BufferElement{ GL_FLOAT, count, GL_FALSE });
	_stride += GLutil::sizeOfType(GL_FLOAT) * count;
}

template <>
void BufferLayout::push<int>(GLint count)
{
	_elements.push_back(BufferElement{ GL_INT, count, GL_FALSE });
	_stride += GLutil::sizeOfType(GL_INT) * count;
}

template <>
void BufferLayout::push<unsigned int>(GLint count)
{
	_elements.push_back(BufferElement{ GL_UNSIGNED_INT, count, GL_FALSE });
	_stride += GLutil::sizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void BufferLayout::push<double>(GLint count)
{
	_elements.push_back(BufferElement{ GL_DOUBLE, count, GL_FALSE });
	_stride += GLutil::sizeOfType(GL_DOUBLE) * count;
}