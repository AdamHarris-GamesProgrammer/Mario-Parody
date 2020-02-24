#pragma once
#include "Actor.h"
#include "SDL.h"
#include "SpriteComponent.h"

class Tile : public Actor, public SpriteComponent
{
public:
	Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest, int tileType);
	~Tile();
	
	void Draw(SDL_Renderer* renderer) override;

	int GetTileType() const { return mTileType; }
	int GetCollisionType()const { return mCollisionType; }
	void SetCollisionType(int newValue) { mCollisionType = newValue; }

	void Update(float deltaTime) override;

private:
	int mTileType;
	int mCollisionType = 0;


	Vector2 position;

};

