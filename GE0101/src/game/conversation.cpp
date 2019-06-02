#include "conversation.h"
#include "../defs.h"
#include "../input/input.h"
#include "../graphics/textbox.h"

void ConvNode::print() const
{
	MSG(_text << std::endl);
	unsigned int optionNum = 1;
	for (auto& option : _options)
	{
		MSG(optionNum++ << ": " << option.text);
	}
}

void ConvNode::render(Renderer* renderer) const
{
	TextBox box(_text);
	unsigned int i = 1;
	box.pushContent(" ");
	for (auto& option : _options)
	{
		box.pushContent(std::to_string(i++) + ": " +  option.text);
	}
	box.render(renderer, Vec2(-0.4f, 0.2f));
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

ConvNode* ConvNode::activate()
{
	static Input& in = Input::instance();

	unsigned int  numOptions = getNumOptions();
	for (unsigned int i = 0; i < numOptions; ++i)
	{
		if (in.poll(KEY_1 + i, KEYSTATE_TYPED))
		{
			return getNodeFromOption(i);
		}
	}
	return this;

}

Conversation::Conversation()
{
	_nodes.reserve(10);
}

Conversation::~Conversation()
{
	for (auto& node : _nodes)
	{
		delete node;
	}
	_nodes.clear();
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
	reset();
}

Conversation_Status Conversation::update()
{
	if (Input::instance().poll(KEY_E, KEYSTATE_TYPED))
	{
		reset();
		return CONVERSATION_FINISHED;
	}
	_activeNode = _activeNode->activate();
	if (!_activeNode)
	{
		reset();
		return CONVERSATION_FINISHED;
	}
	return CONVERSATION_RUNNING;
}

void Conversation::reset()
{
	if (_nodes.empty())
	{
		WARN("Could not reset Conversation - No nodes!");
		return;
	}
	_activeNode = _nodes[0];
}

void Conversation::render(Renderer* renderer) const
{
	if (_activeNode)
	{
		_activeNode->render(renderer);
	}
}