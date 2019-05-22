#pragma once
#include <string>
#include <vector>
#include "../defs.h"

class Observer {
public:
	virtual void onNotify(std::string& message) = 0;
};

class Observable
{
	std::vector<Observer*>		_observers;
public:
	Observable()
	{
		_observers.reserve(10);
	}
	inline void subscribe(Observer* observer)
	{
		if (observer)
		{
			for (auto& ob : _observers)
			{
				if (observer == ob)
				{
					WARN("Obsever subscription ignored - Observer already present");
					return;
				}
			}
			_observers.push_back(observer);
		}
	}
	virtual void notify(std::string& message) = 0;
};