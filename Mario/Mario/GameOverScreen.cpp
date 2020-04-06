#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(class Game* game) : mGame(game)
{
	//Sets position
	retryButton = new RetryButton(mGame, Vector2(250, 200));
	menuButton = new ReturnToMenuButton(mGame, Vector2(250, 300));

	//Sets default states to paused as the game over screen is off by default
	retryButton->SetState(Actor::EPaused);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	menuButton->SetState(Actor::EPaused);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}

GameOverScreen::~GameOverScreen()
{
	delete menuButton;
	menuButton = nullptr;

	delete retryButton;
	retryButton = nullptr;
}

void GameOverScreen::Update(float deltaTime, SDL_Event& e)
{
	//Checks to see if the menu is active before handling events
	if (isActive) {
		retryButton->HandleEvent(&e);
		menuButton->HandleEvent(&e);
	}
}

void GameOverScreen::SetActive(bool newValue)
{
	isActive = newValue;
	if (isActive) {
		Activate();
	}
	else
	{
		DeActivate();
	}
}

void GameOverScreen::Activate()
{
	//Activates all objects
	retryButton->SetState(Actor::EActive);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);

	menuButton->SetState(Actor::EActive);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);
}

void GameOverScreen::DeActivate()
{
	//Deactivates all objects
	retryButton->SetState(Actor::EPaused);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	menuButton->SetState(Actor::EPaused);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}
