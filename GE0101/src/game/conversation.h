#pragma once
#include <string>
#include <vector>
#include <utility>

class ConvNode;

struct ConvOption
{
	std::string			text;
	ConvNode*			link;
};

class ConvNode
{
	std::string					_text{ "" };
	std::vector<ConvOption>		_options;
public:
	void print() const;
	void setText(const std::string& text);
	void addOption(const std::string& text, ConvNode* link);
	unsigned int numOptions() const;
	ConvNode* getNodeFromOption(unsigned int i);
};


class Conversation
{
	bool						_active;
	std::vector<ConvNode*>		_nodes;
public:
	Conversation();
	void push(ConvNode* node);
	void start();
	void activateNode(ConvNode& node);
	void end();
};