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

	void ChangePlayerTile(Vector2 position);

	bool GetDead() const { return bDead; }
	void SetDead(bool newValue) { bDead = newValue; }

	void SetPlayerPosition(const Vector2& newValue);

private:
	class CharacterSpriteComponent* csc;

	class CircleComponent* mCircle;

	bool bGrounded = true;
	bool bCanJump;
	bool bJumping;

	bool bDead = false;

	float mJumpForce;

	float mPlayerVelX;
	
	float mMovementSpeed = 5.0f;

	void CollisionChecks();
	void Jump(Vector2& newPos, float deltaTime);



};

