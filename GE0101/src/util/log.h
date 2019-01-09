#pragma once
#include <vector>

class Log
{
	std::vector<std::string>	_messages;
public:
	void message(const std::string& content);
	void warning(const std::string& content);
	void error(const std::string& content);
	void print() const;
	void printLast() const;
};