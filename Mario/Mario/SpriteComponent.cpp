#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder /*= 100*/) : Component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTexWidth(0), mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);

	mSrcRect = new SDL_Rect();
	mDestRect = new SDL_Rect();

	mSrcRect->x = 0;
	mSrcRect->y = 0;
	mSrcRect->w = mTexWidth;
	mSrcRect->h = mTexHeight;

	mDestRect->x = mOwner->GetPosition().x;
	mDestRect->y = mOwner->GetPosition().y;
	mDestRect->w = mTexWidth * mOwner->GetScale();
	mDestRect->h = mTexHeight * mOwner->GetScale();
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture) {
		mDestRect->x -= mOwner->GetGame()->mCamera.x;
		mDestRect->y -= mOwner->GetGame()->mCamera.y;
		SDL_RenderCopyEx(renderer,
			mTexture,
			mSrcRect,
			mDestRect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;

	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
