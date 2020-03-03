#include "NextLevelScreen.h"
#include "SpriteComponent.h"
NextLevelScreen::NextLevelScreen(class Game* game) : mGame(game)
{
	SDL_Color black = SDL_Color();
	black = { 0,0,0,255 };

	mMenuActor = new Actor(game);
	mMenuActor->SetPosition(Vector2(200, 60));
	mMenuBackground = new SpriteComponent(mMenuActor, 300);
	mMenuBackground->SetTexture(mGame->GetEngine()->GetTexture("Assets/Menus/Blank Screen (400x540).png"));

	successText = new Actor(mGame);
	successText->SetPosition(Vector2(400, 60));
	successTextTsc = new TextSpriteComponent(successText);
	successTextTsc->SetText("Level Complete!");
	successTextTsc->SetTextSize(40);
	successTextTsc->SetTextColor(black);

	scoreText = new Actor(mGame);
	scoreText->SetPosition(Vector2(400, 100));
	scoreTextTsc = new TextSpriteComponent(scoreText);

	scoreTextTsc->SetTextSize(32);
	scoreTextTsc->SetTextColor(black);
	

	highscoreText = new Actor(mGame);
	highscoreText->SetPosition(Vector2(400, 140));
	highscoreTextTsc = new TextSpriteComponent(highscoreText);
	highscoreTextTsc->SetTextSize(32);
	highscoreTextTsc->SetTextColor(black);

	nextLevelButton = new NextLevelButton(mGame, Vector2(250, 180));


	successText->SetState(Actor::EPaused);
	scoreText->SetState(Actor::EPaused);
	highscoreText->SetState(Actor::EPaused);

	nextLevelButton->SetState(Actor::EPaused);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
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
	highscoreTextTsc->SetText("Highscore: " + std::to_string(mGame->GetHighscore()));
	scoreTextTsc->SetText("Score: " + std::to_string(mGame->GetScore()));

	successText->SetState(Actor::EActive);
	scoreText->SetState(Actor::EActive);
	highscoreText->SetState(Actor::EActive);

	nextLevelButton->SetState(Actor::EActive);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EActive);
}

void NextLevelScreen::DeActivate()
{
	successText->SetState(Actor::EPaused);
	scoreText->SetState(Actor::EPaused);
	highscoreText->SetState(Actor::EPaused);

	nextLevelButton->SetState(Actor::EPaused);
	nextLevelButton->mButtonTextComponent->GetOwner()->SetState(Actor::EPaused);
}
