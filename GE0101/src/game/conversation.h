#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../graphics/font.h"

enum Conversation_Status
{
	CONVERSATION_RUNNING,
	CONVERSATION_FINISHED
};

class Layer;
class ConvNode;

struct ConvOption
{
	std::string							text;
	ConvNode*							link;
};

class ConvNode
{
	std::string					_text{ "" };
	std::vector<ConvOption>		_options;
public:
	void print() const;
	void render(Layer& layer) const;
	void setText(const std::string& text);
	void addOption(const std::string& text, std::shared_ptr<ConvNode> link);
	unsigned int getNumOptions() const;
	ConvNode* activate();
	ConvNode* getNodeFromOption(unsigned int i);
};


class Conversation
{
	std::vector<std::shared_ptr<ConvNode>>		_nodes;
	ConvNode*									_activeNode;
public:
	~Conversation();
	Conversation();
	void push(std::shared_ptr<ConvNode> node);
	void start();
	Conversation_Status update();
	void render(Layer& layer) const;
private:
	void reset();
};