#pragma once
#include "Tile.h"
#include "SDL.h"
#include "CircleComponent.h"

class Coin : public Tile
{
public:
	Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect);
	~Coin();

	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};
