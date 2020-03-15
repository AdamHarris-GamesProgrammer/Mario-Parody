#include "Game.h"

#include "ComponentsList.h"
#include "Constants.h"

#include "Actor.h"

#include "Mario.h"
#include "Coin.h"
#include "Tile.h"
#include "LevelGoal.h"
#include "Koopa.h"
#include "PowBlock.h"
#include "ScoreManager.h"
#include "ButtonComponent.h"
#include "NextLevelButton.h"


bool Game::Initialize()
{
	//Initializes the game engine and loads content
	mEngine = new BlueSky(this);
	if (mEngine->Initialize())
	{
		LoadContent();
		mEngine->RunLoop(); //starts the game loop

		return true;
	}
	else
	{
		return false;
	}
}

void Game::LoadContent()
{

	//Loads Background clouds
	mBackgroundActor = new Actor(this);
	mBackgroundActor->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	BGSpriteComponent* background = new BGSpriteComponent(mBackgroundActor);
	background->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	std::vector<SDL_Texture*> backgroundTextures = {
		mEngine->GetTexture("Assets/bgScrolling.png"),
		mEngine->GetTexture("Assets/bgScrolling.png")
	};

	background->SetBGTexture(backgroundTextures);
	background->SetScrollSpeed(-25.0f);


	//Loads and plays background music
	mBGMusic = new Music();
	mBGMusic->SetVolume(20);
	mBGMusic->Load("Assets/Audio/BgMusic.mp3");
	mBGMusic->Play();

	//Loads and displays foreground
	mForegroundActor = new Actor(this);
	mForegroundActor->SetPosition(Vector2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 412.0f));

	BGSpriteComponent* foreground = new BGSpriteComponent(mForegroundActor);
	foreground->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	std::vector<SDL_Texture*> foregroundTextures = {
		mEngine->GetTexture("Assets/BGForeground1.png"),
		mEngine->GetTexture("Assets/BGForeground2.png"),
		mEngine->GetTexture("Assets/BGForeground3.png")
	};

	foreground->SetBGTexture(foregroundTextures);
	foreground->SetScrollSpeed(-10.0f);

	//Creates Mario instance
	mPlayer = new Mario(this);

	//Sets current level
	mCurrentLevel = 0;

	//Loads highscore
	mScoreManager = new ScoreManager(this);
	mHighScore = mScoreManager->GetHighscore();

	//Sets up score text
	mScoreText = new Actor(this);
	mScoreText->SetPosition(Vector2(SCREEN_WIDTH / 2, 32));
	mScoreTsc = new TextSpriteComponent(mScoreText);
	mScoreTsc->SetText("Score: 0");
	mScoreTsc->SetTextSize(72);

	//Sets up gameScreen file paths
	mLevels[0] = new GameScreen(this, "Assets/Maps/MarioMainMenu.csv");
	mLevels[1] = new GameScreen(this, "Assets/Maps/Mario01.csv");
	mLevels[2] = new GameScreen(this, "Assets/Maps/Mario02.csv");
	mLevels[3] = new GameScreen(this, "Assets/Maps/Mario03.csv");
	mLevels[4] = new GameScreen(this, "Assets/Maps/Mario04.csv");

	//Loads the first level
	mLevels[mCurrentLevel]->LoadLevel();

	//Sets up Game UI objects
	mNextLevelScreen = new NextLevelScreen(this);
	mMainMenu = new MainMenuScreen(this);
	mGameOverScreen = new GameOverScreen(this);
}

void Game::IncrementScore(int amount) {
	//increments the score
	mScore += amount;

	//sets the score text to the new value
	std::string text = "Score: " + std::to_string(mScore);
	mScoreTsc->SetText(text);
}


void Game::SetPlayerSpawnPoint(Vector2 position) {
	//moves the player to spawn position and changes the player tile to new position
	mPlayer->SetPosition(position);
	mPlayer->ChangePlayerTile(position);
}

void Game::NextLevel()
{
	//sets the next level screen to false so it no longer displays
	mNextLevelScreen->SetActive(false);

	gameOver = true;
	
	//allows for level looping when the player passes level 4
	if (mCurrentLevel == 4) {
		LevelChange(1); //loads first gameplay level
	}
	else
	{
		LevelChange(mCurrentLevel + 1); //loads next level
	}

	gameOver = false;
}

void Game::PlayFirstLevel()
{
	mMainMenu->SetActive(false); //sets main menu ui to false

	gameOver = true;

	LevelChange(1); //loads first level

	gameOver = false;
	bPaused = false;
}

void Game::ReturnToMainMenu()
{
	//sets possible previous screens to false
	mNextLevelScreen->SetActive(false);
	mGameOverScreen->SetActive(false);


	bPaused = true;

	//Sets main menu to active
	mMainMenu->SetActive(true); 

	mPlayer->SetDead(false); //revives player (in case they were dead)
	gameOver = true;
	
	LevelChange(0); //changes to the main menu level

	gameOver = false;
}

void Game::RetryLevel()
{
	gameOver = true;
	mGameOverScreen->SetActive(false);

	LevelChange(mCurrentLevel); //reloads the current level

	mPlayer->SetDead(false);
	gameOver = false;
}

void Game::LevelChange(int levelIndex)
{
	//Empties the current level
	mLevels[mCurrentLevel]->EmptyMap();

	//resets the score
	mScore = 0;
	mScoreTsc->SetText("Score: " + mScore);

	//Sets the current level to the new level index
	mCurrentLevel = levelIndex;

	//Gets the new highscore
	mHighScore = mScoreManager->GetHighscore();

	//Loads the new level
	mLevels[mCurrentLevel]->LoadLevel();

	//Handle background positioning for each level
	if (mCurrentLevel == 1) { //level 1 is the only level with a single tile at the bottom
		mForegroundActor->SetPosition(Vector2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 508.0f));
	}
	else
	{
		mForegroundActor->SetPosition(Vector2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 412.0f));
	}
}

void Game::OnPlayerDeath()
{
	//sets game over screen to active
	mGameOverScreen->SetActive(true);
	gameOver = true;
}

void Game::PollInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	//calls the update methods for the game ui screens
	mNextLevelScreen->Update(0.16f, event);
	mMainMenu->Update(0.16f, event);
	mGameOverScreen->Update(0.16f, event);

	//calls the poll input method in the engine
	mEngine->PollInput();

	const Uint8* state = SDL_GetKeyboardState(NULL);
	//calls player handle events method
	mPlayer->HandleEvents(state);
}

void Game::Update()
{
	//moves the camera
	mCamera.x = mPlayer->GetPosition().x - SCREEN_WIDTH / 2;

	//stops the camera from scrolling to far to the left
	if (mCamera.x < 0)
		mCamera.x = 0;
	if (mCamera.x > mCamera.w)
		mCamera.x = mCamera.w;
	if (mCamera.y < 0)
		mCamera.y = 0;
	if (mCamera.y > mCamera.h)
		mCamera.y = mCamera.h;

	mEngine->Update();
}

void Game::Render()
{
	mEngine->Render();
}

void Game::LoadNextLevelMenu()
{
	//if the score is greater than the current score
	if (mScore > mHighScore) {
		//set highscore
		mScoreManager->SetHighscore(mScore);
		mHighScore = mScore;
	}
	//loads the next level screen
	mNextLevelScreen->SetActive(true);
	gameOver = true;
}

void Game::Shutdown()
{
	mEngine->Shutdown();
}