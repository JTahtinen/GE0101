#pragma once
#include "../actor.h"

class Controller
{
public:
	virtual void update(Actor* e) = 0;
};