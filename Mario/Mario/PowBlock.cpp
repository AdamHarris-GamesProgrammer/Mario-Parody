#include "PowBlock.h"
#include "Game.h"
#include "TileMapComponent.h"
PowBlock::PowBlock(class Game* game, SDL_Rect* srcRect, SDL_Rect* destRect) : Tile(game, srcRect, destRect, 32){}

PowBlock::~PowBlock(){}

void PowBlock::TakeDamage()
{
	//If active
	if (bActive) {
		//decrement the healthLeft variables
		healthLeft--;

		//determines the src rect
		SDL_Rect* rect = new SDL_Rect{ (4 - healthLeft) * TILE_WIDTH, 32, TILE_WIDTH, TILE_HEIGHT };
		SetSrcRect(rect);

		//increments the score
		mGame->IncrementScore(20);
		if (healthLeft <= 0)
		{
			bActive = false;
			mGame->IncrementScore(100); //bonus points for destroying the whole pow block
			mGame->GetCurrentScreen()->RemovePowBlock(this); //removes the pow block from the current game screen
			mGame->GetCurrentScreen()->GetMap()->ChangeTileAt((GetPosition().y / TILE_HEIGHT), (GetPosition().x / TILE_WIDTH), -1); //changes the value of this tile to air, allowing the player to jump through it
			SetState(Actor::EDead); //Sets this object to be deleted on next frame
		}
	}
	
}
