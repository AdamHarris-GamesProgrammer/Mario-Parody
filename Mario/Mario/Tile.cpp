#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest):  Actor(game), SpriteComponent(this)
{	
	mSrcRect = src;
	mDestRect = dest;
	SetTexture(game->GetTexture("Assets/TileMap.png"));
	SetPosition(Vector2(mDestRect->x, mDestRect->y));
	mGame->AddTile(this);
}

Tile::~Tile()
{
	mGame->RemoveTile(this);
}
