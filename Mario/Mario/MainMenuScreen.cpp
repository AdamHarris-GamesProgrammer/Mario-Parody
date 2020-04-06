#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(class Game* game) : mGame(game)
{
	playButton = new PlayButton(mGame, Vector2(250, 250));
}

MainMenuScreen::~MainMenuScreen()
{
	delete playButton;
	playButton = NULL;
}

void MainMenuScreen::Update(float deltaTime, SDL_Event& e)
{
	if (isActive) {
		playButton->HandleEvent(&e);
	}
}

void MainMenuScreen::SetActive(bool newValue)
{
	isActive = newValue;
	if (isActive) {
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void MainMenuScreen::Activate()
{
	//Activates all objects
	playButton->SetState(Actor::EActive);
	playButton->mButtonTextActor->SetState(Actor::EActive);

}

void MainMenuScreen::Deactivate()
{
	//Deactivates all objects
	playButton->SetState(Actor::EPaused);
	playButton->mButtonTextActor->SetState(Actor::EPaused);

}
