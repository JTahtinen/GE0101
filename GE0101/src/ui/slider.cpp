#include "slider.h"
#include "../math/math.h"
#include <sstream>
#include <iomanip>
#include "../defs.h"

Slider::Slider(const float rangeMin, const float rangeMax, const float initValue, const std::string& label)
	: _rangeMin(rangeMin)
	, _rangeMax(rangeMax)
	, _valueAbs(initValue)
	, _label(label)
	, _tiedValue(nullptr)
	, _showLabel(true)
{
}

Slider::Slider(const float rangeMin, const float rangeMax, float* tiedValue, const std::string& label)
	: Slider(rangeMin, rangeMax, 0.0f, label)
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
	static float sliderVisLength = 0.25f;
	static float sliderVisThickness = 0.02f;
	static float knobThickness = 0.04f;  //snort
	float visValue = 0;
	if (_valueAbs <= _rangeMin)
	{
		visValue = _rangeMin; // This is used to fix a bug where the slider might display negative 0
	}
	else
	{
		visValue = _valueAbs;
	}
	float knobVisPos = pos.y + math::projectToCoordinates(visValue, _rangeMin, _rangeMax, 0, sliderVisLength) + knobThickness * 0.5f;
	layer.submitQuad(Vec2(pos.x - 0.5f * sliderVisThickness, pos.y - 0.5f * sliderVisThickness), Vec2(sliderVisThickness * 2.0f, sliderVisLength + sliderVisThickness), Vec4(0.4f, 0.4f, 0.4f, 1.0f));
	layer.submitQuad(pos, Vec2(sliderVisThickness, sliderVisLength), Vec4(0, 0, 0, 1.0f));
	layer.submitQuad(Vec2(pos.x - 0.25f * knobThickness, knobVisPos), Vec2(knobThickness, -knobThickness), Vec4(0.8f, 0.8f, 0.8f, 0.8f));
	
	
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << visValue;
	
	if (_showLabel)
	{
		layer.submitText(_label, Vec2(pos.x - 0.02f, pos.y + sliderVisLength + 0.022f), 0.2f);
	}
	layer.submitText(stream.str(), Vec2(pos.x, pos.y - 0.04f), 0.2f);
}

float Slider::projectToAbs(float zeroToOneRelative)
{
	return math::projectToCoordinates(zeroToOneRelative, 0, 1.0f, _rangeMin, _rangeMax);
}

float Slider::projectToZeroToOne(float valueAbs)
{
	return math::projectToCoordinates(valueAbs, _rangeMin, _rangeMax, 0, 1.0f);
}