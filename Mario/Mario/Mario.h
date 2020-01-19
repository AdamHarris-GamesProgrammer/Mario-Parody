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

	Vector2 position;

	SDL_Rect* GetDestRect() { return mDestRect; }
	SDL_RendererFlip GetFlipState() { return mFlipState; }

	bool IsJumping() { return mJumping; }

	void CancelJump();

	void Jump();

	void AddGravity(float deltaTime);

private:
	float mMovementSpeed;

	SDL_Rect* mDestRect;
	SDL_RendererFlip mFlipState;

	class AnimSpriteComponent* asc;

	class CircleComponent* mCircle;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

};

