#include "NextLevelScreen.h"

NextLevelScreen::NextLevelScreen(class Game* game) : mGame(game)
{
	successText = new Actor(mGame);
	successText->SetPosition(Vector2(250, 60));
	successTextTsc = new TextSpriteComponent(successText);
	successTextTsc->SetText("Level Complete!");
	successTextTsc->SetTextSize(40);

	scoreText = new Actor(mGame);
	scoreText->SetPosition(Vector2(250, 100));
	scoreTextTsc = new TextSpriteComponent(scoreText);
	scoreTextTsc->SetText("Score: " + std::to_string(mGame->GetScore()));
	scoreTextTsc->SetTextSize(32);

	highscoreText = new Actor(mGame);
	highscoreText->SetPosition(Vector2(250, 140));
	highscoreTextTsc = new TextSpriteComponent(highscoreText);
	highscoreTextTsc->SetText("Highscore: " + std::to_string(mGame->GetHighscore()));
	highscoreTextTsc->SetTextSize(32);

	nextLevelButton = new NextLevelButton(mGame, Vector2(250, 180));
	

	successText->SetState(Actor::EPaused);
	scoreText->SetState(Actor::EPaused);
	highscoreText->SetState(Actor::EPaused);

	nextLevelButton->SetState(Actor::EPaused);

}

NextLevelScreen::~NextLevelScreen()
{

}

void NextLevelScreen::Update(float deltaTime, SDL_Event& e)
{

	nextLevelButton->HandleEvent(&e);
}

void NextLevelScreen::SetActive(bool newValue)
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

void NextLevelScreen::Activate()
{
	for (auto& text : mTextActors) {
		text->SetState(Actor::EActive);
	}

	/*for (auto& button : mButtonActors)
	{
		button->SetState(Actor::EActive);
	}*/
	nextLevelButton->SetState(Actor::EActive);
}

void NextLevelScreen::DeActivate()
{
	for (auto& text : mTextActors) {
		text->SetState(Actor::EPaused);
	}

	/*for (auto& button : mButtonActors)
	{
		button->SetState(Actor::EPaused);
	}*/
	nextLevelButton->SetState(Actor::EPaused);
}
