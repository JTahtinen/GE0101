#pragma once
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include <vector>
#include <string>

class Mesh
{
	VertexArray			_vao;
	IndexBuffer			_ibo;
public:
	Mesh(const std::string& name);
	void pushData(Buffer* data, const BufferLayout& layout);
	void setIndices(const std::vector<unsigned int>& indices);
	inline const std::string& getName() const { return _vao.getName(); }
	inline unsigned int getElementCount() const { return _ibo.getSize(); }
	void bind() const;
	void unbind() const;
	static Mesh* loadMesh(const std::string& filepath);
};