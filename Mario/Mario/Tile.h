#pragma once
#include "Actor.h"
#include "SDL.h"
#include "SpriteComponent.h"

class Tile : public Actor, public SpriteComponent //inherits from both actor and sprite component as a tile is both
{
public:
	Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest, bool collidable);
	~Tile();
	
	//overrides the draw method of the SpriteComponent class
	void Draw(SDL_Renderer* renderer) override;

	//overrides the update method of the SriteComponent class
	void Update(float deltaTime) override;

	bool GetCollidable() const { return bCollidable; }
	void SetCollidable(bool newVal) { bCollidable = newVal; }
private:
	//holds the position data for the tile
	Vector2 position;

	bool bCollidable = false;
};

