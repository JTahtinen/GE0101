#include "mesh.h"
#include "../defs.h"

Mesh::Mesh(const std::string& name)
	: _name(name)
{
	bind();
}

void Mesh::pushData(Buffer* data, const BufferLayout& layout)
{
	if (!data)
	{
		WARN("Could not push buffer data to Mesh - nullptr exception");
		return;
	}
	bind();
	_vao.push(data, layout);
}

void Mesh::setIndices(const std::vector<unsigned int>& indices)
{
	if (indices.empty())
	{
		WARN("Could not push index buffer for mesh - index vector was empty");
		return;
	}
		_ibo.push(&indices[0], indices.size());
}

void Mesh::bind() const
{
	_vao.bind();
	_ibo.bind();
}

void Mesh::unbind() const
{
	_vao.unbind();
	_ibo.unbind();
}


std::shared_ptr<Mesh> Mesh::loadMesh(const std::string& filepath)
{
	//TODO: Mesh loading
	return std::make_shared<Mesh>(filepath);
}