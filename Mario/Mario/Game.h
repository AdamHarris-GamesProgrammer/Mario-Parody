#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Math.h"

#include "Constants.h"
#include "BlueSky.h"
#include "LevelGoal.h"

#include <vector>
#include <fstream>

class Game
{
public:
	Game() {}
	~Game() {}

	bool Initialize();

	void Shutdown();

	void PollInput();

	void Update();

	void Render();



	class Mario* GetPlayer() { return mPlayer; }
	void SetPlayerSpawnPoint(Vector2 position);

	class TileMapComponent* GetMap() { return map; }

	void AddCoin(class Coin* coin);
	void RemoveCoin(class Coin* coin);
	void IncrementScore(int amount = 10);
	std::vector<class Coin*>& GetCoins() { return mCoins; }

	void AddTile(class Tile* tile);
	void RemoveTile(class Tile* tile);
	void EmptyMap();
	std::vector<class Tile*>& GetTiles() { return mTiles; }

	void AddKoopa(class Koopa* koopa);
	void RemoveKoopa(class Koopa* koopa);
	std::vector<class Koopa*>& GetKoopas() { return mKoopas;	}

	void AddPowBlock(class PowBlock* powBlock);
	void RemovePowBlock(class PowBlock* powBlock);
	std::vector<class PowBlock*>& GetPowBlocks() { return mPowBlocks; }

	class LevelGoal* GetLevelGoal() { return mLevelGoal; }
	void AddLevelGoal(class LevelGoal* goal);

	int GetCurrentLevel() const { return mCurrentLevel; }

	void NextLevel();

	SDL_Rect mCamera = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	BlueSky* GetEngine() const { return mEngine; }

private:
	void LoadContent();

	class ScoreManager* mScoreManager = nullptr;

	class Mario* mPlayer = nullptr;
	class Actor* mapActor = nullptr;
	class TileMapComponent* map = nullptr;

	class Actor* bgActor = nullptr;
	class Actor* fgActor = nullptr;

	std::vector<class Coin*> mCoins;

	std::vector<class Tile*> mTiles;
	std::vector<class Koopa*> mKoopas;
	std::vector<class PowBlock*> mPowBlocks;

	class LevelGoal* mLevelGoal = nullptr;

	Actor* mScoreText = nullptr;
	class TextSpriteComponent* mScoreTsc = nullptr;

	int mCurrentLevel = 0;
	std::string mLevels[4];

	int mScore = 0;
	int mHighScore = 0;

	BlueSky* mEngine = nullptr;
};

