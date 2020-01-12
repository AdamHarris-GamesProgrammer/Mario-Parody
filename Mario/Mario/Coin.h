#pragma once
#include "Actor.h"
#include "SDL.h"

class Coin : public Actor
{
public:
	Coin(class Game* game);
	~Coin();

	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};

