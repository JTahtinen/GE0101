#include "aicontroller.h"
#include "../../../defs.h"

AIController::AIController(std::shared_ptr<GameState> game)
	: _game(game)
{
}

void AIController::update(Actor* e)
{
	float speed = 0.6f;
	auto player = _game->getPlayer();
	Vec2 distanceFromPlayer = e->getPhysics()->getPos().center 
		- player->getPhysics()->getPos().center;

	if (_task == AI_IDLE)
	{
		if (distanceFromPlayer > 0.3f)
		{
			_task = AI_FOLLOW;
	//		MSG("AI TASK: Follow");
		}
	} else if (_task == AI_FOLLOW)
	{
		e->move(-distanceFromPlayer, speed);
		if (distanceFromPlayer <= 0.3f)
		{
			e->move(Vec2(0, 0), 0);
			_task = AI_IDLE;
	//		MSG("AI TASK: Idle");
		}
		else if (distanceFromPlayer > 1.0f)
		{
			_task = AI_HOSTILE;
		//	MSG("AI TASK: Hostile");
		}
	}
	else if (_task == AI_HOSTILE)
	{
		e->move(-distanceFromPlayer, speed * 3.0f);
		if (distanceFromPlayer <= 0.3f)
		{
			e->move(Vec2(0, 0), 0);
			_task = AI_IDLE;
	//		MSG("AI TASK: Idle");
		}
	}
}