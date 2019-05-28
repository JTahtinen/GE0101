#pragma once

class Game;

enum State_Type
{
	STATE_GAME,
	STATE_CONVERSATION
};

enum State_Condition
{
	STATE_RUNNING,
	STATE_FINISHED
};

class State
{
public:
	virtual ~State() {};
	virtual State_Condition update(Game* game) = 0;
};