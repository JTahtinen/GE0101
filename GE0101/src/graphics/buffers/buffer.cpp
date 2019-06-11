#include "buffer.h"
#include "../../util/glutil.h"
#include "../../defs.h"

Buffer::Buffer()
{
	GLCALL(glGenBuffers(1, &_id));
}

Buffer::~Buffer()
{
	GLCALL(glDeleteBuffers(1, &_id));
}

void Buffer::push(const void* data, unsigned int size) const
{
	bind();
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}	

void Buffer::bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void Buffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}