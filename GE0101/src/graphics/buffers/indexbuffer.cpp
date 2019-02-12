#include "indexbuffer.h"
#include <GLEW/glew.h>

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &_id);
}

void IndexBuffer::push(const void* data, unsigned int count) const
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}