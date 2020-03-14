#include "factory.h"

#define MAX_STRINGS 50

StringReserve Factory::_stringReserve;

void Factory::init()
{
	_stringReserve.string15.reserve(MAX_STRINGS);
	_stringReserve.string30.reserve(MAX_STRINGS);
	_stringReserve.string50.reserve(MAX_STRINGS);

	for (unsigned int i = 0; i < MAX_STRINGS; ++i)
	{
		_stringReserve.string15.emplace_back(String(15));
		_stringReserve.string30.emplace_back(String(30));
		_stringReserve.string50.emplace_back(String(50));
	}
}

void Factory::quit()
{
}

String* Factory::createString(const char* content)
{
	unsigned int length = strlen(content);
	unsigned int* numString;
	String* string = &_stringReserve.defaultString;
	// Do, or do not. There is no DRY

	if (length <= 15)
	{
		numString = &_stringReserve.numString15;
		if (*numString < MAX_STRINGS)
		{
			string = &_stringReserve.string15[*numString];
			*numString = *numString + 1;
		} 
	} else if (length <= 30)
	{
		numString = &_stringReserve.numString30;
		if (*numString < MAX_STRINGS)
		{
			string = &_stringReserve.string30[*numString];
			*numString = *numString + 1;
		}
	}	
	else if (length <= 50)
	{
		numString = &_stringReserve.numString50;
		if (*numString < MAX_STRINGS)
		{
			string = &_stringReserve.string30[*numString];
			*numString = *numString + 1;
		}
	}
	string->set(content);
	return string;
}