#include "RetryButton.h"
#include "Game.h"

RetryButton::RetryButton(class Game* game, Vector2 position) : Actor(game), ButtonComponent(this)
{
	SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);

	SetButtonText("Retry Level");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight() / 2)));
}

void RetryButton::OnMouseButtonDown()
{
	mGame->RetryLevel();
}
