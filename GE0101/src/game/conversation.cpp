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

unsigned int ConvNode::getNumOptions() const
{
	return _options.size();
}

void ConvNode::activate()
{
	static Input& in = Input::instance();
	print();
	MSG(std::endl);
	unsigned int  numOptions = getNumOptions();
	bool active = (numOptions != 0);
	while (active)
	{
		in.update();
		for (unsigned int i = 0; i < numOptions; ++i)
		{
			if (in.poll(KEY_1 + i, KEYSTATE_TYPED))
			{
				ConvNode* next = getNodeFromOption(i);
				if (next)
				{
					next->activate();
				}
				active = false;
				break;
			}
		}
	}
}

Conversation::Conversation()
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
	if (_nodes.empty())
	{
		WARN("Could not start Conversation - No nodes!");
		return;
	}
	_nodes[0]->activate();
}