#pragma once
#include "../graphics/layer.h"
#include "../math/vec2.h"
#include <string>

class Slider
{
	float						_rangeMin;
	float						_rangeMax;
	float						_valueAbs;
	std::string					_label;
	float*						_tiedValue;
	bool						_showLabel;
public:
	Slider(const float rangeMin, const float rangeMax, const float initValue, const std::string& label);
	Slider(const float rangeMin, const float rangeMax, float* tiedValue, const std::string& label);
	void setValueAbs(float value);
	void setValueZeroToOne(float value);
	void slideByAbs(float value);
	void slideByZeroToOne(float value);
	void toggleLabel();
	void render(Layer& layer, const Vec2& pos) const;
	float getValue() const;
private:
	float projectToAbs(float zeroToOneRelative);
	float projectToZeroToOne(float valueAbs);
};