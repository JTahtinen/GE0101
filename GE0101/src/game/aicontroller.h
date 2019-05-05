#pragma once
#include "controller.h"

class AIController : public Controller
{
public:
	virtual void update(Entity* e) const override;
};