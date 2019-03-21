#include "buffer.h"
#include "../../util/glutil.h"

Buffer::Buffer()
{
	glGenBuffers(1, &_id);
}

void Buffer::push(const void* data, unsigned int size) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}