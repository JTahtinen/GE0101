#pragma once
#include <string>

class Vec3
{
public:

	float x;
	float y;
	float z;

	Vec3(float x, float y, float z);
	Vec3(float x, float y);
	Vec3();
	Vec3& set(float x, float y, float z);
	Vec3& set(float x, float y);
	Vec3 getNormal() const;
	Vec3& normalize();
	float length() const;
	Vec3& add(float x, float y, float z);
	Vec3& add(const Vec3& other);
	Vec3& sub(float x, float y, float z);
	Vec3& sub(const Vec3& other);
	Vec3& mul(float value);
	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(float value) const;
	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(float value);
	bool operator==(const Vec3& other) const;
	bool operator!=(const Vec3& other) const;
	bool operator>(float distance) const;
	bool operator<(float distance) const;
	bool operator>=(float distance) const;
	bool operator<=(float distance) const;
	Vec3 operator-() const;
	void print() const;
	std::string toString() const;
};