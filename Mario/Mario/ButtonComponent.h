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

	void SetPosition(Vector2 position);
	void HandleEvent(SDL_Event* e);

	void Draw(SDL_Renderer* renderer) override;

	enum ButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION,
		BUTTON_SPRITE_MOUSE_DOWN,
		BUTTON_SPRITE_MOUSE_UP,
		BUTTON_SPRITE_TOTAL = 4
	};

	int GetButtonHeight() const { return mButtonHeight; }
	int GetButtonWidth() const { return mButtonWidth; }

	void SetButtonHeight(int newValue) { mButtonWidth = newValue; }
	void SetButtonWidth(int newValue) { mButtonHeight = newValue; }

	void SetButtonText(std::string newText) { mButtonTextComponent->SetText(newText); }
	void SetButtonTextSize(int newValue) { mButtonTextComponent->SetTextSize(newValue); }
	void SetButtonTextPosition(Vector2 newPosition) { mButtonTextActor->SetPosition(newPosition); }

	void SetTexture(SDL_Texture* texture) override;

	ButtonSprite mCurrentSprite;

	virtual void OnMouseOver();
	virtual void OnMouseButtonDown();
	virtual void OnMouseButtonUp();


	Actor* mButtonTextActor = nullptr;
	class TextSpriteComponent* mButtonTextComponent = nullptr;
private:
	int mButtonWidth;
	int mButtonHeight;
	const int totalNumberOfButtons = 4;

	Vector2 mPosition;



};

