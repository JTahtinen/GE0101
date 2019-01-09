#pragma once

class Vec2
{
public:
	float x{0};
	float y{0};

	Vec2() = default;
	Vec2(float x, float y);
	Vec2& set(float x, float y);
	Vec2 getNormal() const;
	Vec2& normalize();
	float length() const;
	Vec2& add(float x, float y);
	Vec2& add(const Vec2& other);
	Vec2& sub(float x, float y);
	Vec2& sub(const Vec2& other);
	Vec2& mul(float value);
	float dot(const Vec2& other);
	Vec2 operator+(const Vec2& other);
	Vec2 operator-(const Vec2& other);
	Vec2 operator*(float value);
	float operator*(const Vec2& other);
	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);
	Vec2& operator*=(float value);
	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);

};