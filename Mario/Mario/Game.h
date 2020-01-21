#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Constants.h"
#include "BlueSky.h"

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


	//game specific code
	class Mario* GetPlayer() { return mPlayer; }

	class TileMapComponent* GetMap() { return map; }

	void AddCoin(class Coin* coin);
	void RemoveCoin(class Coin* coin);
	std::vector<class Coin*>& GetCoins() { return mCoins; }

	void AddTile(class Tile* tile);
	void RemoveTile(class Tile* tile);
	std::vector<class Tile*>& GetTiles() { return mTiles; }

	SDL_Rect mCamera = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	BlueSky* GetEngine() const { return mEngine; }

private:
	void LoadContent();

	//Game specific code
	class Mario* mPlayer = nullptr;
	class Actor* mapActor = nullptr;
	class TileMapComponent* map = nullptr;

	class Actor* bgActor = nullptr;
	class Actor* fgActor = nullptr;

	std::vector<class Coin*> mCoins;

	std::vector<class Tile*> mTiles;
	

	Actor* scoreText = nullptr;
	class TextSpriteComponent* scoreTsc = nullptr;

	int score = 0;

	BlueSky* mEngine;
};

