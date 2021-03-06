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

void ConvNode::render(Layer& layer) const
{
	TextBox box(_text);
	unsigned int i = 1;
	box.addContent(" ");
	for (auto& option : _options)
	{
		box.addContent(std::to_string(i++) + ": " +  option.text);
	}
	box.render(layer, Vec2(-0.4f, 0.2f));
}

void ConvNode::setText(const std::string& text)
{
	_text = text;
}

void ConvNode::addOption(const std::string& text, std::shared_ptr<ConvNode> link)
{
	_options.emplace_back(ConvOption{ text, link.get() });
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
		if (in.pollKeyboard(KEY_1 + i, KEYSTATE_TYPED))
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
	_nodes.clear();
}

void Conversation::push(std::shared_ptr<ConvNode> node)
{
		_nodes.push_back(node);
}

void Conversation::start()
{
	reset();
}

Conversation_Status Conversation::update()
{
	if (Input::instance().pollKeyboard(KEY_E, KEYSTATE_TYPED))
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
	_activeNode = _nodes[0].get();
}

void Conversation::render(Layer& layer) const
{
	if (_activeNode)
	{
		_activeNode->render(layer);
	}
}