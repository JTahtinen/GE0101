#include "animatedgraphicscomponent.h"
#include "../../camera.h"

#define NUM_FRAMES 5

enum
{
	FRAME_STATIONARY = 0,
	FRAME_LEFT,
	FRAME_UP,
	FRAME_RIGHT,
	FRAME_DOWN
};

AnimatedGraphicsComponent::AnimatedGraphicsComponent(std::vector<std::shared_ptr<const Sprite>> frames)
	: _frames(frames)
{
	ASSERT(_frames.size() == NUM_FRAMES);
	_currentFrame = _frames[0];
}

void AnimatedGraphicsComponent::update(Entity* e)
{
	const PhysicsObject* physics = e->getPhysics();
	const Vec2& vel = physics->getForce();
	if (!physics->isMoving())
	{
		_currentFrame = _frames[FRAME_STATIONARY];
		return;
	}
	if (vel.x > 0)
	{
		_currentFrame = _frames[FRAME_RIGHT];
		return;
	}
	if (vel.x < 0)
	{
		_currentFrame = _frames[FRAME_LEFT];
		return;
	}
	if (vel.y > 0)
	{
		_currentFrame = _frames[FRAME_UP];
		return;
	}

	if (vel.y < 0)
	{
		_currentFrame = _frames[FRAME_DOWN];
		return;
	}

}

void AnimatedGraphicsComponent::render(const Entity* e, Layer* layer, const Camera& camera) const
{
	const Vec2& pos = e->getPhysics()->getPos().center;

	const float screenLeft = camera.getLeft();
	const float screenRight = camera.getRight();
	const float screenBottom = camera.getBottom();
	const float screenTop = camera.getTop();
	if (camera.inBounds(pos, _currentFrame->size))
	{
		layer->submitSprite(_currentFrame, pos, -camera.getPos());
	}
}