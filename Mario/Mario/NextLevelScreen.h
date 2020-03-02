#pragma once

#include "Game.h"
#include "Actor.h"
#include "ButtonComponent.h"
#include "TextSpriteComponent.h"
#include "NextLevelButton.h"

class NextLevelScreen
{
public:
	NextLevelScreen(class Game* game);
	~NextLevelScreen();

	void Update(float deltaTime, SDL_Event& e);


	bool GetActive() const { return isActive; }
	void SetActive(bool newValue);

	

private:
	Actor* successText;
	Actor* scoreText;
	Actor* highscoreText;

	TextSpriteComponent* successTextTsc;
	TextSpriteComponent* scoreTextTsc;
	TextSpriteComponent* highscoreTextTsc;

	NextLevelButton* nextLevelButton;
	ButtonComponent* tryAgainButton;
	ButtonComponent* exitToMainMenuButton;


	std::vector<class ButtonComponent*> mButtonActors;
	std::vector<class Actor*> mTextActors;

	bool isActive = false;

	void Activate();
	void DeActivate();

	class Game* mGame;
};

