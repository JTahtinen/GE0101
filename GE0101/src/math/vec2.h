#pragma once

class Vec2
{
public:
	float x{0};
	float y{0};

	Vec2() = default;
	Vec2(float x, float y);
	Vec2 getNormal() const;
	Vec2 normalize();
	float length() const;
	void add(float x, float y);
	void add(const Vec2& other);
	void sub(float x, float y);
	void sub(const Vec2& other);
	void mul(float value);
	float dot(const Vec2& other);

};