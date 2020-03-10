#include "TileMapComponent.h"

#include "Actor.h"
#include "Coin.h"
#include "Game.h"
#include "Tile.h"
#include "LevelGoal.h"
#include "Mario.h"
#include "TileValues.h"
#include "PowBlock.h"
#include "Koopa.h"

TileMapComponent::TileMapComponent(class Actor* owner, int drawOrder /*= 10*/) : SpriteComponent(owner, drawOrder) {}

bool TileMapComponent::LoadMap(const std::string& fileName)
{
	std::ifstream mapFile;
	mapFile.open(fileName);
	if (mapFile.good()) {
		mLevelWidth = 0;
		mLevelHeight = 0;

		while (mapFile.good()) {
			std::string line;
			getline(mapFile, line, '\n');
			std::istringstream iss(line);
			std::string token;
			std::vector<int> row;
			while (std::getline(iss, token, ',')) {
				row.push_back(std::stoi(token));
			}

			mMap.push_back(row);
			row.clear();

		}
		mLevelHeight = mMap.size() - 1;
		mLevelWidth = mMap[mLevelHeight - 1].size();

		GenerateObjects();
		return true;
	}
	else
	{
		std::cout << "Map: " << fileName << " could not be loaded" << std::endl;
		return false;
	}

}

void TileMapComponent::GenerateObjects() {
	int type = 0;

	for (int row = 0; row < mLevelHeight; row++) {
		std::vector<Tile*> tileRow;
		for (int column = 0; column < mLevelWidth; column++) {
			type = mMap.at(row).at(column);

			SDL_Rect* destRect = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
			if (type == AIR) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);
			}
			else if (type == BRICK) {
				SDL_Rect* brickSrc = new SDL_Rect { 0,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, destRect, 0);
				brick->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));
				tileRow.push_back(brick);
			}
			else if (type == DROPBRICK) {
				SDL_Rect* brickSrc = new SDL_Rect{ 32,0,TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, destRect, -1);
				brick->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));
				tileRow.push_back(brick);
			}
			else if (type == PLAYERSPAWN) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);

				mOwner->GetGame()->SetPlayerSpawnPoint(Vector2(column * TILE_WIDTH, (row * TILE_HEIGHT)));
			}
			else if (type == LEVELGOAL) {
				SDL_Rect* goalSrc = new SDL_Rect{ 128,0,TILE_WIDTH,TILE_HEIGHT };

				LevelGoal* goal = new LevelGoal(mOwner->GetGame(), goalSrc, destRect);
				mOwner->GetGame()->AddLevelGoal(goal);
				tileRow.push_back(goal);
			}
			else if (type == KOOPA) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);

				Koopa* koopa = new Koopa(mOwner->GetGame());
				koopa->SetPosition(Vector2(destRect->x, destRect->y + 2.0f));
				mOwner->GetGame()->AddKoopa(koopa);
				
				
			}
			else if (type == KOOPATURN) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);
			}
			else if (type == GOLDBRICK) {
				SDL_Rect* goldBrickSrc = new SDL_Rect{ 0,32,TILE_WIDTH,TILE_HEIGHT };

				PowBlock* pow = new PowBlock(mOwner->GetGame(), goldBrickSrc, destRect);
				pow->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));

				mOwner->GetGame()->AddPowBlock(pow);
				tileRow.push_back(pow);
			}
			else if (type == COIN) {
				SDL_Rect* coinSrc = new SDL_Rect{ 0,64,TILE_WIDTH,TILE_HEIGHT };

				Coin* coin = new Coin(mOwner->GetGame(), coinSrc, destRect);
				mOwner->GetGame()->AddCoin(coin);
				tileRow.push_back(coin);
			}
			else if (type == PIPE_HORIZONTAL) {
				SDL_Rect* pipeSrc = new SDL_Rect{ 0, 96, TILE_WIDTH, TILE_HEIGHT };

				Tile* tile = new Tile(mOwner->GetGame(), pipeSrc, destRect, 0);
				tileRow.push_back(tile);
			}
			else if(type == PIPE_LEFTEND)
			{
				SDL_Rect* pipeSrc = new SDL_Rect{ 64, 96, TILE_WIDTH, TILE_HEIGHT };

				Tile* tile = new Tile(mOwner->GetGame(), pipeSrc, destRect, 0);
				tileRow.push_back(tile);
			}
			else if (type == PIPE_RIGHTEND) {
				SDL_Rect* pipeSrc = new SDL_Rect{ 32, 96, TILE_WIDTH, TILE_HEIGHT };

				Tile* tile = new Tile(mOwner->GetGame(), pipeSrc, destRect, 0);
				tileRow.push_back(tile);
			}
			else if (type == PIPE_VERTICAL) {
				SDL_Rect* pipeSrc = new SDL_Rect{ 96, 96, TILE_WIDTH, TILE_HEIGHT };

				Tile* tile = new Tile(mOwner->GetGame(), pipeSrc, destRect, 0);
				tileRow.push_back(tile);
			}
			else if (type == PIPE_VERTICAL_TOP) {
				SDL_Rect* pipeSrc = new SDL_Rect{ 128, 96, TILE_WIDTH, TILE_HEIGHT };

				Tile* tile = new Tile(mOwner->GetGame(), pipeSrc, destRect, 0);
				tileRow.push_back(tile);
			}
			else {

			}
		}
		mTileMap.push_back(tileRow);
		tileRow.clear();
	}
}

void TileMapComponent::ClearMap()
{
	mMap.clear();
	mTileMap.clear();
}

void TileMapComponent::ChangeTileAt(int row, int column, int newValue)
{
	mMap.at(row).at(column) = newValue;
}
