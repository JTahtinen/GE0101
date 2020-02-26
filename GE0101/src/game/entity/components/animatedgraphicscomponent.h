#pragma once
#include <memory>
#include <vector>
#include "graphicscomponent.h"
#include "../../../graphics/sprite.h"

class AnimatedGraphicsComponent : public GraphicsComponent
{
protected:
	std::vector<std::shared_ptr<const Sprite>>			_frames;
	std::shared_ptr<const Sprite>						_currentFrame;
public:
	AnimatedGraphicsComponent(std::vector<std::shared_ptr<const Sprite>> frames);
	virtual void update(Entity* e) override;
	virtual void render(const Entity* e, Layer* layer, const Camera& camera) const override;
};