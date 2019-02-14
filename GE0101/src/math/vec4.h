#pragma once

class Vec4
{
public:

	float x;
	float y;
	float z;
	float w;

	float& r{ x };
	float& g{ y };
	float& b{ z };
	float& a{ w };

	Vec4(float x, float y, float z, float w);
	Vec4(float x, float y, float z);
	Vec4();
};