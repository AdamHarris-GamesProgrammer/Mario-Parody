#include "ButtonComponent.h"
#include "Actor.h"
#include "Game.h"
#include "BlueSky.h"
#include "TextSpriteComponent.h"

ButtonComponent::ButtonComponent(class Actor* owner, int drawOrder /*= 100*/) : SpriteComponent(owner, drawOrder)
{
	mPosition.x = 0;
	mPosition.y = 0;

	mButtonWidth = GetTexWidth() / BUTTON_SPRITE_TOTAL;
	mButtonHeight = GetTexHeight();
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	mButtonTextActor = new Actor(mOwner->GetGame());
	mButtonTextComponent = new TextSpriteComponent(mButtonTextActor, 160);
}

ButtonComponent::~ButtonComponent()
{
	delete mButtonTextComponent;
	mButtonTextComponent = NULL;
}

void ButtonComponent::SetPosition(Vector2 position)
{
	mPosition = position;
}

void ButtonComponent::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

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

		if (!inside) {
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
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
	SDL_Rect* srcRect = new SDL_Rect{ mButtonWidth * mCurrentSprite, 0, mButtonWidth, mButtonHeight };
	SDL_Rect* destRect = new SDL_Rect{ (int)mPosition.x, (int)mPosition.y, mButtonWidth, mButtonHeight };

	SDL_RenderCopy(renderer, mTexture, srcRect, destRect);
}

void ButtonComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;

	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	mButtonWidth = mTexWidth / BUTTON_SPRITE_TOTAL;
	mButtonHeight = mTexHeight;
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
