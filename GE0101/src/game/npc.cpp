#include "npc.h"

void NPC::setTarget(const Entity* target)
{
	_target = target;
}

const Entity* NPC::getTarget() const
{
	return _target;
}

void NPC::addAlly(const Actor* ally)
{
	if (ally)
	{
		for (const auto& actor : _allies)
		{
			if (ally == actor)
			{
				return;
			}
		}
		_allies.push_back(ally);
	}
}

void NPC::addEnemy(const Actor* enemy)
{
	if (enemy)
	{
		for (const auto& actor : _enemies)
		{
			if (enemy == actor)
			{
				return;
			}
		}
		_enemies.push_back(enemy);
	}
}