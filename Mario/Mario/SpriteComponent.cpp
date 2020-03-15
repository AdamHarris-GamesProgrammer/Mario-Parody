#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder /*= 100*/) : Component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTexWidth(0), mTexHeight(0) //Sets default values
{
	//Adds sprite to the game
	mOwner->GetGame()->GetEngine()->AddSprite(this);

	//Sets the src and dest rect variables to have sensible values
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
	//deletes the dest and src rect
	delete mDestRect;
	delete mSrcRect;

	//removes the sprite
	mOwner->GetGame()->GetEngine()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	//if a texture is found
	if (mTexture) {
		//Moves the sprite according to the camera position
		mDestRect->x -= mOwner->GetGame()->mCamera.x;
		mDestRect->y -= mOwner->GetGame()->mCamera.y;

		//sets the width and height
		mDestRect->w = mTexWidth;
		mDestRect->h = mTexHeight;

		//Renders the sprite
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
	//Sets the texture
	mTexture = texture;

	//sets the texture width and height using the Query method 
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
