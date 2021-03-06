#pragma once
#include "Tile.h"
#include "SDL.h"
#include "CircleComponent.h"

class Coin : public Tile
{
public:
	Coin(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect);
	~Coin();

	void Update(float deltaTime) override;

	//Circle used for collision with the player
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;

	//used for animating the button
	int currentFrame = 0;
	float currentElapsedTime = 0;
};

