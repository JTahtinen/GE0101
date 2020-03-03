#include "inputcontroller.h"
#include "../../../input/input.h"


InputController::InputController()
	: _numCommands(0)
{
	_inputCommands.reserve(NUM_INPUTS);
	_commandList.reserve(NUM_INPUTS);
	
	for (int i = 0; i < NUM_INPUTS; ++i)
	{
		_inputCommands.push_back(std::pair<EntityCommand, bool>()); 
		_commandList.push_back(std::pair<EntityCommand, int>());
		_inputCommands[i].second = false;
		_commandList[i].second = -1;
	}
	_inputCommands[MOVE_LEFT].first = COMMAND_MOVE_LEFT;
	_inputCommands[MOVE_RIGHT].first = COMMAND_MOVE_RIGHT;
	_inputCommands[MOVE_UP].first = COMMAND_MOVE_UP;
	_inputCommands[MOVE_DOWN].first = COMMAND_MOVE_DOWN;
	_inputCommands[INC_SPEED].first = COMMAND_INCREASE_SPEED;

	_commandList[MOVE_LEFT].first = COMMAND_MOVE_LEFT;
	_commandList[MOVE_RIGHT].first = COMMAND_MOVE_RIGHT;
	_commandList[MOVE_UP].first = COMMAND_MOVE_UP;
	_commandList[MOVE_DOWN].first = COMMAND_MOVE_DOWN;
	_commandList[INC_SPEED].first = COMMAND_INCREASE_SPEED;


}

void InputController::update(Actor* e)
{
	static float speed = 1.0f;
	static float runningSpeed = 1.8f;
	static float currentSpeed = speed;
	Input& in = Input::instance();
	if (in.pollKeyboard(KEY_LSHIFT, KEYSTATE_TYPED))
	{
		setInput(INC_SPEED, true);
		//e->addCommand(COMMAND_INCREASE_SPEED);
	}
	else if (in.pollKeyboard(KEY_LSHIFT, KEYSTATE_RELEASED))
	{
		//e->addCommand(COMMAND_DECREASE_SPEED);
		setInput(INC_SPEED, false);
	}
	if (in.pollKeyboard(KEY_A, KEYSTATE_TYPED))
	{
		//e->addCommand(COMMAND_MOVE_LEFT);
		setInput(MOVE_LEFT, true);
	}
	else if (in.pollKeyboard(KEY_A, KEYSTATE_RELEASED))
	{
		setInput(MOVE_LEFT, false);
	}
	if (in.pollKeyboard(KEY_D, KEYSTATE_TYPED))
	{
		//e->addCommand(COMMAND_MOVE_LEFT);
		setInput(MOVE_RIGHT, true);
	}
	else if (in.pollKeyboard(KEY_D, KEYSTATE_RELEASED))
	{
		setInput(MOVE_RIGHT, false);
	}
	if (in.pollKeyboard(KEY_W, KEYSTATE_TYPED))
	{
		//e->addCommand(COMMAND_MOVE_LEFT);
		setInput(MOVE_UP, true);
	}
	else if (in.pollKeyboard(KEY_W, KEYSTATE_RELEASED))
	{
		setInput(MOVE_UP, false);
	}
	if (in.pollKeyboard(KEY_S, KEYSTATE_TYPED))
	{
		//e->addCommand(COMMAND_MOVE_LEFT);
		setInput(MOVE_DOWN, true);
	}
	else if (in.pollKeyboard(KEY_S, KEYSTATE_RELEASED))
	{
		setInput(MOVE_DOWN, false);
	}


	std::vector<EntityCommand> sortedCommands;
	sortedCommands.reserve(6);

	for (int i = 0; i < _numCommands; ++i)
	{
		for (auto& command : _commandList)
		{
			if (command.second == i)
			{
				sortedCommands.push_back(command.first);
				break;
			}
		}
	}
	for (auto& command : sortedCommands)
	{
		e->addCommand(command);
	}
}

void InputController::setInput(InputCommand command, bool active)
{
	if (!active)
	{
		if (_inputCommands[command].second == true)
		{
			int curCommandNum = _commandList[command].second;
			--_numCommands;
			_commandList[command].second = -1;
			_inputCommands[command].second = false;
			for (auto& otherCommand : _commandList)
			{
				if (otherCommand.second > curCommandNum)
				{
					--otherCommand.second;
				}
			}
		}
	}
	else
	{
		if (_inputCommands[command].second == false)
		{
			_inputCommands[command].second = true;
			_commandList[command].second = _numCommands++;
		}
	}
}