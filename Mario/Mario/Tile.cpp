#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest, int tileType):  Actor(game), SpriteComponent(this), mTileType(tileType)
{	
	mSrcRect = src;
	mDestRect = dest;

	position.x = dest->x;
	position.y = dest->y;

	SetTexture(game->GetEngine()->GetTexture("Assets/TileMap.png"));
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
		SDL_RenderCopyEx(renderer,
			mTexture,
			mSrcRect,
			mDestRect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
	//TODO: Check camera collision with tile
}

void Tile::Update(float deltaTime)
{
	mDestRect->x = position.x - mGame->mCamera.x;
	mDestRect->y = position.y - mGame->mCamera.y;
}
