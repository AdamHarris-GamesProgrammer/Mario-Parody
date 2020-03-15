#include "NextLevelScreen.h"
#include "SpriteComponent.h"

NextLevelScreen::NextLevelScreen(class Game* game) : mGame(game)
{
	SDL_Color black = SDL_Color();
	black = { 0,0,0,255 };

	//Sets up the success text
	successText = new Actor(mGame);
	successText->SetPosition(Vector2(400, 60));
	successTextTsc = new TextSpriteComponent(successText);
	successTextTsc->SetText("Level Complete!");
	successTextTsc->SetTextSize(40);
	successTextTsc->SetTextColor(black);

	//Sets up the score text
	scoreText = new Actor(mGame);
	scoreText->SetPosition(Vector2(400, 100));
	scoreTextTsc = new TextSpriteComponent(scoreText);
	scoreTextTsc->SetTextSize(32);
	scoreTextTsc->SetTextColor(black);
	
	//Sets up the highscore text
	highscoreText = new Actor(mGame);
	highscoreText->SetPosition(Vector2(400, 140));
	highscoreTextTsc = new TextSpriteComponent(highscoreText);
	highscoreTextTsc->SetTextSize(32);
	highscoreTextTsc->SetTextColor(black);

	//Sets up the buttons
	nextLevelButton = new NextLevelButton(mGame, Vector2(250, 180));
	tryAgainButton = new RetryButton(mGame, Vector2(250, 280));
	exitToMainMenuButton = new ReturnToMenuButton(mGame, Vector2(250, 380));

	//Set all objects to paused state
	successText->SetState(Actor::EPaused);
	scoreText->SetState(Actor::EPaused);
	highscoreText->SetState(Actor::EPaused);

	nextLevelButton->SetState(Actor::EPaused);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	exitToMainMenuButton->SetState(Actor::EPaused);
	exitToMainMenuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	tryAgainButton->SetState(Actor::EPaused);
	tryAgainButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}

NextLevelScreen::~NextLevelScreen()
{
	delete successText;
	delete scoreText;
	delete highscoreText;

	delete successTextTsc;
	delete tryAgainButton;
	delete exitToMainMenuButton;

	successText = NULL;
	scoreText = NULL;
	highscoreText = NULL;
	scoreTextTsc = NULL;
	tryAgainButton = NULL;
	exitToMainMenuButton = NULL;
}

void NextLevelScreen::Update(float deltaTime, SDL_Event& e)
{
	//Checks to see if the menu is active
	if (isActive) {
		//Calls the handle event method for each button
		nextLevelButton->HandleEvent(&e);
		exitToMainMenuButton->HandleEvent(&e);
		tryAgainButton->HandleEvent(&e);
	}
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
	//Resets the score and highscore text
	highscoreTextTsc->SetText("Highscore: " + std::to_string(mGame->GetHighscore()));
	scoreTextTsc->SetText("Score: " + std::to_string(mGame->GetScore()));

	//Sets all objects to active state
	successText->SetState(Actor::EActive);
	scoreText->SetState(Actor::EActive);
	highscoreText->SetState(Actor::EActive);

	nextLevelButton->SetState(Actor::EActive);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);

	exitToMainMenuButton->SetState(Actor::EActive);
	exitToMainMenuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);

	tryAgainButton->SetState(Actor::EActive);
	tryAgainButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);
}

void NextLevelScreen::DeActivate()
{
	//Sets all objects to paused state
	successText->SetState(Actor::EPaused);
	scoreText->SetState(Actor::EPaused);
	highscoreText->SetState(Actor::EPaused);

	nextLevelButton->SetState(Actor::EPaused);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	exitToMainMenuButton->SetState(Actor::EPaused);
	exitToMainMenuButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);

	tryAgainButton->SetState(Actor::EPaused);
	tryAgainButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}
