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

	void LoadMap(const std::string& fileName);

	void GenerateObjects();

	int GetValueAtTile(int row, int column)
	{
		if (row < mLevelHeight && column < mLevelWidth) {
			return map[row][column];
		}
		return -1; //returns -1 if the tile is out of the map
	}

	void ChangeTileAt(int row, int column, int newValue);


private:
	int mLevelWidth;
	int mLevelHeight;

	std::vector<class Coin*> mCoins;

	int map[20][32];
	Tile* tileMap[20][32];
};

