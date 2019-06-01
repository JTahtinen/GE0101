#pragma once
#include "controller.h"

class InputController : public Controller
{
public:
	virtual void update(Actor* e) override;
};