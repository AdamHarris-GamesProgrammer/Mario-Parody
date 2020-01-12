#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(class Actor* owner, int updateOrder /*= 10*/) : Component(owner, updateOrder), mAngularSpeed(0.0f), mForwardSpeed(0.0f)
{

}

void MovementComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed)) {
		float rotation = mOwner->GetRotation();
		rotation = mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
	}

	if (!Math::NearZero(mForwardSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		mOwner->SetPosition(pos);
	}
}
