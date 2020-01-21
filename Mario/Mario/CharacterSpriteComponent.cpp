#include "CharacterSpriteComponent.h"
#include "Actor.h"

CharacterSpriteComponent::CharacterSpriteComponent(class Actor* owner, int drawOrder /*= 100*/, int texWidth, int texHeight) : AnimSpriteComponent(owner, drawOrder)
{
	mDestRect->w = texWidth;
	mDestRect->h = texHeight;
	mFlipState = SDL_FLIP_NONE;
}

void CharacterSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, mTexture, nullptr, mDestRect, 0.0f, nullptr, mFlipState);
}

void CharacterSpriteComponent::Update(float deltaTime)
{
	AnimSpriteComponent::Update(deltaTime);
}
