#include "indexbuffer.h"
#include <GLEW/glew.h>
#include "../../defs.h"

IndexBuffer::IndexBuffer()
	:
	_numIndices(0)
{
	GLCALL(glGenBuffers(1, &_id));
	bind();
}

void IndexBuffer::push(const void* data, unsigned int count)
{
	_numIndices = count;
	bind();
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}