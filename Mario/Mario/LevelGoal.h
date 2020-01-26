#pragma once
#include "Tile.h"
class LevelGoal : public Tile
{
public:
	LevelGoal(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect);
	~LevelGoal();


	class CollisionComponent* GetCollision() const { return mCollision; }
private:
	class CollisionComponent* mCollision;
};

