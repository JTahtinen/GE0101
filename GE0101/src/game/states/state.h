#pragma once

class Game;
class Layer;
class Vec2;

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
	virtual State_Condition update(Game& game) = 0;
	virtual void render(Layer& layer) = 0;
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const = 0;
};