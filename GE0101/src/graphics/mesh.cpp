#include "mesh.h"
#include "../defs.h"

Mesh::Mesh(const std::string& name)
	: _vao(name)
{
	bind();
}

void Mesh::pushData(Buffer* data, const BufferLayout& layout, std::vector<unsigned int>& indices)
{
	if (!data)
	{
		WARN("Could not push buffer data to Mesh - nullptr exception");
		return;
	}
	bind();
	_vao.push(data, layout);
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


Mesh* Mesh::loadMesh(const std::string& filepath)
{
	//TODO: Mesh loading
	return new Mesh(filepath);
}