#include "ReturnToMenuButton.h"
#include "Game.h"

ReturnToMenuButton::ReturnToMenuButton(class Game* game, Vector2 position) : Actor(game), ButtonComponent(this)
{
	//Sets the button texture
	SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);

	//Sets the button text details
	SetButtonText("Return to Main Menu");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight() / 2)));
}

void ReturnToMenuButton::OnMouseButtonDown()
{
	//Calls the ReturnToMainMenu method in the game class
	mGame->ReturnToMainMenu();
}
