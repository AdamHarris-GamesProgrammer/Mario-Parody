#pragma once

#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "NextLevelButton.h"
#include "ReturnToMenuButton.h"
#include "RetryButton.h"

class NextLevelScreen
{
public:
	NextLevelScreen(class Game* game);
	~NextLevelScreen();

	void Update(float deltaTime, SDL_Event& e);

	//Getter/Setter for isActive
	bool GetActive() const { return isActive; }
	void SetActive(bool newValue);

	

private:
	//Actors for text
	Actor* successText;
	Actor* scoreText;
	Actor* highscoreText;

	//Text components
	TextSpriteComponent* successTextTsc;
	TextSpriteComponent* scoreTextTsc;
	TextSpriteComponent* highscoreTextTsc;

	//Buttons
	NextLevelButton* nextLevelButton;
	RetryButton* tryAgainButton;
	ReturnToMenuButton* exitToMainMenuButton;

	bool isActive = false;

	void Activate();
	void DeActivate();

	class Game* mGame;
};

