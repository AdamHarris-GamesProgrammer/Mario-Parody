#pragma once

#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "PlayButton.h"

class MainMenuScreen
{
public:
	MainMenuScreen(class Game* game);
	~MainMenuScreen();

	void Update(float deltaTime, SDL_Event& e);

	bool GetActive() const { return isActive; }
	void SetActive(bool newValue);

private:
	Actor* marioLogoActor;
	SpriteComponent* marioLogo;


	PlayButton* playButton;

	bool isActive = true;

	void Activate();
	void Deactivate();

	Game* mGame;
};

