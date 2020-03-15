#include "PlayButton.h"
#include "Game.h"

PlayButton::PlayButton(class Game* game, Vector2 position) : ButtonComponent(this), Actor(game)
{
	//Sets the button texture
	SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);

	//Sets up the button text details
	SetButtonText("Play Game");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight() / 2)));
}

void PlayButton::OnMouseButtonDown()
{
	//Calls the PlayFirstLevel button in the game class
	mGame->PlayFirstLevel();
}

