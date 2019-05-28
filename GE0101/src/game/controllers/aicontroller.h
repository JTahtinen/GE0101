#pragma once
#include "controller.h"
#include "../gamestate.h"

enum AITask
{
	AI_IDLE = 0,
	AI_FOLLOW,
	AI_HOSTILE,
	AI_NUM_TASKS
};

class AIController : public Controller
{
	const GameState*	_game;
	AITask				_task{ AI_IDLE };
public:
	AIController(GameState* game);
	virtual void update(Actor* e) override;
};