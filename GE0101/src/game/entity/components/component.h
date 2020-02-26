#pragma once

class Entity;

class Component
{
public:
	virtual void update(Entity* e) = 0;
};