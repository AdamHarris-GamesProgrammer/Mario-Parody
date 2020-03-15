#include "ButtonComponent.h"
#include "Actor.h"
#include "Game.h"
#include "BlueSky.h"
#include "TextSpriteComponent.h"

ButtonComponent::ButtonComponent(class Actor* owner, int drawOrder /*= 100*/) : SpriteComponent(owner, drawOrder) 
{
	mPosition.x = 0;
	mPosition.y = 0;
	
	//Sets up the button dimensions
	mButtonWidth = GetTexWidth() / BUTTON_SPRITE_TOTAL;
	mButtonHeight = GetTexHeight();

	//default sprite for the buttons is when the mouse is outside of the button
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	//Initializes button text actor and component objects
	mButtonTextActor = new Actor(mOwner->GetGame());
	mButtonTextComponent = new TextSpriteComponent(mButtonTextActor, 160);
}

ButtonComponent::~ButtonComponent()
{
	//cleans up text related memory
	delete mButtonTextComponent;
	mButtonTextComponent = NULL;
	delete mButtonTextActor;
	mButtonTextActor = NULL;
}

void ButtonComponent::SetPosition(Vector2 position)
{
	//Sets the position
	mPosition = position;
}

void ButtonComponent::HandleEvent(SDL_Event* e)
{
	//if mouse has any events this frame
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		//Holds the mouse's X and Y Position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//checks if the mouse is inside the button
		bool inside = true;
		if (x < mPosition.x) {
			inside = false;
		}
		else if (x > mPosition.x + mButtonWidth) {
			inside = false;
		}
		else if (y < mPosition.y) {
			inside = false;
		}
		else if (y > mPosition.y + mButtonHeight) {
			inside = false;
		}

		//if the mouse is not inside then set the sprite to BUTTON_SPRITE_MOUSE_OUT
		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
				//Sets the button sprite to the required one
			case SDL_MOUSEMOTION:
				OnMouseOver();
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				OnMouseButtonDown();
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				OnMouseButtonUp();
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void ButtonComponent::Draw(SDL_Renderer* renderer)
{
	//Creates a src and dest rect object that correspond to the needed sprite for the button
	SDL_Rect* srcRect = new SDL_Rect{ mButtonWidth * mCurrentSprite, 0, mButtonWidth, mButtonHeight };
	SDL_Rect* destRect = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, mButtonWidth, mButtonHeight };

	SDL_RenderCopy(renderer, mTexture, srcRect, destRect);
}

void ButtonComponent::SetTexture(SDL_Texture* texture)
{
	//Sets the texture
	mTexture = texture;

	//sets the texture width and height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);

	//sets button dimensions
	mButtonWidth = mTexWidth / BUTTON_SPRITE_TOTAL;
	mButtonHeight = mTexHeight;

	//sets the position of the button text
	SetButtonTextPosition(Vector2(mPosition.x + mButtonWidth / 2, mPosition.y + mButtonHeight / 2));
}

void ButtonComponent::OnMouseOver()
{
}

void ButtonComponent::OnMouseButtonDown()
{
}

void ButtonComponent::OnMouseButtonUp()
{
}
