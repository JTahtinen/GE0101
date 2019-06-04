#include "Vec3.h"
#include <iostream>
#include "math.h"

Vec3::Vec3(float x, float y, float z)
	:
	x(x)
	, y(y)
	, z(z)
{
}



Vec3::Vec3(float x, float y)
	: Vec3(x, y, 0)
{
}

Vec3::Vec3()
	: Vec3(0.0f, 0.0f)
{
}


Vec3& Vec3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vec3& Vec3::set(float x, float y)
{
	return set(x, y, 0);
}

Vec3 Vec3::getNormal() const
{
	float len = length();
	return Vec3(x / len, y / len, z / len);
}

Vec3& Vec3::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
	return *this;
}

float Vec3::length() const
{
	return sqrtf(x * x + y * y + z * z);
}

Vec3& Vec3::add(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
	return *this;
}

Vec3& Vec3::add(const Vec3& other)
{
	return add(other.x, other.y, other.z);
}

Vec3& Vec3::sub(float x, float y, float z)
{
	this->x -= x;
	this->y -= y;
	this->z -= z;
	return *this;
}
Vec3& Vec3::Vec3::sub(const Vec3& other)
{
	return sub(other.x, other.y, other.z);
}
Vec3& Vec3::mul(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}
Vec3 Vec3::operator*(float value) const
{
	return Vec3(x * value, y * value, z * value);
}


Vec3& Vec3::operator+=(const Vec3& other)
{
	return add(other);
}

Vec3& Vec3::operator-=(const Vec3& other)
{
	return sub(other);
}

Vec3& Vec3::operator*=(float value)
{
	return mul(value);
}
bool Vec3::operator==(const Vec3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vec3::operator!=(const Vec3& other) const
{
	return !(*this == other);
}
bool Vec3::operator>(float distance) const
{
	return (length() > distance);
}
bool Vec3::operator<(float distance) const
{
	return (length() < distance);
}

bool Vec3::operator>=(float distance) const
{
	return (length() >= distance);
}

bool Vec3::operator<=(float distance) const
{
	return (length() <= distance);
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

void Vec3::print() const
{
	std::cout << toString() << std::endl;
}

std::string Vec3::toString() const
{
	return std::string("Vec3: [X: " + std::to_string(x) +
		", Y: " + std::to_string(y) +
		", Z: " + std::to_string(z) + "]");
}