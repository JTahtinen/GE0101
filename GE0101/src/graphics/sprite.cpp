#include "sprite.h"
#include "../defs.h"

Sprite::Sprite(const Mesh* mesh, const Texture* texture, const std::string& name)
	: _mesh(mesh)
	, _texture(texture)
	, _name(name)
{
	ASSERT(_mesh);
	ASSERT(_texture);
	bind();
}

void Sprite::bind() const
{
	_mesh->bind();
	_texture->bind();
}

void Sprite::unbind() const
{
	_mesh->unbind();
	_texture->unbind();
}