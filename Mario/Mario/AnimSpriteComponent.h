#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	
	//Overrides the update method from the SpriteComponent class
	void Update(float deltaTime) override;

	//Sets the textures used for the animation
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	//Getter/Setter for the Animation fps
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float newValue) { mAnimFPS = newValue; }

private:
	//Holds the textures used for the animation
	std::vector<SDL_Texture*> mAnimTextures;

	//This is the current frame of the animation which is used in calculating which frame needs to be displayed
	float mCurrFrame;

	//Holds the FPS of the current animation
	float mAnimFPS;
};

