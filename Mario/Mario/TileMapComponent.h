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

	bool LoadMap(const std::string& fileName);

	void GenerateObjects();

	void ClearMap();
	
	int GetValueAtTile(int row, int column)
	{
		if (row < mLevelHeight && column < mLevelWidth && row >= 0 && column >= 0) {
			return mMap.at(row).at(column);
		}
		else
		{
			return -1;
		}
	}

	void ChangeTileAt(int row, int column, int newValue);

	class Tile* GetTile(int row, int column) {
		if (row < mLevelHeight && column < mLevelWidth && row > 0 && column > 0) {
			return mTileMap.at(row).at(column);
		}
	}

	int GetCalculatedLevelWidth() { return mLevelWidth * TILE_WIDTH; }
	int GetCalculatedLevelHeight() { return mLevelHeight * TILE_HEIGHT; }

private:
	int mLevelWidth;
	int mLevelHeight;

	std::vector<std::vector<int>> mMap;
	std::vector<std::vector<class Tile*>> mTileMap;
};

