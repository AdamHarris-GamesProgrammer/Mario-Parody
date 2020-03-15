#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math {
	//Pi to 10 decimal places
	const float Pi = 3.1415926535f;

	//Sees if a value is near zero
	inline bool NearZero(float value, float epsilon = 0.001f) {
		if (fabs(value) <= epsilon) {
			return true;
		}
		else
		{
			return false;
		}
	}

	//Converts radians to degrees
	inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}

	//just wrapper methods for Sin, Cos and Tan
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

//Vector2 class which holds operator overloading and a couple of helper methods
class Vector2 {
public:
	float x, y;

	//Sets a default constructor
	Vector2() : x(0.0f), y(0.0f) {}

	//This constructor requires explicit values for X and Y
	explicit Vector2(float inX, float inY) : x(inX), y(inY) {}


	//Sets the X and Y values 
	void Set(float inX, float inY) {
		x = inX;
		y = inY;
	}

	//overloads the Addition operator
	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}

	//overloads the subtraction operator
	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}

	//overloads the multiplication operator
	friend Vector2 operator*(const Vector2& vec, float scalar) {
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//overrides the compound addition operator
	Vector2 operator+=(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}

	//overrides the compound subtraction operator
	Vector2 operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	//overrides the compound multiplication operator
	Vector2 operator*=(const Vector2& vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;

	}


	//length squared of a vector
	float LengthSq() const {
		return (x * x + y * y);
	}

	//Vectors that can be useful for some maths
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};
