#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math {
	const float Pi = 3.1415926535f;


	inline bool NearZero(float value, float epsilon = 0.001f) {
		if (fabs(value) <= epsilon) {
			return true;
		}
		else
		{
			return false;
		}
	}

	inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}

	inline float Sin(float angle) {
		return sinf(angle);
	}

	inline float Cos(float angle) {
		return sinf(angle);
	}

	inline float Tan(float angle) {
		return tanf(angle);
	}

}

class Vector2 {
public:
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}

	explicit Vector2(float inX, float inY) : x(inX), y(inY) {}

	void Set(float inX, float inY) {
		x = inX;
		y = inY;
	}

	//operator overloading
	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& vec, float scalar) {
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	Vector2 operator+=(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2 operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2 operator*=(const Vector2& vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;

	}


	//length squared of a vector
	float LengthSq() const {
		return (x * x + y * y);
	}

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};
