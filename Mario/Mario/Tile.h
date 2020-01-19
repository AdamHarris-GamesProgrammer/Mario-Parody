#pragma once
#include "Actor.h"
#include "SDL.h"
#include "SpriteComponent.h"

class Tile : public Actor, public SpriteComponent
{
public:
	Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest);
	~Tile();

	void Draw(SDL_Renderer* renderer) override;

	int GetTileType() const { return mTileType; }

private:
	int mTileType;

};

