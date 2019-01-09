#pragma once
#include "entity.h"
#include "../graphics/window.h"

class Camera : public Entity
{
	int					_targetW;
	int					_targetH;
public:
	Camera(const Surface& target);
	void update(Game* game) override;
	void setTarget(const Vec2& target);
	Vec2 getCameraCorrection(const Vec2& pos) const;
};