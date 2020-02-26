#pragma once
#include <memory>
#include "graphicscomponent.h"
#include "../../../graphics/sprite.h"

class StaticGraphicsComponent : public GraphicsComponent
{
protected:
	std::shared_ptr<const Sprite>					_sprite;
public:
	StaticGraphicsComponent(std::shared_ptr<const Sprite> sprite);
	virtual void update(Entity* e) override;
	virtual void render(const Entity* e, Layer* layer, const Camera& camera) const override;
};
