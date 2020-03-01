#pragma once
#include "SpriteComponent.h"
#include "Math.h"

class ButtonComponent : public SpriteComponent
{
public:
	ButtonComponent(class Actor* owner, int drawOrder = 500);
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


	ButtonSprite mCurrentSprite;
private:
	int mButtonWidth;
	int mButtonHeight;
	const int totalNumberOfButtons = 4;

	Vector2 mPosition;



};

