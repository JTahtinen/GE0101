#pragma once
#include <vector>
#include <string>
#include "../../defs.h"

#define DATA_OPERATIONS(t)		void load##t(const std::string& filepath);\
								void push##t(##t* unit);\
								##t* get##t(const std::string& name);\
								void remove##t(const std::string& name)


template <typename T>
inline void push(T* unit, std::vector<T*>& data)
{
	if (!unit)
	{
		WARN("Could not push item to vector - nullptr exception");
		return;
	}

	for (auto& e : data)
	{
		if (e == unit)
		{
			WARN("Unit addition to vector ignored - unit already present");
		}
	}
	data.push_back(unit);
}

template <typename T>
inline T* find(const std::string& name, std::vector<T*>& data)
{
	for (auto& unit : data)
	{
		if (unit->getName() == name)
		{
			return unit;
		}
	}
	return nullptr;
}

template <typename T>
inline void removeUnit(const std::string& name, std::vector<T*>& data)
{
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (data[i]->getName() == name)
		{
			delete data[i];
			data[i] = nullptr;
			return;
		}
	}
}