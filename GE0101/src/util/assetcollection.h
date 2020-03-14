#pragma once

#include <unordered_map>
#include <string>
#include <memory>

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
		clear();
	}

	inline void addElement(std::shared_ptr<T> element, const std::string& name)
	{		
		_data[name] = element;
	}

	inline void removeElement(const std::string& name)
	{
		_data.erase(name);
	}

	inline std::shared_ptr<T> getElement(const std::string& name)
	{
		std::shared_ptr<T> elem = _data[name];
		if (!elem)
		{
			return nullptr;
		}
		return elem;
	}

	inline void clear()
	{
		_data.clear();
	}

	inline bool empty() const
	{
		return _data.empty();
	}
};