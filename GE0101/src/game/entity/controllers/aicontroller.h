#pragma once
#include "controller.h"
#include "../../states/gamestate.h"

enum AITask
{
	AI_IDLE = 0,
	AI_FOLLOW,
	AI_HOSTILE,
	AI_NUM_TASKS
};

class AIController : public Controller
{
	const std::shared_ptr<GameState>	_game;
	AITask								_task{ AI_IDLE };
public:
	AIController(std::shared_ptr<GameState> game);
	virtual void update(Actor* e) override;
};