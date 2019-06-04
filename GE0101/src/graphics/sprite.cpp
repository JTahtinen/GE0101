/*#include "sprite.h"
#include "../defs.h"
#include "renderers/renderer.h"

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
	_texture->bind(TEXTURE_SLOT_SPRITE);
}

void Sprite::unbind() const
{
	_mesh->unbind();
	_texture->unbind();
}*/