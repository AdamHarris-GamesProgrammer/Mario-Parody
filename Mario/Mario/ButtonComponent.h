#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <string>
#include <iostream>
#include "TextSpriteComponent.h"
#include "Actor.h"

class ButtonComponent : public SpriteComponent
{
public:
	ButtonComponent(class Actor* owner, int drawOrder = 150);
	~ButtonComponent();

	//Sets the button positon
	void SetPosition(Vector2 position);

	//Handles the events for the button (Mosue Over, Button Down, Button Up)
	void HandleEvent(SDL_Event* e);

	//Overrides the draw method in the SpriteComponent Class
	void Draw(SDL_Renderer* renderer) override;
	
	//Holds each of the possible sprites for the button
	enum ButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION,
		BUTTON_SPRITE_MOUSE_DOWN,
		BUTTON_SPRITE_MOUSE_UP,
		BUTTON_SPRITE_TOTAL = 4
	};

	//Getters for the button dimensions
	int GetButtonHeight() const { return mButtonHeight; }
	int GetButtonWidth() const { return mButtonWidth; }

	//Setters for the button dimensions
	void SetButtonHeight(int newValue) { mButtonWidth = newValue; }
	void SetButtonWidth(int newValue) { mButtonHeight = newValue; }

	//Setters for the button text values
	void SetButtonText(std::string newText) { mButtonTextComponent->SetText(newText); }
	void SetButtonTextSize(int newValue) { mButtonTextComponent->SetTextSize(newValue); }
	void SetButtonTextPosition(Vector2 newPosition) { mButtonTextActor->SetPosition(newPosition); }

	//Sets the buttons textures
	void SetTexture(SDL_Texture* texture) override;

	//Holds the current Sprite being used
	ButtonSprite mCurrentSprite;

	//Virtual functions for each type of event
	virtual void OnMouseOver();
	virtual void OnMouseButtonDown();
	virtual void OnMouseButtonUp();

	//Actor for the button text
	Actor* mButtonTextActor = nullptr;

	//Text component for the button
	class TextSpriteComponent* mButtonTextComponent = nullptr;
private:
	//Button dimensions
	int mButtonWidth;
	int mButtonHeight;

	//Holds the number of button states
	const int totalNumberOfButtons = 4;

	//Holds the position of the button
	Vector2 mPosition;
};

