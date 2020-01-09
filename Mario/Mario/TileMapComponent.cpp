#include "TileMapComponent.h"
#include <sstream>


TileMapComponent::TileMapComponent(class Actor* owner, int drawOrder /*= 10*/) : SpriteComponent(owner, drawOrder) {
	srcRect = new SDL_Rect();
	destRect = new SDL_Rect();

	srcRect->h = TILE_HEIGHT;
	srcRect->w = TILE_WIDTH;

	destRect->h = TILE_HEIGHT;
	destRect->w = TILE_WIDTH;

	mLevelWidth = 32;
	mLevelHeight = 20;
}

//USE DYNAMIC memory to resize the array to the needed size

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
}

void TileMapComponent::Render(SDL_Renderer* renderer)
{
	int type = 0;

	for (int row = 0; row < mLevelHeight; row++) {
		for (int column = 0; column < mLevelWidth; column++) {
			type = map[row][column];

			if (type != -1) {
				destRect->x = column * TILE_WIDTH;
				destRect->y = row * TILE_HEIGHT;

				switch (type)
				{
				case -1:
					srcRect->x = 0;
					srcRect->y = 0;
					break;
				case 0:
					srcRect->x = 0;
					srcRect->y = 0;
					SpriteComponent::Draw(renderer, srcRect, destRect);
					break;
				case 32:
					srcRect->x = 0;
					srcRect->y = 32;
					SpriteComponent::Draw(renderer, srcRect, destRect);
					break;
				}
			}

		}
	}
}
