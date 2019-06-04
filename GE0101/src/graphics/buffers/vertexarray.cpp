#include "vertexarray.h"
#include <GLEW/glew.h>
#include "../../util/glutil.h"
#include "../../defs.h"

VertexArray::VertexArray()
	: _numAttributes(0)
{
	GLCALL(glGenVertexArrays(1, &_id));
	bind();
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &_id));
	for (auto& buffer : _buffers)
	{
		delete buffer;
	}
}

void VertexArray::push(Buffer* buffer, const BufferLayout& layout)
{
	const auto& elements = layout.getElements();
	bind();
	buffer->bind();
	int offset = 0;
	for (auto& element : elements)
	{
		GLCALL(glEnableVertexAttribArray(_numAttributes));
		GLCALL(glVertexAttribPointer
		(_numAttributes++, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * GLutil::sizeOfType(element.type);
	}
	_buffers.push_back(buffer);
}

void VertexArray::bind() const
{
	GLCALL(glBindVertexArray(_id));
}

void VertexArray::unbind() const
{
	GLCALL(glBindVertexArray(0));
}

VertexArray* VertexArray::loadVertexArray(const std::string& filepath)
{
	//TODO: Vao loading
	return new VertexArray();
}