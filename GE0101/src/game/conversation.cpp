#include "conversation.h"
#include "../defs.h"
#include "../input/input.h"

void ConvNode::print() const
{
	MSG(_text << std::endl);
	unsigned int optionNum = 1;
	for (auto& option : _options)
	{
		MSG(optionNum++ << ": " << option.text);
	}
}

void ConvNode::setText(const std::string& text)
{
	_text = text;
}

void ConvNode::addOption(const std::string& text, ConvNode* link)
{
	_options.emplace_back(ConvOption{ text, link });
}

ConvNode* ConvNode::getNodeFromOption(unsigned int i)
{
	if (i < _options.size())
	{
		return _options[i].link;
	}
	return nullptr;
}

unsigned int ConvNode::numOptions() const
{
	return _options.size();
}

Conversation::Conversation()
	: _active(false)
{
	_nodes.reserve(10);
}

void Conversation::push(ConvNode* node)
{
	if (node)
	{
		_nodes.push_back(node);
	}
}

void Conversation::start()
{
	_active = true;
	activateNode(*_nodes[0]);
	
}

void Conversation::activateNode(ConvNode& node)
{
	static Input& in = Input::instance();
	node.print();
	MSG(std::endl);
	unsigned int numOptions = node.numOptions();
	while (_active)
	{
		in.update();
		if (numOptions == 0)
		{
			_active = false;
			return;
		}
		for (unsigned int i = 0; i < numOptions; ++i)
		{
			if (in.poll(KEY_1 + i, KEYSTATE_TYPED))
			{
				ConvNode* next = node.getNodeFromOption(i);
				if (next)
				{
					activateNode(*next);
				}
				else 
				{
					_active = false;
					return;
				}
			}
		}
	}
	
}

void Conversation::end()
{

}