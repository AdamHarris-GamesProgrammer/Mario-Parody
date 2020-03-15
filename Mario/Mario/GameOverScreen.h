#pragma once

#include "RetryButton.h"
#include "ReturnToMenuButton.h"
#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"

class GameOverScreen
{
public:
	GameOverScreen(class Game* game);
	~GameOverScreen();

	void Update(float deltaTime, SDL_Event& e);

	//Getter/Setter for isActive variables
	bool GetActive() const { return isActive; }
	void SetActive(bool newValue);

private:
	bool isActive = false;

	//Sets all the objects to active 
	void Activate();

	//Sets all the onjects to paused
	void DeActivate();

	class Game* mGame;

	ReturnToMenuButton* menuButton;
	RetryButton* retryButton;

};

