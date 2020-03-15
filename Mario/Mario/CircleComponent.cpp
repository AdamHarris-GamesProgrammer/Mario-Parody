#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner) : Component(owner), mRadius(0.0f) {} //Sets default values

//Returns the center of the circle, based on the actor position
const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	//Gets the center of both the circles
	Vector2 diff = a.GetCenter() - b.GetCenter();

	//Gets the distance squared of the circles
	float distSq = diff.LengthSq();

	//Squares the sum of the two radii added together
	float radiiSq = a.GetRadius() + b.GetRadius();

	//Squares the radii
	radiiSq *= radiiSq;

	//if distance squared is less than radii squared thena  collision must have occured
	return distSq <= radiiSq;
}
