#include "TileMapComponent.h"

#include "Actor.h"
#include "Coin.h"
#include "Game.h"
#include "Tile.h"
#include "LevelGoal.h"
#include "Mario.h"

TileMapComponent::TileMapComponent(class Actor* owner, int drawOrder /*= 10*/) : SpriteComponent(owner, drawOrder)
{
}

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
		for (int column = 0; column < mLevelWidth; column++) {
			type = mMap.at(row).at(column);
			std::cout << "Tile Type: " << type << std::endl;
			if (type == 0) {
				SDL_Rect* brickSrc = new SDL_Rect { 0,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, brickDest, 0);
				brick->SetPosition(Vector2(brickDest->x + 16.0f, brickDest->y + 16.0f));
				brick->SetDestRect(brickDest);
				brick->SetSrcRect(brickSrc);
			}
			else if (type == 1) {
				SDL_Rect* brickSrc = new SDL_Rect{ 32,0,TILE_WIDTH, TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, brickDest, -1);
				brick->SetPosition(Vector2(brickDest->x + 16.0f, brickDest->y + 16.0f));
				brick->SetDestRect(brickDest);
				brick->SetSrcRect(brickSrc);
			}
			else if (type == 3) {
				mOwner->GetGame()->SetPlayerSpawnPoint(Vector2(column * TILE_WIDTH, (row * TILE_HEIGHT)));
			}
			else if (type == 4) {
				SDL_Rect* goalSrc = new SDL_Rect{ 128,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* goalDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				LevelGoal* goal = new LevelGoal(mOwner->GetGame(), goalSrc, goalDest);
				mOwner->GetGame()->AddLevelGoal(goal);
			}
			else if (type == 32) {
				SDL_Rect* goldBrickSrc = new SDL_Rect{ 0,32,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* goldBrickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), goldBrickSrc, goldBrickDest, 2);
				brick->SetPosition(Vector2(goldBrickDest->x + 16.0f, goldBrickDest->y + 16.0f));
				brick->SetDestRect(goldBrickDest);
				brick->SetSrcRect(goldBrickSrc);
			}
			else if (type == 64) {
				SDL_Rect* coinSrc = new SDL_Rect{ 0,64,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* coinDest = new SDL_Rect{ column * TILE_WIDTH, (row * TILE_HEIGHT) + (int)16.0f, TILE_WIDTH, TILE_HEIGHT };

				Coin* coin = new Coin(mOwner->GetGame(), coinSrc, coinDest);
				mOwner->GetGame()->AddCoin(coin);
			}
			else {

			}
		}
	}
}

void TileMapComponent::ClearMap()
{
	mMap.clear();
}

void TileMapComponent::ChangeTileAt(int row, int column, int newValue)
{
	mMap.at(row).at(column) = newValue;
}
