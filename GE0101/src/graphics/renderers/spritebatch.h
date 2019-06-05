#pragma once
#include "../sprite.h"
#include "../../math/vec3.h"
#include <vector>
#include "spritebatch.h"

struct SpriteRenderable
{
	const Sprite* sprite;
	Vec2 pos;
	Vec3 offset;
};

class SpriteBatch
{
	const Texture*								_refTexture;
	std::vector<SpriteRenderable>				_data;
public:
	SpriteBatch(const Texture* reference);
	void submit(const Sprite* sprite, const Vec2& pos, const Vec3& offset);
	inline bool checkCompatibility(const Sprite* sprite)
	{
		return (sprite->texture->getId() == _refTexture->getId());
	}
	void bindTexture(unsigned int slot = 0) const;
	inline const std::vector<SpriteRenderable>& getData() const { return _data; }
	void clear();
};