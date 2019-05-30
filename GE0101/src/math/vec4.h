#pragma once
#include <string>

class Vec4
{
public:

	float x;
	float y;
	float z;
	float w;

	Vec4(float x, float y, float z, float w);
	Vec4(float x, float y, float z);
	Vec4(float x, float y);
	Vec4();
	Vec4& set(float x, float y, float z, float w);
	Vec4& set(float x, float y, float z);
	Vec4& set(float x, float y);
	Vec4 getNormal() const;
	Vec4& normalize();
	float length() const;
	Vec4& add(float x, float y, float z, float w);
	Vec4& add(const Vec4& other);
	Vec4& sub(float x, float y, float z, float w);
	Vec4& sub(const Vec4& other);
	Vec4& mul(float value);
	Vec4 operator+(const Vec4& other) const;
	Vec4 operator-(const Vec4& other) const;
	Vec4 operator*(float value) const;
	Vec4& operator+=(const Vec4& other);
	Vec4& operator-=(const Vec4& other);
	Vec4& operator*=(float value);
	bool operator==(const Vec4& other) const;
	bool operator!=(const Vec4& other) const;
	bool operator>(float distance) const;
	bool operator<(float distance) const;
	bool operator>=(float distance) const;
	bool operator<=(float distance) const;
	Vec4 operator-() const;
	void print() const;
	std::string toString() const;
};