#pragma once
#include "Actor.h"
#include "SDL.h"
#include "SpriteComponent.h"

class Tile : public Actor, public SpriteComponent
{
public:
	Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest, int tileType, bool wall);
	~Tile();
	
	void Draw(SDL_Renderer* renderer) override;

	int GetTileType() const { return mTileType; }

	void Update(float deltaTime) override;

	bool IsWall() const { return isWall; }

private:
	int mTileType;

	bool isWall;
	Vector2 position;

};

