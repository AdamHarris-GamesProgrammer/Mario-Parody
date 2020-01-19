#include "TileMapComponent.h"

#include "Actor.h"
#include "Coin.h"
#include "Game.h"
#include "Tile.h"

TileMapComponent::TileMapComponent(class Actor* owner, int drawOrder /*= 10*/) : SpriteComponent(owner, drawOrder)
{
	mLevelWidth = 32;
	mLevelHeight = 20;
}

//TODO USE DYNAMIC memory to resize the array to the needed size

void TileMapComponent::LoadMap(const std::string& fileName)
{
	std::ifstream mapFile;
	mapFile.open(fileName);

	int row = 0;

	while (mapFile.good()) {
		int column = 0;

		std::string line;
		getline(mapFile, line, '\n');
		std::istringstream iss(line);
		std::string token;
		while (std::getline(iss, token, ',')) {
			map[row][column] = std::stoi(token);
			column++;
		}
		row++;

	}

	GenerateObjects();
}

void TileMapComponent::GenerateObjects() {
	int type = 0;

	for (int row = 0; row < mLevelHeight; row++) {
		for (int column = 0; column < mLevelWidth; column++) {
			type = map[row][column];

			if (type == 0) {
				SDL_Rect* brickSrc = new SDL_Rect { 0,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, brickDest);
				brick->SetPosition(Vector2(brickDest->x + 16.0f, brickDest->y + 16.0f));
				brick->SetDestRect(brickDest);
				brick->SetSrcRect(brickSrc);
			}
			else if (type == 32) {
				SDL_Rect* goldBrickSrc = new SDL_Rect{ 0,32,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* goldBrickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mOwner->GetGame(), goldBrickSrc, goldBrickDest);
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

void TileMapComponent::ChangeTileAt(int row, int column, int newValue)
{
	map[row][column] = newValue;
}
