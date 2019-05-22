#include "aicontroller.h"
#include "../../defs.h"

AIController::AIController(Game* game)
	: _game(game)
{
	ASSERT(game);
}

void AIController::update(Actor* e)
{
	float speed = 0.6f;
	const Actor* player = _game->getPlayer();
	Vec2 distanceFromPlayer = e->getPos() - player->getPos();

	if (_task == AI_IDLE)
	{
		if (distanceFromPlayer > 0.3f)
		{
			_task = AI_FOLLOW;
	//		MSG("AI TASK: Follow");
		}
	} else if (_task == AI_FOLLOW)
	{
		e->setForce(-distanceFromPlayer.getNormal() * speed);
		if (distanceFromPlayer <= 0.3f)
		{
			e->setForce(Vec2(0, 0));
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
		e->setForce(-distanceFromPlayer.getNormal() * speed * 3.0f);
		if (distanceFromPlayer <= 0.3f)
		{
			e->setForce(Vec2(0, 0));
			_task = AI_IDLE;
	//		MSG("AI TASK: Idle");
		}
	}
}