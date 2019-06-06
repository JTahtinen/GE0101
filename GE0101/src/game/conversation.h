#pragma once
#include <string>
#include <vector>
//#include <utility>
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
	std::shared_ptr<ConvNode>			link;
};

class ConvNode
{
	std::string					_text{ "" };
	std::vector<ConvOption>		_options;
public:
	void print() const;
	void render(Layer& layer, std::shared_ptr<const Font> font) const;
	void setText(const std::string& text);
	void addOption(const std::string& text, std::shared_ptr<ConvNode> link);
	unsigned int getNumOptions() const;
	std::shared_ptr<ConvNode> activate();
	std::shared_ptr<ConvNode> getNodeFromOption(unsigned int i);
};


class Conversation
{
	std::vector<std::shared_ptr<ConvNode>>		_nodes;
	std::shared_ptr<ConvNode>					_activeNode;
public:
	~Conversation();
	Conversation();
	void push(std::shared_ptr<ConvNode> node);
	void start();
	Conversation_Status update();
	void render(Layer& layer, std::shared_ptr<const Font> font) const;
private:
	void reset();
};