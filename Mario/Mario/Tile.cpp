#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game, SDL_Rect* src, SDL_Rect* dest, int tileType):  Actor(game), SpriteComponent(this) //sets up the base classes
{	
	//Sets the dest and src rect equal to the ones passed in
	mSrcRect = src;
	mDestRect = dest;

	//sets the tile position to the dest rect position
	position.x = dest->x;
	position.y = dest->y;

	//Sets the texture to the tile map
	SetTexture(game->GetEngine()->GetTexture("Assets/TileMap.png"));

	//Sets the position of the tile
	SetPosition(Vector2(mDestRect->x, mDestRect->y));

	//Adds a tile to the current game screen
	mGame->GetCurrentScreen()->AddTile(this);
}

Tile::~Tile()
{
	//Removes a tile from the current game screen
	mGame->GetCurrentScreen()->RemoveTile(this);
}

void Tile::Draw(SDL_Renderer* renderer)
{
	//if a texture is found then
	if (mTexture) {
		//render the tile
		SDL_RenderCopyEx(renderer,
			mTexture,
			mSrcRect,
			mDestRect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void Tile::Update(float deltaTime)
{
	//sets up world position vs screen position
	mDestRect->x = position.x - mGame->mCamera.x;
	mDestRect->y = position.y - mGame->mCamera.y;
}
