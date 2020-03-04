#pragma once
#include "../graphics/layer.h"
#include "../math/vec2.h"
#include <string>
#include "../graphics/screenelement.h"
#include "../graphics/label.h"

class Slider : public ScreenElement
{
	Vec2						_pos;
	float						_rangeMin;
	float						_rangeMax;
	float						_valueAbs;
	Label						_label;
	float*						_tiedValue;
	bool						_showLabel;
	bool						_highLight;
public:
	Slider(const float rangeMin, const float rangeMax, const float initValue, const std::string& label, const Vec2& pos);
	Slider(const float rangeMin, const float rangeMax, float* tiedValue, const std::string& label, const Vec2& pos);
	void setValueAbs(float value);
	void setValueZeroToOne(float value);
	void slideByAbs(float value);
	void slideByZeroToOne(float value);
	void toggleLabel();
	void render(Layer& layer) const;
	float getValue() const;

	virtual void onHover(const Vec2& relativePos) override;
	virtual void onClickHold(const Vec2& relativePos) override;
	virtual void onExit(const Vec2& relativePos) override;
	virtual inline const std::string getLabel() const override { return _label.str(); }
private:
	float projectToAbs(float zeroToOneRelative);
	float projectToZeroToOne(float valueAbs);
};