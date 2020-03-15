#include "GameScreen.h"

#include "TileMapComponent.h"

#include "Mario.h"
#include "Coin.h"
#include "Tile.h"
#include "LevelGoal.h"
#include "Koopa.h"
#include "PowBlock.h"
#include "Game.h"
#include "Actor.h"

GameScreen::GameScreen(Game* game,const std::string& filePath) : mFilePath(filePath), mGame(game)
{
	mTileTextures = mGame->GetEngine()->GetTexture("Assets/TileMap.png");
}

GameScreen::~GameScreen()
{

}

void GameScreen::LoadLevel()
{
	mapActor = new Actor(mGame);
	mMap = new TileMapComponent(mapActor);
	mMap->SetTexture(mTileTextures);
	mMap->LoadMap(mFilePath);
}

void GameScreen::AddTile(class Tile* tile)
{
	mTiles.emplace_back(tile);
}

void GameScreen::RemoveTile(class Tile* tile)
{
	auto iter = std::find(mTiles.begin(), mTiles.end(), tile);

	if (iter != mTiles.end()) {
		mTiles.erase(iter);
	}
}

void GameScreen::EmptyMap()
{
	for (auto& tile : mTiles) {
		tile->SetState(Actor::EDead);
	}

	for (auto& koopa : mKoopas) {
		koopa->SetState(Actor::EDead);
		RemoveKoopa(koopa);
	}

	for (auto& powBlock : mPowBlocks) {
		RemovePowBlock(powBlock);
	}

	mPowBlocks.clear();
	mTiles.clear();
	mCoins.clear();
	mKoopas.clear();
}

void GameScreen::AddCoin(class Coin* coin)
{
	mCoins.emplace_back(coin);

}

void GameScreen::RemoveCoin(class Coin* coin)
{
	auto iter = std::find(mCoins.begin(), mCoins.end(), coin);

	if (iter != mCoins.end()) {
		mCoins.erase(iter);
	}
}

void GameScreen::AddKoopa(class Koopa* koopa)
{
	mKoopas.emplace_back(koopa);
}

void GameScreen::RemoveKoopa(class Koopa* koopa)
{
	auto iter = std::find(mKoopas.begin(), mKoopas.end(), koopa);

	if (iter != mKoopas.end()) {
		mKoopas.erase(iter);
	}
}

void GameScreen::AddPowBlock(class PowBlock* powBlock)
{
	mPowBlocks.emplace_back(powBlock);
}

void GameScreen::RemovePowBlock(class PowBlock* powBlock)
{
	auto iter = std::find(mPowBlocks.begin(), mPowBlocks.end(), powBlock);

	if (iter != mPowBlocks.end()) {
		mPowBlocks.erase(iter);
	}
}

void GameScreen::AddLevelGoal(class LevelGoal* goal)
{
	mLevelGoal = goal;
}


