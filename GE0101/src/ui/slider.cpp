#include "slider.h"
#include "../math/math.h"
#include <sstream>
#include <iomanip>
#include "../defs.h"

#define SLIDER_VIS_WIDTH 0.02f
#define SLIDER_VIS_LENGTH 0.25f
#define SLIDER_KNOB_WIDTH 0.04f
#define SLIDER_KNOB_DEFAULT_COLOR Vec4(0.8f, 0.8f, 0.8f, 0.8f)
#define SLIDER_KNOB_HIGHLIGHT_COLOR Vec4(1.0f, 1.0f, 1.0f, 0.8f)
#define SLIDER_LABEL_SCALE 0.2f

Slider::Slider(const float rangeMin, const float rangeMax, const float initValue, const std::string& label, const Vec2& pos)
	: _rangeMin(rangeMin)
	, _rangeMax(rangeMax)
	, _valueAbs(initValue)
	, _label(label, SLIDER_LABEL_SCALE)
	, _tiedValue(nullptr)
	, _showLabel(true)
	, _pos(pos)
	, _highLight(false)
	, ScreenElement(pos - Vec2(SLIDER_KNOB_WIDTH * 0.25, SLIDER_KNOB_WIDTH * 0.25), Vec2(SLIDER_KNOB_WIDTH, SLIDER_VIS_LENGTH))
{
}

Slider::Slider(const float rangeMin, const float rangeMax, float* tiedValue, const std::string& label, const Vec2& pos)
	: Slider(rangeMin, rangeMax, 0.0f, label, pos)
{
	if (!tiedValue)
	{
		ERR("SLIDER: Could not tie value to slider. Pointer was NULL");
	}
	else
	{
		_tiedValue = tiedValue;
		_valueAbs = *tiedValue;
	}
}

void Slider::setValueAbs(float value)
{
	if (value > _rangeMax)
	{
		_valueAbs = _rangeMax;
	}
	else if (_valueAbs < _rangeMin)
	{
		_valueAbs = _rangeMin;
	}
	else {
		_valueAbs = value;
	}

	if (_tiedValue)
	{
		*_tiedValue = _valueAbs;
	}
}

void Slider::setValueZeroToOne(float value)
{
	if (value > 1.0f)
	{
		_valueAbs = _rangeMax;
	}
	else if (_valueAbs < 0)
	{
		_valueAbs = _rangeMin;
	}
	else {
		_valueAbs = projectToAbs(value);
	}

	if (_tiedValue)
	{
		*_tiedValue = _valueAbs;
	}
}

void Slider::slideByAbs(float value)
{
	setValueAbs(_valueAbs + value);
}

void Slider::slideByZeroToOne(float value)
{
	setValueZeroToOne(projectToZeroToOne(_valueAbs) + value);
}

void Slider::toggleLabel()
{
	_showLabel = !_showLabel;
}

float Slider::getValue() const
{
	return _valueAbs;
}

void Slider::render(Layer& layer, const Vec2& pos) const
{
	Vec2 finalPos = _posStart + pos;
	float visValue = 0;
	if (_valueAbs <= _rangeMin)
	{
		visValue = _rangeMin; // This is used to fix a bug where the slider might display negative 0
	}
	else
	{
		visValue = _valueAbs;
	}
	float knobVisPos = finalPos.y + math::projectToCoordinates(visValue, _rangeMin, _rangeMax, 0, SLIDER_VIS_LENGTH) + SLIDER_KNOB_WIDTH * 0.5f;
	layer.submitQuad(Vec2(finalPos.x - 0.5f * SLIDER_VIS_WIDTH, finalPos.y - 0.5f * SLIDER_VIS_WIDTH), Vec2(SLIDER_VIS_WIDTH * 2.0f, SLIDER_VIS_LENGTH + SLIDER_VIS_WIDTH), Vec4(0.4f, 0.4f, 0.4f, 1.0f));
	layer.submitQuad(finalPos, Vec2(SLIDER_VIS_WIDTH, SLIDER_VIS_LENGTH), Vec4(0, 0, 0, 1.0f));
	
	Vec4 knobColor;
	if (_highLight)
	{
		knobColor = SLIDER_KNOB_HIGHLIGHT_COLOR;
	}
	else
	{
		knobColor = SLIDER_KNOB_DEFAULT_COLOR;
	}
	
	layer.submitQuad(Vec2(finalPos.x - 0.25f * SLIDER_KNOB_WIDTH, knobVisPos), Vec2(SLIDER_KNOB_WIDTH, -SLIDER_KNOB_WIDTH), knobColor);
	
	
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << visValue;
	
	if (_showLabel)
	{
		_label.render(Vec2(finalPos.x - 0.02f, finalPos.y + SLIDER_VIS_LENGTH + 0.022f), layer);
		//layer.submitText(_label, Vec2(_pos.x - 0.02f, _pos.y + SLIDER_VIS_LENGTH + 0.022f), 0.2f);
	}
	Label valueLabel(stream.str(), SLIDER_LABEL_SCALE);
	valueLabel.render(Vec2(finalPos.x, finalPos.y - valueLabel.getScreenDimensions().y - 0.02f), layer);
	//layer.submitText(stream.str(), Vec2(_pos.x, _pos.y - 0.04f), 0.2f);
	ScreenElement::render(layer, finalPos);
}

void Slider::onHover(const Vec2& relativePos)
{
	_highLight = true;
}

void Slider::onClickHold(const Vec2& relativePos)
{
	setValueAbs(math::projectToCoordinates(_posStart.y + relativePos.y, _posStart.y, _posEnd.y, _rangeMin, _rangeMax));
}

void Slider::onExit(const Vec2& relativePos) 
{
	_highLight = false;
}

float Slider::projectToAbs(float zeroToOneRelative)
{
	return math::projectToCoordinates(zeroToOneRelative, 0, 1.0f, _rangeMin, _rangeMax);
}

float Slider::projectToZeroToOne(float valueAbs)
{
	return math::projectToCoordinates(valueAbs, _rangeMin, _rangeMax, 0, 1.0f);
}