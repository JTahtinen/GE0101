#include "log.h"
#include "../defs.h"

void Log::message(const std::string& content)
{
	_messages.push_back(content);
#ifdef _DEBUG
	printLast();
#endif
}

void Log::warning(const std::string& content)
{
	_messages.push_back("WARNING: " + content);
#ifdef _DEBUG
	printLast();
#endif 
}

void Log::error(const std::string& content)
{
	_messages.push_back("ERROR: " + content);
#ifdef _DEBUG
	printLast();
#endif 
}

void Log::print() const
{
	for (auto& message : _messages)
	{
		MSG(message.c_str());
	}
}

void Log::printLast() const
{
	if (!_messages.empty())
	{
		MSG(_messages.back().c_str());
	}
}