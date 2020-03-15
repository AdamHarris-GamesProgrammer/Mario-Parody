#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	//Constructor for the background sprite component takes a lower draw order as it should always be drawn towards the back
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	//Overrides the Draw and Update methods from the Sprite Component
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	//Sets the background textures to the passed in texture 
	void SetBGTexture(const std::vector<SDL_Texture*>& textures);

	//Sets the screen size
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }

	//Getter/Setter for the scroll speed variable
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }

private:
	//This struct holds a texture and a offset for each background object
	struct BGTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	//Holds a vector of BGTexture objects used for rendering
	std::vector<BGTexture> mBGTextures;
	//Holds the screen size
	Vector2 mScreenSize;

	//Holds the scroll speed
	float mScrollSpeed;
};

