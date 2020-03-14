#pragma once
#include "../datatypes/string.h"
#include <vector>
#include <memory>

struct StringReserve
{
	std::vector<String>					string15;
	unsigned int						numString15{ 0 };
	std::vector<String>					string30;
	unsigned int						numString30{ 0 };
	std::vector<String>					string50;
	unsigned int						numString50{ 0 };
	String								defaultString{ String("DEFAULT_STRING") };
};

class Factory
{	
	static StringReserve				_stringReserve;
public:
	static void init();
	static void quit();
	static String* createString(const char* content);

};