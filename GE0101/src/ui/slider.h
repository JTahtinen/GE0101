#pragma once
#include "../graphics/layer.h"
#include "../math/vec2.h"

class Slider
{
	float						_rangeMin;
	float						_rangeMax;
	float						_valueAbs;
	float*						_tiedValue;
public:
	Slider(const float rangeMin, const float rangeMax, const float initValue);
	Slider(const float rangeMin, const float rangeMax, float* tiedValue);
	void setValueAbs(float value);
	void setValueZeroToOne(float value);
	void slideByAbs(float value);
	void slideByZeroToOne(float value);
	void render(Layer& layer, const Vec2& pos) const;
	float getValue() const;
private:
	float projectToAbs(float zeroToOneRelative);
	float projectToZeroToOne(float valueAbs);
};