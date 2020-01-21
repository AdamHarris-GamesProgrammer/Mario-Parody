#pragma once
#include "AnimSpriteComponent.h"
#include "SDL.h"
class CharacterSpriteComponent : public AnimSpriteComponent
{
public:
	CharacterSpriteComponent(class Actor* owner, int drawOrder = 100, int texWidth = 32, int texHeight = 48);

	SDL_RendererFlip GetFlipState() const { return mFlipState; }
	void SetRendererFlip(SDL_RendererFlip newValue) { mFlipState = newValue; }

	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltaTime) override;
private:
	SDL_RendererFlip mFlipState;
};

