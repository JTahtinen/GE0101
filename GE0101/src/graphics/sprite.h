#pragma once
#include "texture.h"
#include "mesh.h"

class Sprite
{
	const Mesh*				_mesh;
	const Texture*			_texture;
	std::string				_name;
public:
	Sprite(const Mesh* mesh, const Texture* texture, const std::string& name);
	void bind() const;
	void unbind() const;
	inline unsigned int getElementCount() const { return _mesh->getElementCount(); }
	inline const std::string& getName() const { return _name; }
};