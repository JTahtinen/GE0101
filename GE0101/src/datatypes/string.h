#pragma once

class String
{
	unsigned int					_numCharacters;
	char*							_content;
public:
	String(const char* content);
	String(const String& other);
	~String();
	void set(const char* content);
	void print() const;
	
	inline String operator=(const char* content) { return String(content); }
};