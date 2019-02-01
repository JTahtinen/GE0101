#pragma once
#include "controller.h"

class InputController : public Controller
{
public:
	virtual void update(Entity* e) const override;
};