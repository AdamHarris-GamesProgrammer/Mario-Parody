#pragma once
#include "Actor.h"
#include "SDL.h"

class Mario : public Actor
{
public:
	Mario(class Game* game);
	void UpdateActor(float deltaTime) override;
	void HandleEvents(const uint8_t* state);
	float GetMovementSpeed() const { return mMovementSpeed; }

	void Draw();

	SDL_Rect* GetSourceRect() { return mSrcRect; }
	SDL_RendererFlip GetFlipState() { return mFlipState; }

private:
	float mMovementSpeed;

	SDL_Rect* mSrcRect;
	SDL_RendererFlip mFlipState;

	class AnimSpriteComponent* asc;
};

