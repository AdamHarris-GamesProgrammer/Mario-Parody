#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner); //Sets the owner of the CircleComponent so it can attach to an object

	//Getter/Setter for the radius
	void SetRadius(float newValue) { mRadius = newValue; }
	float GetRadius() const { return mRadius; }

	//Gets the center of the circle (Used for collision checking
	const Vector2& GetCenter() const;

private:
	//Holds the radius of the circle
	float mRadius;
};

//Checks to see if there is a intersection between two circles. Written outside of the class so it can be called without a CircleComponent object
bool Intersect(const CircleComponent& a, const CircleComponent& b);

