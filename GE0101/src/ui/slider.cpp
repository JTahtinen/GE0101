#include "slider.h"
#include "../math/math.h"
#include <sstream>
#include <iomanip>
#include "../defs.h"

Slider::Slider(const float rangeMin, const float rangeMax, const float initValue)
	: _rangeMin(rangeMin)
	, _rangeMax(rangeMax)
	, _valueAbs(initValue)
	, _tiedValue(nullptr)
{
}

Slider::Slider(const float rangeMin, const float rangeMax, float* tiedValue)
	: Slider(rangeMin, rangeMax, 0.0f)
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
	else if (_valueAbs < 0.0f)
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


float Slider::getValue() const
{
	return _valueAbs;
}

void Slider::render(Layer& layer, const Vec2& pos) const
{
	static float sliderVisLength = 0.25f;
	static float knobThickness = 0.04f;  //snort
	float knobVisPos = (pos.y - sliderVisLength) + math::projectToCoordinates(_valueAbs, _rangeMin, _rangeMax, 0, sliderVisLength) + knobThickness * 0.5f;
	layer.submitQuad(pos, Vec2(0.02f, sliderVisLength), Vec4(0.2f, 0.2f, 0.2f, 1.0f));
	layer.submitQuad(Vec2(pos.x - 0.25f * knobThickness, knobVisPos), Vec2(knobThickness, knobThickness), Vec4(0.8f, 0.8f, 0.8f, 0.5f));
	
	
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << _valueAbs;
	
	layer.submitText(stream.str(), Vec2(pos.x, pos.y - sliderVisLength - 0.02f), 0.2f);
}

float Slider::projectToAbs(float zeroToOneRelative)
{
	return math::projectToCoordinates(zeroToOneRelative, 0, 1.0f, _rangeMin, _rangeMax);
}

float Slider::projectToZeroToOne(float valueAbs)
{
	return math::projectToCoordinates(valueAbs, _rangeMin, _rangeMax, 0, 1.0f);
}