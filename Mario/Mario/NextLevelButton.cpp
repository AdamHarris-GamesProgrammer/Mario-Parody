#include "NextLevelButton.h"
#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "SDL_pixels.h"
#include "Math.h"

NextLevelButton::NextLevelButton(class Game* game, Vector2 position) : Actor(game), ButtonComponent(this)
{
	//Sets the button texutre
	SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);
	
	//Sets the text, text colour, and positon
	SetButtonText("Next Level");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight()/2)));
}

void NextLevelButton::OnMouseButtonDown()
{
	//Calls the next level method in the game class
	mGame->NextLevel();
}
