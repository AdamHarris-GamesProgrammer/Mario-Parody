#pragma once
#include "Component.h"

class MovementComponent : public Component
{
public:
	MovementComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float newValue) { mAngularSpeed = newValue; }
	void SetForwardSpeed(float newValue) { mForwardSpeed = newValue; }

private:
	float mAngularSpeed;

	float mForwardSpeed;
};

