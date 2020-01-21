#pragma once
#include "Actor.h"
#include "SDL.h"
#include "Constants.h"

class Mario : public Actor
{
public:
	Mario(class Game* game);
	void UpdateActor(float deltaTime) override;
	void HandleEvents(const uint8_t* state);
	float GetMovementSpeed() const { return mMovementSpeed; }

	Vector2 position;

	bool IsJumping() { return mJumping; }

	void CancelJump();

	void Jump();

	void AddGravity(float deltaTime);

private:
	float mMovementSpeed;

	class CharacterSpriteComponent* csc;

	class CircleComponent* mCircle;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

};

