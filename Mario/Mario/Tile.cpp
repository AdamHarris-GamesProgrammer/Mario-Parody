#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest):  Actor(game), mSrcRect(src), mDestRect(dest)
{
	sc = new SpriteComponent(this);
	sc->SetSrcRect(mSrcRect);
	sc->SetDestRect(mDestRect);
	sc->SetTexture(game->GetTexture("Assets/TileMap.png"));
	sc->GetOwner()->SetPosition(Vector2(mDestRect->x, mDestRect->y));
}
