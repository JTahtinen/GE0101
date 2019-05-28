#pragma once
#include <string>
#include <vector>
#include <utility>

enum Conversation_Status
{
	CONVERSATION_RUNNING,
	CONVERSATION_FINISHED
};

class Renderer;
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
	void render(Renderer* renderer) const;
	void setText(const std::string& text);
	void addOption(const std::string& text, ConvNode* link);
	unsigned int getNumOptions() const;
	ConvNode* activate();
	ConvNode* getNodeFromOption(unsigned int i);
};


class Conversation
{
	std::vector<ConvNode*>		_nodes;
	ConvNode*					_activeNode;
public:
	Conversation();
	void push(ConvNode* node);
	void start();
	Conversation_Status update();
	void render(Renderer* renderer) const;
private:
	void reset();
};