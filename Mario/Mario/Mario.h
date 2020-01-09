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

	void Draw();

	Vector2 gravity = Vector2(0.0f, -8.0f);
	Vector2 velocity = Vector2(15.0f, 15.0f);
	Vector2 position;

	SDL_Rect* GetSourceRect() { return mSrcRect; }
	SDL_RendererFlip GetFlipState() { return mFlipState; }

	bool IsJumping() { return mJumping; }

	void CancelJump();

	void Jump();

	void AddGravity(float deltaTime);

private:
	float mMovementSpeed;

	SDL_Rect* mSrcRect;
	SDL_RendererFlip mFlipState;

	class AnimSpriteComponent* asc;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

};

