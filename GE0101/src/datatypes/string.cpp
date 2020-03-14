#include "string.h"
#include <cstring>
#include <stdio.h>

String::String(const char* content)
	: _capacity(strlen(content) + 1)
	, _numCharacters(_capacity)
	, _content(new char[_capacity])
{
	memcpy(_content, content, _numCharacters);
}

String::String(unsigned int capacity)
	: _capacity(capacity)
	, _numCharacters(_capacity)
	, _content(new char[_capacity])
{

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
	if (_numCharacters > _capacity)
	{
		_numCharacters = _capacity;
	}
	memcpy(_content, content, _numCharacters);
	_content[_numCharacters - 1] = '\0';
}

void String::print() const
{
	printf("%s", _content);
}