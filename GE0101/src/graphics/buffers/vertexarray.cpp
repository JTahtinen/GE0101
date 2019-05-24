#include "vertexarray.h"
#include <GLEW/glew.h>
#include "../../util/glutil.h"
#include "../../defs.h"

VertexArray::VertexArray(const std::string& name)
	: _name(name)
{
	GLCALL(glGenVertexArrays(1, &_id));
	bind();
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &_id));
}

void VertexArray::push(Buffer* buffer, const BufferLayout& layout)
{
	const auto& elements = layout.getElements();
	bind();
	buffer->bind();
	int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(_numAttributes));
		GLCALL(glVertexAttribPointer(_numAttributes++, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
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
	return new VertexArray(filepath);
}