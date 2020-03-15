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
	//Clears mMap and mTileMap if they are not empty
	if(!mMap.empty()){
		mMap.clear();
	}
	if (!mTileMap.empty()) {
		mTileMap.clear();
	}

	//This holds the file buffer for the mapFile thats being loaded in
	std::ifstream mapFile;

	//opens the file
	mapFile.open(fileName);

	//if there are contents in the file
	if (mapFile.good()) {
		mLevelWidth = 0;
		mLevelHeight = 0;

		//loops through each line in the file
		while (mapFile.good()) {
			std::string line;
			//gets the current line
			getline(mapFile, line, '\n');

			//Tokenises the line into Comma separated values e.g. 1,2,3 would become 1 2 3
			std::istringstream iss(line);
			std::string token;
			std::vector<int> row;
			while (std::getline(iss, token, ',')) {
				//pushes the value of iss into the row vector
				row.push_back(std::stoi(token));
			}
			//pushes the row vector into the map vector
			mMap.push_back(row);

			//clears the row vector so it can load another row
			row.clear();

		}

		//Sets the level height and width
		mLevelHeight = mMap.size() - 1;
		//-1 on the index as the last element of a vector is always 0 to act as a end check
		mLevelWidth = mMap[mLevelHeight - 1].size();

		//Calls the generate objects function to create the tile map
		GenerateObjects();
		return true;
	}
	else
	{
		//if the map cannot be loaded 
		std::cout << "Map: " << fileName << " could not be loaded" << std::endl;
		return false;
	}

	mapFile.close();

}

void TileMapComponent::GenerateObjects() {
	//type holds the value of the current map index
	int type = 0;

	//cycles through each row
	for (int row = 0; row < mLevelHeight; row++) {
		std::vector<Tile*> tileRow;
		//cycles through each column
		for (int column = 0; column < mLevelWidth; column++) {
			//sets type equal to the value at row at a particular column
			type = mMap.at(row).at(column);

			//This dest rect is used for placing all objects
			SDL_Rect* destRect = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

			//if the type is AIR 
			if (type == AIR) {
				//Uses a blank tile on the tile map
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };
				//Adds the tile to the game
				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				//Adds the tile to the tileRow vector
				tileRow.push_back(blankTile);
			}

			//if the type is brick
			else if (type == BRICK) {
				//Brick src coordinates
				SDL_Rect* brickSrc = new SDL_Rect { 0,0,TILE_WIDTH,TILE_HEIGHT };

				//Creates a new tile object with the brick src passed through
				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, destRect, 0);
				brick->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));
				tileRow.push_back(brick);
			}
			//if the type is 2 (blank tile placed by accident when using map editor
			else if (type == 2) {
				//sets the tile to air
				mMap.at(row).at(column) = -1;
			}

			//if the type is DROPBRICK 
			else if (type == DROPBRICK) {
				//dropbrick src coords
				SDL_Rect* brickSrc = new SDL_Rect{ 32,0,TILE_WIDTH, TILE_HEIGHT };

				//creates tile
				Tile* brick = new Tile(mOwner->GetGame(), brickSrc, destRect, -1);
				brick->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));

				//pushes back tile
				tileRow.push_back(brick);
			}
			else if (type == PLAYERSPAWN) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);

				//sets the players spawn position
				mOwner->GetGame()->SetPlayerSpawnPoint(Vector2(column * TILE_WIDTH, (row * TILE_HEIGHT)));
			}
			else if (type == LEVELGOAL) {
				SDL_Rect* goalSrc = new SDL_Rect{ 128,0,TILE_WIDTH,TILE_HEIGHT };

				LevelGoal* goal = new LevelGoal(mOwner->GetGame(), goalSrc, destRect);

				//adds the level goal to the current screen
				mOwner->GetGame()->GetCurrentScreen()->AddLevelGoal(goal);
				tileRow.push_back(goal);
			}
			else if (type == KOOPA) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);

				//adds the koopa to the game
				Koopa* koopa = new Koopa(mOwner->GetGame());
				koopa->SetPosition(Vector2(destRect->x, destRect->y + 2.0f));
				mOwner->GetGame()->GetCurrentScreen()->AddKoopa(koopa);
				
				
			}
			else if (type == KOOPATURN) {
				SDL_Rect* blankSrc = new SDL_Rect{ 64,0,TILE_WIDTH,TILE_HEIGHT };

				Tile* blankTile = new Tile(mOwner->GetGame(), blankSrc, destRect, -1);

				tileRow.push_back(blankTile);
			}
			else if (type == GOLDBRICK) {
				SDL_Rect* goldBrickSrc = new SDL_Rect{ 0,32,TILE_WIDTH,TILE_HEIGHT };

				//creates a pow block instance
				PowBlock* pow = new PowBlock(mOwner->GetGame(), goldBrickSrc, destRect);
				pow->SetPosition(Vector2(destRect->x + 16.0f, destRect->y + 16.0f));

				//adds pow block to the current screen
				mOwner->GetGame()->GetCurrentScreen()->AddPowBlock(pow);
				tileRow.push_back(pow);
			}
			else if (type == COIN) {
				SDL_Rect* coinSrc = new SDL_Rect{ 0,64,TILE_WIDTH,TILE_HEIGHT };

				//Creates a coin instance
				Coin* coin = new Coin(mOwner->GetGame(), coinSrc, destRect);

				//Adds the coin to the current screen
				mOwner->GetGame()->GetCurrentScreen()->AddCoin(coin);
				tileRow.push_back(coin);
			}
			//Process is the same for all the PIPE blocks just with different src coords
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
		}
		//pushes back the tile row into the mTileMap vector
		mTileMap.push_back(tileRow);

		//clears the tileRow so it can be used to load another row
		tileRow.clear();
	}
}

void TileMapComponent::ChangeTileAt(int row, int column, int newValue)
{
	//sets the value at the desired position to the new value
	mMap.at(row).at(column) = newValue;
}
