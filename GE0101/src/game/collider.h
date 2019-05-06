#pragma once
#include "../math/shapes.h"
#include "../math/vec2.h"

class Game;
class Entity;

class Collider
{
	math::Rect _dimensions{ 1.0f, 1.0f };
public:
	Collider() = default;
	
	Collider(float width, float height);
	
	static bool collidesWith(const Vec2& pos1, const Vec2& pos2, 
		const Collider& collider1, const Collider& collider2);

	static Vec2 clippedVelocityVector(const Game* game, const Entity* e);
};