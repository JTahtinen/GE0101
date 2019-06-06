#pragma once
#include "../sprite.h"
#include "../../math/vec3.h"
#include <vector>
#include "spritebatch.h"

struct SpriteRenderable
{
	std::shared_ptr<const Sprite>		sprite;
	Vec2								pos;
	Vec3								offset;
};

class SpriteBatch
{
	std::shared_ptr<const Texture>				_refTexture;
	std::vector<SpriteRenderable>				_data;
public:
	SpriteBatch(std::shared_ptr<const Texture> reference);
	void submit(std::shared_ptr<const Sprite> sprite, const Vec2& pos, const Vec3& offset);
	inline bool checkCompatibility(const Sprite& sprite)
	{
		return (sprite.texture->getId() == _refTexture->getId());
	}
	void bindTexture() const;
	inline const std::vector<SpriteRenderable>& getData() const { return _data; }
	void clear();
};