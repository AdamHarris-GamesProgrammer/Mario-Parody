#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(class Game* game) : mGame(game)
{
	SDL_Color black = SDL_Color();
	black = { 0,0,0,255 };

	marioLogoActor = new Actor(game);
	marioLogoActor->SetPosition(Vector2(200, 200));
	marioLogo = new SpriteComponent(marioLogoActor, 300);
	marioLogo->SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Logo.png"));

	playButton = new PlayButton(mGame, Vector2(250, 250));
}

MainMenuScreen::~MainMenuScreen()
{
	delete marioLogoActor;
	marioLogoActor = NULL;

	delete marioLogo;
	marioLogo = NULL;

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
	marioLogoActor->SetState(Actor::EActive);
	playButton->SetState(Actor::EActive);
	playButton->mButtonTextActor->SetState(Actor::EActive);

}

void MainMenuScreen::Deactivate()
{
	marioLogoActor->SetState(Actor::EPaused);
	playButton->SetState(Actor::EPaused);
	playButton->mButtonTextActor->SetState(Actor::EPaused);

}
