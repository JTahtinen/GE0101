#pragma once

#include <unordered_map>
#include <string>
#include "../defs.h"

template <typename T>
class AssetCollection
{
	std::unordered_map<std::string, std::shared_ptr<T>>		_data;
public:
	AssetCollection()
	{
		_data.reserve(50);
	}
	~AssetCollection()
	{
		_data.clear();
	}

	void addElement(std::shared_ptr<T> element, const std::string& name)
	{
		if (_data.find(name) == _data.end())
		{
			_data.insert({ name, element });
		}
	}

	void removeElement(const std::string& name)
	{
		_data.erase(name);
	}

	std::shared_ptr<T> getElement(const std::string& name) const
	{
		std::shared_ptr<T> elem = _data.at(name);
		if (!elem)
		{
			ERR("AssetManager: Could not get element : " << name);
			return nullptr;
		}
		return elem;
	}
};