#pragma once

#include <unordered_map>
#include <string>

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
	std::shared_ptr<const T> getElement(const std::string& name) const
	{
		return _data.at(name);
	}
};