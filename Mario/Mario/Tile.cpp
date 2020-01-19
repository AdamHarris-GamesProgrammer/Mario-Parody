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

void Tile::Draw(SDL_Renderer* renderer)
{
	if (mTexture) {
		SDL_Rect* camera = mGame->GetCamera();

		SDL_Rect* dest = mDestRect;

		dest->x -= camera->x;
		dest->y -= camera->y;

		SDL_RenderCopyEx(renderer,
			mTexture,
			mSrcRect,
			dest,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
	//TODO: Check camera collision with tile
}
