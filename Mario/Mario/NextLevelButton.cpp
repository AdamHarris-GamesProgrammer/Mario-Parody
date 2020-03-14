#include "NextLevelButton.h"
#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "SDL_pixels.h"
#include "Math.h"

NextLevelButton::NextLevelButton(class Game* game, Vector2 position) : Actor(game), ButtonComponent(this)
{
	SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);
	
	SetButtonText("Next Level");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight()/2)));
}

void NextLevelButton::OnMouseButtonDown()
{
	mGame->NextLevel();
}
