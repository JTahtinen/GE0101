#pragma once
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include <vector>
#include <string>

class Mesh
{
	std::string			_name;
	VertexArray			_vao;
	IndexBuffer			_ibo;
public:
	Mesh(const std::string& name);
	void pushData(Buffer* data, const BufferLayout& layout);
	void setIndices(const std::vector<unsigned int>& indices);
	inline unsigned int getElementCount() const { return _ibo.getSize(); }
	void bind() const;
	void unbind() const;
	static std::shared_ptr<Mesh> loadMesh(const std::string& filepath);
	inline const std::string& getName() const { return _name; }
};