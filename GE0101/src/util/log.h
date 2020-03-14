#pragma once
#include <vector>
#include <string>

class Log
{
	std::vector<std::string>	_messages;
public:
	void message(const std::string& content);
	void warning(const std::string& content);
	void error(const std::string& content);
	void print() const;
	void printLast() const;
	void writeToFile(const std::string& filename) const;
	std::string toString() const;
};