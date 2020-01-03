#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math {
	const float Pi = 3.1415926535f;

	inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
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

	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& vec, float scalar) {
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};
