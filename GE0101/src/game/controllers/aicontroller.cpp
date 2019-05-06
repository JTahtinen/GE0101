#include "aicontroller.h"
#include "../../defs.h"

AIController::AIController(Game* game)
	: _game(game)
{
	ASSERT(game);
}

void AIController::update(Actor* e)
{
	const Actor* player = _game->getPlayer();
	Vec2 distanceFromPlayer = e->getPos() - player->getPos();

	if (_task == AI_IDLE)
	{
		if (distanceFromPlayer > 0.3f)
		{
			_task = AI_FOLLOW;
			MSG("AI TASK: Follow");
		}
	} else if (_task == AI_FOLLOW)
	{
		e->setVel(-distanceFromPlayer.getNormal() * 0.001f);
		if (distanceFromPlayer <= 0.3f)
		{
			e->setVel(Vec2(0, 0));
			_task = AI_IDLE;
			MSG("AI TASK: Idle");
		}
		else if (distanceFromPlayer > 2.0f)
		{
			_task = AI_HOSTILE;
			MSG("AI TASK: Hostile");
		}
	}
	else if (_task == AI_HOSTILE)
	{
		e->setVel(-distanceFromPlayer.getNormal() * 0.01f);
		if (distanceFromPlayer <= 0.3f)
		{
			e->setVel(Vec2(0, 0));
			_task = AI_IDLE;
			MSG("AI TASK: Idle");
		}
	}
}