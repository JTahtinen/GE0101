#include "staticgraphicscomponent.h"
#include "../entity.h"
#include "../../../graphics/layer.h"
#include "../../camera.h"


StaticGraphicsComponent::StaticGraphicsComponent(std::shared_ptr<const Sprite> sprite)
	: _sprite(sprite)
{
	ASSERT(_sprite);
}

void StaticGraphicsComponent::update(Entity* e)
{

}

void StaticGraphicsComponent::render(const Entity* e, Layer* layer, const Camera& camera) const
{
	const Vec2& pos = e->getPhysics()->getPos().center;

	const float screenLeft = camera.getLeft();
	const float screenRight = camera.getRight();
	const float screenBottom = camera.getBottom();
	const float screenTop = camera.getTop();
	if (camera.inBounds(pos, _sprite->size))
	{
		layer->submitSprite(_sprite, pos, -camera.getPos());
	}
}