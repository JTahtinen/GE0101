#pragma once
#include "entity.h"

class Controller
{
public:
	virtual void update(Entity* e) const = 0;
};