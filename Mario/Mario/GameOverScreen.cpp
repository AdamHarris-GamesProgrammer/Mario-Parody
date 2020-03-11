#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(class Game* game) : mGame(game)
{
	retryButton = new RetryButton(mGame, Vector2(250, 200));
	menuButton = new ReturnToMenuButton(mGame, Vector2(250, 300));


	retryButton->SetState(Actor::EPaused);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	menuButton->SetState(Actor::EPaused);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}

GameOverScreen::~GameOverScreen()
{

}

void GameOverScreen::Update(float deltaTime, SDL_Event& e)
{
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
	retryButton->SetState(Actor::EActive);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);

	menuButton->SetState(Actor::EActive);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);
}

void GameOverScreen::DeActivate()
{
	retryButton->SetState(Actor::EPaused);
	retryButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	menuButton->SetState(Actor::EPaused);
	menuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}
