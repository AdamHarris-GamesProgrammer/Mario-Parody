#include "ButtonComponent.h"
#include "Actor.h"
#include "Game.h"
#include "BlueSky.h"

ButtonComponent::ButtonComponent(class Actor* owner, int drawOrder /*= 100*/) : SpriteComponent(owner, drawOrder)
{
	mPosition.x = 0;
	mPosition.y = 0;

	SetTexture(mOwner->GetGame()->GetEngine()->GetTexture("Assets/Menus/Buttons (400x200).png"));
	mButtonWidth = GetTexWidth() / BUTTON_SPRITE_TOTAL;
	mButtonHeight = GetTexHeight();
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

ButtonComponent::~ButtonComponent()
{

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
				std::cout << "Mouse Over" << std::endl;
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Button Down" << std::endl;
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				std::cout << "Mouse Button Up" << std::endl;
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
