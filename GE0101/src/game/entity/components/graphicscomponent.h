#pragma once
#include "component.h"
#include "../../../math/vec3.h"

class Camera;
class Layer;

class GraphicsComponent : public Component
{
public:
	virtual void render(const Entity* e, Layer* layer, const Camera& camera) const = 0;
};