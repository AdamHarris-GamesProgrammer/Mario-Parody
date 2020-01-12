#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float newValue) { mRadius = newValue; }
	float GetRadius() const { return mRadius; }

	const Vector2& GetCenter() const;

private:
	float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

