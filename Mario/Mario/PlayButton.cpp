#include "PlayButton.h"
#include "Game.h"

PlayButton::PlayButton(class Game* game, Vector2 position) : ButtonComponent(this), Actor(game)
{
	SetTexture(mOwner->GetGame()->GetEngine()->GetTexture("Assets/Menus/Buttons (300x75).png"));
	ButtonComponent::SetPosition(position);

	SetButtonText("Play Game");
	SDL_Color color = SDL_Color();
	color = { 0,0,0,255 };
	mButtonTextComponent->SetTextColor(color);
	SetButtonTextPosition(Vector2(position.x + (GetButtonWidth() / 2), position.y + (GetButtonHeight() / 2)));
}

PlayButton::~PlayButton()
{

}

void PlayButton::OnMouseButtonDown()
{
	mOwner->GetGame()->PlayFirstLevel();
}

void PlayButton::OnMouseOver()
{
	std::cout << "Over Play Game Button!" << std::endl;
}
