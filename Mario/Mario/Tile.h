#pragma once
#include "Actor.h"
#include "SDL.h"
#include "SpriteComponent.h"

class Tile : public Actor
{
public:
	Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest);

	int GetTileType() const { return mTileType; }

	void SetSrcRect(SDL_Rect* newRect) { sc->SetSrcRect(newRect); }
	void SetDestRect(SDL_Rect* newRect) { sc->SetDestRect(newRect); }
private:
	int mTileType;
	SDL_Rect* mSrcRect;
	SDL_Rect* mDestRect;
protected:
	class SpriteComponent* sc;


};

