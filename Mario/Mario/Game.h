#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Math.h"

#include "Constants.h"
#include "BlueSky.h"
#include "LevelGoal.h"
#include "NextLevelScreen.h"
#include "NextLevelButton.h"
#include "GameOverScreen.h"
#include "TextSpriteComponent.h"
#include "ButtonComponent.h"
#include <vector>
#include <fstream>
#include "Sound.h"
#include "Music.h"
#include "PlayButton.h"
#include "MainMenuScreen.h"
#include "ReturnToMenuButton.h"
#include "GameScreen.h"

class Game
{
public:
	Game() {}
	~Game() {}

	//calls the initialize method in the BlueSky class
	bool Initialize();

	//Calls the Shutdown method in the BlueSky class
	void Shutdown();

	//Polls input for all objects that need it (menu objects and player)
	void PollInput();

	//handles objects that need updating as well as camera positioning
	void Update();

	//calls render method in BlueSky class
	void Render();

	//Set the next level menu to active (allowing the player to see and interact with it)
	void LoadNextLevelMenu();

	//Player related functions
	//Returns the player
	class Mario* GetPlayer() { return mPlayer; }
	//Sets the player spawn point
	void SetPlayerSpawnPoint(Vector2 position);

	//Increments the score
	void IncrementScore(int amount = 10);

	//Returns the current level variable
	int GetCurrentLevel() const { return mCurrentLevel; }

	//Menu button methods for loading certain levels
	void NextLevel();
	void PlayFirstLevel();
	void ReturnToMainMenu();
	void RetryLevel();

	//On player death event
	void OnPlayerDeath();

	//Creates camera and sets values appropriately
	SDL_Rect mCamera = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	//Gets the score and highscore
	int GetScore() const { return mScore; }
	int GetHighscore() const { return mHighScore; }

	//Returns a pointer to the mEngine variable allowing objects to load textures etc.
	BlueSky* GetEngine() const { return mEngine; }

	//Returns if the game is over if it is paused
	bool IsGameOver() const { return gameOver; }
	bool IsGamePaused() const { return bPaused; }

	//Loops through all enemies and flips them
	void FlipEnemies();


	//returns a pointer to the current game screen class
	class GameScreen* GetCurrentScreen() { return mLevels[mCurrentLevel]; } 
private:
	///game over and paused variables
	bool gameOver = false;
	bool bPaused = true;

	//loads the required content for the game such as initial level, Mario, background and foreground
	void LoadContent();

	//Score manager class used for loading and saving the highscore
	class ScoreManager* mScoreManager = nullptr;

	//Actors for the background and foreground
	class Actor* mBackgroundActor = nullptr;
	class Actor* mForegroundActor = nullptr;

	//Player actor
	class Mario* mPlayer = nullptr;

	//Music object for the game
	Music* mBGMusic = nullptr;

	//Game Screen UIs
	class NextLevelScreen* mNextLevelScreen = nullptr;
	class MainMenuScreen* mMainMenu = nullptr;
	class GameOverScreen* mGameOverScreen = nullptr;

	//Score text actor and component
	Actor* mScoreText = nullptr;
	class TextSpriteComponent* mScoreTsc = nullptr;

	//The current level
	int mCurrentLevel = 0;

	//Score and highscore
	int mScore = 0;
	int mHighScore = 0;

	//Pointer to BlueSky to act as the game engine
	BlueSky* mEngine = nullptr;

	//Array of GameScreen objects 
	GameScreen* mLevels[5];

	//Method for helping with common features of a level change
	void LevelChange(int levelIndex);
};

