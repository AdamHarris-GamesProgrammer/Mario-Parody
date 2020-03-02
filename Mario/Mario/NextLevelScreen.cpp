#include "NextLevelScreen.h"
#include "SpriteComponent.h"
NextLevelScreen::NextLevelScreen(class Game* game) : mGame(game)
{
	mMenuActor = new Actor(game);
	mMenuActor->SetPosition(Vector2(200, 60));
	mMenuBackground = new SpriteComponent(mMenuActor, 300);
	mMenuBackground->SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Blank Screen (400x540).png"));

	successText = new Actor(mGame);
	successText->SetPosition(Vector2(400, 60));
	successTextTsc = new TextSpriteComponent(successText);
	successTextTsc->SetText("Level Complete!");
	successTextTsc->SetTextSize(40);

	scoreText = new Actor(mGame);
	scoreText->SetPosition(Vector2(400, 100));
	scoreTextTsc = new TextSpriteComponent(scoreText);
	scoreTextTsc->SetText("Score: " + std::to_string(mGame->GetScore()));
	scoreTextTsc->SetTextSize(32);
	

	highscoreText = new Actor(mGame);
	highscoreText->SetPosition(Vector2(400, 140));
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
	mMenuBackground->Draw(mGame->GetEngine()->GetRenderer());
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
