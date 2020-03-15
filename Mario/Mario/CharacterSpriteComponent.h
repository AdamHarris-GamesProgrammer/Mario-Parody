#pragma once
#include "AnimSpriteComponent.h"
#include "SDL.h"
class CharacterSpriteComponent : public AnimSpriteComponent
{
public:
	CharacterSpriteComponent(class Actor* owner, int drawOrder = 100, int texWidth = 26, int texHeight = 32); //Takes in an owner for the component to attach to, a draw order and then a texture width and height. (26 and 32) for these as that is Marios sprite details

	//Getter and Setter for the flip state variable
	SDL_RendererFlip GetFlipState() const { return mFlipState; }
	void SetRendererFlip(SDL_RendererFlip newValue) { mFlipState = newValue; }

	//Overrides the AnimSprite Components draw method
	void Draw(SDL_Renderer* renderer) override;

	//Overrides the AnimSprite Components update method
	void Update(float deltaTime) override;
private:
	//Holds the flip state for the character. This allows them to face left and right based on direction of travel
	SDL_RendererFlip mFlipState;
};

