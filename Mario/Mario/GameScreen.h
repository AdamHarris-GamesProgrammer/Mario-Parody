#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Game.h"
#include "SDL.h"
#include "Coin.h"
#include "Tile.h"
#include "Koopa.h"
#include "PowBlock.h"

class GameScreen
{
public:
	GameScreen(class Game* game, const std::string& filePath);
	~GameScreen();

	virtual void LoadLevel();

	//Tile Functions
	void AddTile(class Tile* tile);
	void RemoveTile(class Tile* tile);
	void EmptyMap();

	//Coin Functions
	void AddCoin(class Coin* coin);
	void RemoveCoin(class Coin* coin);
	std::vector<class Coin*>& GetCoins() { return mCoins; }

	//Koopa Functions
	void AddKoopa(class Koopa* koopa);
	void RemoveKoopa(class Koopa* koopa);
	std::vector<class Koopa*>& GetKoopas() { return mKoopas; }

	//Pow Block Functions
	void AddPowBlock(class PowBlock* powBlock);
	void RemovePowBlock(class PowBlock* powBlock);
	std::vector<class PowBlock*>& GetPowBlocks() { return mPowBlocks; }

	//Level Goal Functions
	class LevelGoal* GetLevelGoal() { return mLevelGoal; }
	void AddLevelGoal(class LevelGoal* goal);

	//TileMap Functions
	class TileMapComponent* GetMap() { return mMap; }


	

private:
	std::vector<class Coin*> mCoins;
	std::vector<class Tile*> mTiles;
	std::vector<class Koopa*> mKoopas;
	std::vector<class PowBlock*> mPowBlocks;

	class LevelGoal* mLevelGoal = nullptr;

	class TileMapComponent* mMap = nullptr;

	class Game* mGame = nullptr;

	class Actor* mapActor = nullptr;

	std::string mFilePath;

	SDL_Texture* mTileTextures = nullptr;

};

