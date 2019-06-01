#pragma once
#include "physicsobject.h"
#include <vector>


class Collider
{
	std::vector<PhysicsObject*>		_objects;
	std::vector<PhysicsObject*>		_movingObjects;
public:
	inline static Collider& instance()
	{
		static Collider collider;
		return collider;
	}
	void push(PhysicsObject* obj);
	void update();
private:
	Collider();
	void clear();	
	bool overlap(const Location& loc1, const Location& loc2) const;
};