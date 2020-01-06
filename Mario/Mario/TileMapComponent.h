#pragma once
#include "SpriteComponent.h"
#include "Constants.h"
#include <iostream>

//32 x 20 tiles

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 100) : SpriteComponent(owner, drawOrder) {
		srcRect = new SDL_Rect();
		destRect = new SDL_Rect();

		srcRect->w = srcRect->h = TILE_HEIGHT;
		destRect->w = destRect->h = TILE_HEIGHT;

		mLevelWidth = 32;
		mLevelHeight = 20;
	}

	void LoadTileTextures(SDL_Texture* tileTexture);
	void LoadMap(const std::string& fileName);
	void LoadMap(int arr[32][20]);
	//void Draw(SDL_Renderer* renderer, SDL_Rect* sourceRect, double rotation /* = 0.0f */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */) override;
	void Render(SDL_Renderer* renderer);

private:
	int mLevelWidth;
	int mLevelHeight;

	SDL_Texture* mTexture;
	SDL_Rect* destRect;
	SDL_Rect* srcRect;



	int map[32][20];
};

