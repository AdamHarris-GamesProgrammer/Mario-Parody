#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder /*= 10*/) : SpriteComponent(owner, drawOrder), mScrollSpeed(0.0f) //Initializes all of the variables to a suitable default value
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	//Calls the update method for the base SpriteComponent class
	SpriteComponent::Update(deltaTime);
	
	//Cycles through all of the background texture objects in the mBGTextures vector
	for (auto& bg : mBGTextures) {
		//Sets the offset equal to how fast it should scroll times by delta time
		bg.mOffset.x += mScrollSpeed * deltaTime;

		//moves the background texture to the right hand side of the screen once it has scrolled all the way to the left
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{

		SDL_Rect destRect;
		//Sets the width and height of the dest rect equal to the screen size 
		destRect.w = static_cast<int>(mScreenSize.x);
		destRect.h = static_cast<int>(mScreenSize.y);
		//Centers the textures into the middle of the screen
		destRect.x = static_cast<int>(mOwner->GetPosition().x - destRect.w / 2 + bg.mOffset.x);
		destRect.y = static_cast<int>(mOwner->GetPosition().y - destRect.h / 2 + bg.mOffset.y);

		// Draw the background texture
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&destRect
		);
	}
}

void BGSpriteComponent::SetBGTexture(const std::vector<SDL_Texture*>& textures)
{
	//this count variable is incremented for each background added
	int count = 0;
	for (auto tex : textures) {
		//Creates a temp BGTexture object
		BGTexture temp;

		//Sets the texture
		temp.mTexture = tex;

		//Sets the x offset
		temp.mOffset.x = count * mScreenSize.x;

		//Sets the y offset
		temp.mOffset.y = 0;

		//Places the temp BGTexture into the mBGTextures vector
		mBGTextures.emplace_back(temp);

		//Increments the count variable
		count++;
	}
}
