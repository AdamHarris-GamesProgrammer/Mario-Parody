#include "TileMapComponent.h"

//USE DYNAMIC memory to resize the array to the needed size

void TileMapComponent::LoadTileTextures(SDL_Texture* tileTexture)
{
	SetTexture(tileTexture);
}

void TileMapComponent::LoadMap(const std::string& fileName)
{

}

void TileMapComponent::LoadMap(int arr[32][20])
{
	for (int row = 0; row < mLevelWidth; row++) {
		for (int column = 0; column < mLevelHeight; column++) {
			map[row][column] = arr[row][column];
		}
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
