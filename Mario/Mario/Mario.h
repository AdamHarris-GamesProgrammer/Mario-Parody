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


private:
	class CharacterSpriteComponent* csc;

	class CircleComponent* mCircle;

	bool bGrounded = true;
	bool bCanJump;
	bool bJumping;

	float mJumpForce;

	float mPlayerVelY;
	float mPlayerVelX;
	
	float mMovementSpeed = 5.0f;
};

