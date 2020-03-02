#include "NextLevelButton.h"
#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "SDL_pixels.h"
#include "Math.h"

NextLevelButton::NextLevelButton(class Game* game, Vector2 position) : Actor(game), ButtonComponent(this)
{
	SetTexture(mOwner->GetGame()->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);

	mButtonTextActor = new Actor(game);
	mButtonTextActor->SetPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y  + (GetButtonHeight() /2)));

	mButtonTextComponent = new TextSpriteComponent(mButtonTextActor);
	mButtonTextComponent->SetText("Next Level");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
}

NextLevelButton::~NextLevelButton()
{

}

void NextLevelButton::OnMouseButtonDown()
{
	mOwner->GetGame()->NextLevel();
}
