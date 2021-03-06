#include "spritebatch.h"
#include "../../defs.h"
#include "renderer.h"

SpriteBatch::SpriteBatch(std::shared_ptr<const Texture> reference)
	: _refTexture(reference)
{
	_data.reserve(500);
}

void SpriteBatch::submit(std::shared_ptr<const Sprite> sprite, const Vec2& pos, const Vec3& offset)
{
	if (sprite)
	{
		_data.emplace_back(SpriteRenderable{ sprite, pos, offset });
	}
}

void SpriteBatch::clear()
{
	_data.clear();
}

void SpriteBatch::bindTexture() const
{
	_refTexture->bind(TEXTURE_SLOT_SPRITE);
}