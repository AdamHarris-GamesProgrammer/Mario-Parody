#pragma once
#include "SpriteComponent.h"
#include "Constants.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 10);

	//Loads the map into the mMap vector
	bool LoadMap(const std::string& fileName);

	//This method generates the tiles based off the mMap vector contents
	void GenerateObjects();

	
	//Returns the value of a tile at a particular position
	int GetValueAtTile(int row, int column)
	{
		//if the desired tile is in the map 
		if (row < mLevelHeight && column < mLevelWidth && row >= 0 && column >= 0) {
			//return value
			return mMap.at(row).at(column);
		}
		else
		{
			//return -1 (AIR value)
			return -1;
		}
	}

	//This method changes the value of a tile at a certain position used for dealing with destroying Pow blocks and coins
	void ChangeTileAt(int row, int column, int newValue);

	//Returns the actual level width in pixels 
	int GetCalculatedLevelWidth() { return mLevelWidth * TILE_WIDTH; }
	int GetCalculatedLevelHeight() { return mLevelHeight * TILE_HEIGHT; }

private:
	int mLevelWidth;
	int mLevelHeight;

	//mMap holds all of the tile values
	std::vector<std::vector<int>> mMap;

	//mTileMap holds all of the tile objects on the map
	std::vector<std::vector<class Tile*>> mTileMap;
};

