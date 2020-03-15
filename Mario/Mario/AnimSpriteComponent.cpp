#include "AnimSpriteComponent.h"
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder /*= 100*/): SpriteComponent(owner, drawOrder), mCurrFrame(0.0f), mAnimFPS(24.0f) //Sets default values for each member variable 
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	//Calls the update function of the base class
	SpriteComponent::Update(deltaTime);

	//Checks that there are animations in the anim vector
	if (mAnimTextures.size() > 0) {
		//Sets the current frame based on FPS times by delta time
		mCurrFrame += mAnimFPS * deltaTime;

		//Sets the current frame back to 0 when there are no more frames to be played
		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}

		//Calls the set texture method in the Sprite component which changes which texture will be drawn
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	//Checks to see if the anim textures have changed from the current ones, stops a animation being stuck on a single frame
	if (mAnimTextures != textures) {
		//Sets the textures
		mAnimTextures = textures;
		if (mAnimTextures.size() > 0) {
			//This resets the texture shown and the current frame variables
			mCurrFrame = 0.0f;
			SetTexture(mAnimTextures[0]);
		}
	}
}
