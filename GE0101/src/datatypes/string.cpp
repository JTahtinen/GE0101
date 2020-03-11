#include "string.h"
#include <cstring>
#include <stdio.h>

String::String(const char* content)
	: _numCharacters(strlen(content) + 1)
	, _content(new char[_numCharacters])
{
	memcpy(_content, content, _numCharacters);
}

String::String(const String& other)
	: _numCharacters(other._numCharacters)
	, _content(new char[_numCharacters])
{
	memcpy(_content, other._content, _numCharacters);	
}

String::~String()
{
	delete _content;
	_content = nullptr;
}

void String::set(const char* content)
{
	_numCharacters = strlen(content) + 1;
	memcpy(_content, content, _numCharacters);
}

void String::print() const
{
	printf("%s", _content);
}