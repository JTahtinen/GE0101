#pragma once
#include "../actor.h"
#include <memory>

class Controller
{
public:
	virtual void update(Actor* e) = 0;
};