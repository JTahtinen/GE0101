#pragma once
#include "controller.h"
#include <vector>
#include <utility>

enum InputCommand
{
	MOVE_LEFT = 0,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	INC_SPEED,
	NUM_INPUTS
};


class InputController : public Controller
{
	std::vector<std::pair<EntityCommand, bool>>		_inputCommands;
	std::vector<std::pair<EntityCommand, int>>		_commandList;
	int												_numCommands;
public:
	InputController();
	virtual void update(Actor* e) override;
private:
	void setInput(InputCommand command, bool active);
};