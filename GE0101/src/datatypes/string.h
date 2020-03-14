#pragma once

class String
{
	unsigned int					_capacity;
	unsigned int					_numCharacters;
	char*							_content;
public:
	String(const char* content);
	String(unsigned int capacity);
	String(const String& other);
	~String();
	void set(const char* content);
	void print() const;
	
	inline const char* c_str() {return _content;} const
	inline String operator=(const char* content) { return String(content); }
};