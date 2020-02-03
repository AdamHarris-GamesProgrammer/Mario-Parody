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
	void IncrementScore();
	std::vector<class Coin*>& GetCoins() { return mCoins; }

	void AddTile(class Tile* tile);
	void RemoveTile(class Tile* tile);
	void EmptyMap();
	std::vector<class Tile*>& GetTiles() { return mTiles; }

	class LevelGoal* GetLevelGoal() { return mLevelGoal; }
	void AddLevelGoal(class LevelGoal* goal);

	void NextLevel();

	SDL_Rect mCamera = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	BlueSky* GetEngine() const { return mEngine; }

private:
	void LoadContent();

	class Mario* mPlayer = nullptr;
	class Actor* mapActor = nullptr;
	class TileMapComponent* map = nullptr;

	class Actor* bgActor = nullptr;
	class Actor* fgActor = nullptr;

	std::vector<class Coin*> mCoins;

	std::vector<class Tile*> mTiles;

	class LevelGoal* mLevelGoal = nullptr;

	Actor* scoreText = nullptr;
	class TextSpriteComponent* scoreTsc = nullptr;

	int currentLevel = 0;
	std::string levels[5];

	int score = 0;

	BlueSky* mEngine;
};

