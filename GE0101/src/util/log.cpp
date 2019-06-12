#include "log.h"
#include "../defs.h"
#include <fstream>

void Log::message(const std::string& content)
{
	_messages.push_back(content);
#ifdef _DEBUG
	printLast();
#endif
}

void Log::warning(const std::string& content)
{
	_messages.push_back("[WARNING] " + content);
#ifdef _DEBUG
	printLast();
#endif 
}

void Log::error(const std::string& content)
{
	_messages.push_back("[ERROR] " + content);
#ifdef _DEBUG
	printLast();
#endif 
}

void Log::print() const
{

	MSG(this->toString().c_str());
	
}

void Log::printLast() const
{
	if (!_messages.empty())
	{
		MSG(_messages.back().c_str());
	}
}

void Log::writeToFile(const std::string& filename) const
{
	std::ofstream file;
	file.open(filename);
	if (file.is_open())
	{
		file << this->toString().c_str();
	}
	else
	{
		ERR("Could not write log to file: " << filename.c_str());
	}
	file.close();
}

std::string Log::toString() const
{
	std::string output = "";
	for (const auto& msg : _messages)
	{
		output += msg;
	}
	return output;
}